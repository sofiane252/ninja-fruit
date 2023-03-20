#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr)
        : QMainWindow(parent)
    {
        setWindowTitle("Fruit Ninja");
        setFixedSize(800, 600);

        /*QLabel *scoreLabel = new QLabel("Score: 0", this);
        scoreLabel->setGeometry(10, 10, 100, 30);*/
    }
};