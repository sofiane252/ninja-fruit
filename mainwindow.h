#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPropertyAnimation>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    QPropertyAnimation *animation;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QTimer *timer;

private slots:
    void spawnFruit();

protected:
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // MAINWINDOW_H
