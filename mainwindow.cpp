#include "mainwindow.h"
#include <fruit.h>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>
#include <QMouseEvent>
#include <QCoreApplication>
#include <QMessageBox>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) 
{
    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    setCentralWidget(view);
    view->setRenderHint(QPainter::Antialiasing);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setMouseTracking(true);

    lives = 5; //nombre de vie du joueur

    // Taille personnalisée de la fenêtre
    int windowWidth = 1080;
    int windowHeight = 720;
    setFixedSize(windowWidth, windowHeight);

    // Retirer la scrollbar (vue)
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Ajustement de la taille de la scène pour correspondre à la taille de la fenêtre
    scene->setSceneRect(0, 0, windowWidth, windowHeight);

    // Mettre background
    QPixmap backgroundImage("./assets/img/background.jpg");
    QBrush backgroundBrush(backgroundImage);
    view->setBackgroundBrush(backgroundBrush);

    // Création et ajout du label pour afficher les vies à la barre de statut
    livesLabel = new QLabel(this);
    updateLivesLabel();
    statusBar()->addWidget(livesLabel);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::spawnFruit);
    timer->start(700);
}

void MainWindow::spawnFruit() {
    QStringList fruitImages = {
        "./assets/img/ananas.png",
        "./assets/img/banane.png",
        "./assets/img/bombe.png",
        "./assets/img/cerise.png",
        "./assets/img/fraise.png",
        "./assets/img/les-raisins.png",
        "./assets/img/pomme.png"
        };
    QString fruitImage = fruitImages[QRandomGenerator::global()->bounded(fruitImages.size())];

    int fruitSpeed = 2000; // vitesse de la chute
    int fruitWidth = 80;
    int fruitHeight = 80;
    QPixmap originalPixmap(fruitImage);

    QPixmap scaledPixmap = originalPixmap.scaled(fruitWidth, fruitHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    
    Fruit *fruit = new Fruit(scaledPixmap);
    bool noCollision = false;
    int maxTries = 10;
    int tries = 0;

    while (!noCollision && tries < maxTries) {
        qreal x = QRandomGenerator::global()->bounded(scene->width() - fruit->boundingRect().width());
        qreal y = scene->height();

        fruit->setPos(x, y);

        noCollision = true;
        for (QGraphicsItem *item : scene->items()) {
            if (item != fruit && item->collidesWithItem(fruit)) {
                noCollision = false;
                break;
            }
        }

        tries++;
    }

    if (noCollision) {
        scene->addItem(fruit);

        animation = new QPropertyAnimation(fruit, "pos");
        animation->setDuration(fruitSpeed);
         animation->setStartValue(QPointF(fruit->x(), 0 - fruit->boundingRect().height())); // Position de départ en haut de la fenêtre
        animation->setEndValue(QPointF(fruit->x(), scene->height())); // Position finale en bas de la fenêtre
        animation->setEasingCurve(QEasingCurve::InQuad);

        // Connectez le signal 'finished' de l'animation pour détecter quand un fruit atteint le bas de la fenêtre
        connect(animation, &QPropertyAnimation::finished, [=]() {
            // Vérifiez si le fruit est toujours dans la scène (il n'a pas été coupé)
            if (scene->items().contains(fruit)) {
                // Décrémentez le compteur de vies et mettez à jour le label
                lives--;
                updateLivesLabel();

                // Vérifiez si le joueur a perdu toutes ses vies
                if (lives <= 0) {
                    // Affichez un message indiquant que le joueur a perdu et quittez le jeu
                    // QMessageBox::information(this, "Game Over", "Vous avez perdu toutes vos vies. Le jeu va maintenant se terminer.");
                    // Affichez une boîte de dialogue pour demander au joueur s'il veut recommencer ou quitter
                    QMessageBox::StandardButton reply;
                    reply = QMessageBox::question(this, "Recommencer", "Voulez-vous recommencer le jeu ?", QMessageBox::Yes|QMessageBox::No);
                    if (reply == QMessageBox::Yes) {
                        // Si le joueur a choisi de recommencer, redémarrez le jeu
                        restartGame();
                    } else {
                        // Si le joueur a choisi de quitter, quittez le jeu
                        QCoreApplication::quit();
                    }
                }
            }
            //animation->targetObject()->deleteLater();
            //animation->deleteLater();
            fruit->deleteLater();
            animation->deleteLater();
        });
        animation->start();
    } else {
        delete fruit;
    }

}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QPointF mousePos = event->pos();
        QGraphicsItem *itemToDelete = nullptr;

        // Parcours de tous les éléments de la scène
        for (QGraphicsItem *item : scene->items()) {
            if (item->contains(item->mapFromScene(mousePos))) {
                itemToDelete = item;
                break;
            }
        }

        // Si un fruit a été touché par le curseur, supprimez-le de la scène
        if (itemToDelete) {
            scene->removeItem(itemToDelete);
            delete itemToDelete;
        }
    }

    QMainWindow::mousePressEvent(event);
}

void MainWindow::restartGame() {
    // Réinitialiser les variables du jeu
    lives = 5;
    updateLivesLabel();

    // Redémarrer le timer
    timer->start(1000);
}

void MainWindow::updateLivesLabel() {
    livesLabel->setText("Vies : " + QString::number(lives));
}
