#ifndef FRUIT_H
#define FRUIT_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Fruit : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    enum FruitType {
        BOMB,
        FRUIT
    };
    explicit Fruit(const QPixmap &pixmap, const QString &imagePath, int points, FruitType type);
    FruitType type;
    int getPoints();
    QString getImagePath();
    FruitType getType();

private:
    QString imagePath;
    int points;

};

#endif
