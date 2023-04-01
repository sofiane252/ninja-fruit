#include "mainwindow.h"
#include "mainmenu.h"
#include "fruit.h"
#include <QWidget>
#include <QGraphicsView>
#include <QMessageBox>
#include <QMouseEvent>
#include <QStatusBar>
#include <QDebug>
#include <QRandomGenerator>
#include <QCoreApplication>
#include <QGraphicsScene>



MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    
    init();
    qDebug() << "--------------";

    scene = new QGraphicsScene(this);
    view = new QGraphicsView(scene, this);

    setCentralWidget(view);
    view->setRenderHint(QPainter::Antialiasing);
    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    view->setMouseTracking(true);

    setFixedSize(windowWidth, windowHeight);

    QPixmap backgroundImage("./assets/img/background.jpg");
    QBrush backgroundBrush(backgroundImage);
    view->setBackgroundBrush(backgroundBrush);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Ajustement de la taille de la scène pour correspondre à la taille de la fenêtre
    scene->setSceneRect(0, 0, windowWidth, windowHeight);

    scoreLabel = new QLabel(this);
    updateScoreLabel();
    statusBar()->addWidget(scoreLabel);
}

void MainWindow::init(){
    setLives(1);
    score = 0;
    setSpeed(5000); 
    setFruitFrequence(600);
    setWindowWidth(1080);
    setWindowHeight(720);
    qDebug() << "Init OK";
}

void MainWindow::start(int lives, int windowWidth, int windowHeight, int fruitSpeed, int fruitFrequence) {
    setLives(lives);

    livesLabel = new QLabel(this);
    updateLivesLabel();
    statusBar()->addWidget(livesLabel);


    setSpeed(fruitSpeed); 

    setFruitFrequence(fruitFrequence);
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::spawnFruit);
    timer->start(getFrequence());
    
    setWindowWidth(windowWidth);
    setWindowHeight(windowHeight);

    spawnFruit();
}

void MainWindow::spawnFruit() {
    struct FruitInfo {
        QString imagePath;
        int points;
        Fruit::FruitType type;
    };

    QVector<FruitInfo> fruitImages = {
        {"./assets/img/ananas.png", 10, Fruit::FRUIT},
        {"./assets/img/banane.png", 15, Fruit::FRUIT},
        {"./assets/img/bombe.png", -50, Fruit::BOMB},
        {"./assets/img/cerise.png", 20, Fruit::FRUIT},
        {"./assets/img/fraise.png", 25, Fruit::FRUIT},
        {"./assets/img/les-raisins.png", 30, Fruit::FRUIT},
        {"./assets/img/pomme.png", 35, Fruit::FRUIT}
    };

    FruitInfo fruitInfo = fruitImages[QRandomGenerator::global()->bounded(fruitImages.size())];

    int fruitWidth = 100;
    int fruitHeight = 100;
    QPixmap originalPixmap(fruitInfo.imagePath);

    QPixmap scaledPixmap = originalPixmap.scaled(fruitWidth, fruitHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    
    Fruit *fruit = new Fruit(scaledPixmap, fruitInfo.imagePath, fruitInfo.points, fruitInfo.type);
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
        animation->setDuration(getSpeed());
        animation->setStartValue(QPointF(fruit->x(), 0 - fruit->boundingRect().height())); // Position de départ en haut de la fenêtre
        animation->setEndValue(QPointF(fruit->x(), scene->height())); // Position finale en bas de la fenêtre
        animation->setEasingCurve(QEasingCurve::InQuad);

        
        connect(animation, &QPropertyAnimation::finished, [=]() {
            if (scene->items().contains(fruit)) {
                if (fruit->getType() != Fruit::BOMB) {
                    lives--;
                    updateLivesLabel();
                }
                
                if (lives == 0) {
                    QMessageBox::information(this, "Game Over", "Vous avez perdu toutes vos vies. Le jeu va maintenant se terminer.");
                    QCoreApplication::quit();
                }
            }
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
    if (Fruit *fruit = dynamic_cast<Fruit*>(itemToDelete)) {
        if (fruit->getType() == Fruit::BOMB) {
            lives--;
            score -= 50;
            if (score < 0) {
                score = 0;
            }
            if (lives <= 0) {
                QMessageBox::information(this, "Game Over", "Vous avez perdu toutes vos vies. Le jeu va maintenant se terminer.");
                QCoreApplication::quit();
            }
        } else {
            score += fruit->getPoints();
        }
        updateLivesLabel();
        updateScoreLabel();
    }
    
    scene->removeItem(itemToDelete);
    delete itemToDelete;
}
    }

    QMainWindow::mousePressEvent(event);
}

void MainWindow::updateLivesLabel() {
    livesLabel->setText("Vies : " + QString::number(getLives()));
}

void MainWindow::updateScoreLabel() {
    scoreLabel->setText("Score : " + QString::number(score));
}

void MainWindow::setLives(int l) {
    lives = l;
}

int MainWindow::getLives() {
    return lives;
}

void MainWindow::setSpeed(int s) {
    fruitSpeed = s;
}

int MainWindow::getSpeed() {
    return fruitSpeed;
}

void MainWindow::setFruitFrequence(int fF) {
    fruitFrequence = fF;
}

int MainWindow::getFrequence() {
    return fruitFrequence;
}

void MainWindow::setWindowWidth(int W) {
    windowWidth = W;
}

int MainWindow::getWindowWidth() {
    return windowWidth;
}

void MainWindow::setWindowHeight(int H) {
    windowHeight = H;
}

int MainWindow::getWindowHeight() {
    return windowHeight;
}

