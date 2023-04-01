#include "fruit.h"
#include <QGraphicsPixmapItem>

Fruit::Fruit(const QPixmap &pixmap, const QString &imagePath, int points, FruitType type)
: QGraphicsPixmapItem(pixmap), imagePath(imagePath), points(points), type(type) {
    setPixmap(pixmap);
    if (imagePath == "./assets/img/bombe.png")
        type = BOMB;
    type = FRUIT;
    
}

int Fruit::getPoints() {
    return points;
}

QString Fruit::getImagePath() {
    return imagePath;
}

Fruit::FruitType Fruit::getType() {
    return type;
}
