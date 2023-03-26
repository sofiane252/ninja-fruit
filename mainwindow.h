#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPropertyAnimation>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <QLabel>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    int lives;
    QLabel *livesLabel;
    QPropertyAnimation *animation;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QTimer *timer;

private slots:
    void spawnFruit();
    void updateLivesLabel();

protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // MAINWINDOW_H
