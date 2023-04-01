#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QLabel>
#include <QTimer>
#include <QPropertyAnimation>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    void start(int lives, int windowWidth, int windowHeight, int fruitSpeed, int fruitFrequence);
    void spawnFruit();

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    void updateLivesLabel();
    void updateScoreLabel();
    void init();
    void setLives(int l);
    int getLives();
    void setSpeed(int s);
    int getSpeed();
    void setFruitFrequence(int fF);

    int getFrequence();
    void setWindowWidth(int W);

    int getWindowWidth();
    void setWindowHeight(int H);
    int getWindowHeight();
    


    QGraphicsScene *scene;
    QGraphicsView *view;
    QLabel *livesLabel;
    QLabel *scoreLabel;
    QTimer *timer;
    QPropertyAnimation *animation;

    int lives;
    int score;
    int fruitSpeed;
    int fruitFrequence;
    int windowWidth;
    int windowHeight;
};

#endif // MAINWINDOW_H
