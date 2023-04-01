#include <QApplication>
#include "mainwindow.h"
#include "mainmenu.h"
#include <QDebug>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainMenu menu;
    menu.show();

    MainWindow mainWindow;
    
    QObject::connect(&menu, &MainMenu::gameStarted, [&]() {
        mainWindow.show();
        menu.hide();
        mainWindow.start(menu.lives(),
                        1080, 720,
                        menu.fruitSpeed(),
                        menu.fruitFrequence()
        );   
    });

    return app.exec();
}
