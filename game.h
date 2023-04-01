#ifndef GAME_H
#define GAME_H

#include "mainwindow.h"
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsTextItem>

class MainWindow;

class Game : public QWidget {
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    explicit Game();

};

#endif // GAME_H
