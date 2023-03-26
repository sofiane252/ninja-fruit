#ifndef FRUIT_H
#define FRUIT_H

#include <QObject>
#include <QGraphicsPixmapItem>

class Fruit : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
    Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
    explicit Fruit(const QPixmap &pixmap);
};

#endif // FRUIT_H
