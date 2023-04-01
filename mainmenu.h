#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QPushButton>
#include "mainwindow.h"

class MainMenu : public QWidget {
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = nullptr);
    void setFruitSpawnInterval(int interval);
    int fruitFrequence();
    void setFruitSpeed(int speed);
    int fruitSpeed();
    void setLives(int l);
    int lives();

signals:
    void gameStarted();

public slots:
    void startGame();
    void handleDifficultySelectionV2(int id);

private:
    int m_fruitSpawnFrequence;
    int m_fruitSpeed;
    int live;
    QPushButton *startButton;
    QPushButton *difficultyButton;
    QPushButton *quitButton;
    MainWindow *mainWindow;
};

#endif // MAINMENU_H
