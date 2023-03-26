#include "mainwindow.h"
#include <fruit.h>
#include <QGraphicsPixmapItem>
#include <QRandomGenerator>
#include <QMouseEvent>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    scene = new QGraphicsScene(this);
        view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setMouseTracking(true);

    setCentralWidget(view);
    setWindowTitle("Fruit Ninja");
    resize(800, 600);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::spawnFruit);
    timer->start(1000);
}

void MainWindow::spawnFruit() {
    QStringList fruitImages = {
        "./assets/img/ananas.png",
        "./assets/img/banane.png",
        "./assets/img/bombe.png",
        "./assets/img/cerise.png",
        "./assets/img/fraise.png",
        "./assets/img/les-raisins.png",
        ".assets/img/pomme.png"
        };
    QString fruitImage = fruitImages[QRandomGenerator::global()->bounded(fruitImages.size())];

    int fruitWidth = 100;
    int fruitHeight = 100;
    QPixmap originalPixmap(fruitImage);

    QPixmap scaledPixmap = originalPixmap.scaled(fruitWidth, fruitHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    Fruit *fruit = new Fruit(scaledPixmap);
    fruit->setPos(QRandomGenerator::global()->bounded(scene->width()
    - fruit->boundingRect().width()), scene->height());
    scene->addItem(fruit);

   animation = new QPropertyAnimation(fruit, "pos");
    animation->setDuration(2000);
    animation->setStartValue(fruit->pos());
    animation->setEndValue(QPointF(fruit->x(), 0 - fruit->boundingRect().height()));
    animation->setEasingCurve(QEasingCurve::InQuad);

    connect(animation, &QPropertyAnimation::finished, [=]() {
        animation->targetObject()->deleteLater();
        animation->deleteLater();
    });
    animation->start();
}


void MainWindow::mouseMoveEvent(QMouseEvent *event) {
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

    QMainWindow::mouseMoveEvent(event);
}

