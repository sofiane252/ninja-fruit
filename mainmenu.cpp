#include "mainmenu.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QRadioButton>
#include <QGroupBox>
#include <QButtonGroup>
#include <QDebug>

MainMenu::MainMenu(QWidget *parent) : QWidget(parent) {
    QBoxLayout *layout = new QVBoxLayout(this);
    this->setFixedSize(1080, 720);

    QGroupBox *difficultyBox = new QGroupBox("Niveau de difficulté", this);
    QVBoxLayout *difficultyLayout = new QVBoxLayout(difficultyBox);
    QButtonGroup *difficultyGroup = new QButtonGroup(difficultyBox);

    QRadioButton *easyButton = new QRadioButton("Facile", difficultyBox);
    QRadioButton *mediumButton = new QRadioButton("Intermédiaire", difficultyBox);
    QRadioButton *hardButton = new QRadioButton("Difficile", difficultyBox);

    difficultyGroup->addButton(easyButton, 0);
    difficultyGroup->addButton(mediumButton, 1);
    difficultyGroup->addButton(hardButton, 2);

    difficultyLayout->addWidget(easyButton);
    difficultyLayout->addWidget(mediumButton);
    difficultyLayout->addWidget(hardButton);

    layout->addWidget(difficultyBox);

    startButton = new QPushButton("Lancer le jeu", this);
    startButton->setFixedSize(1080, 320);
    connect(startButton, &QPushButton::clicked, this, &MainMenu::startGame);

    quitButton = new QPushButton("Quitter", this);
    quitButton->setFixedSize(1080, 320);
    connect(quitButton, &QPushButton::clicked, this, &MainMenu::close);

    layout->addWidget(startButton);
    layout->addWidget(quitButton);

    // Connexion du signal buttonClicked du groupe de boutons radio à une méthode
    connect(difficultyGroup, QOverload<int>::of(&QButtonGroup::idClicked), this, &MainMenu::handleDifficultySelectionV2);

}

void MainMenu::handleDifficultySelectionV2(int id) {
    if (id == 0) {
        qDebug() << "Facile sélectionné";
        this->setLives(10);
        this->setFruitSpeed(3000);
        this->setFruitSpawnInterval(700);
    } else if (id == 1) {
        qDebug() << "Intermédiaire sélectionné";
        this->setLives(7);
        this->setFruitSpeed(2000);
        this->setFruitSpawnInterval(600);
    } else if (id == 2) {
        qDebug() << "Difficile sélectionné";
        this->setLives(5);
        this->setFruitSpeed(1600);
        this->setFruitSpawnInterval(450);
    }
}

void MainMenu::startGame() {
    emit gameStarted();
}

void MainMenu::setFruitSpeed(int speed) {
    m_fruitSpeed = speed;
}

void MainMenu::setFruitSpawnInterval(int frequence) {
    m_fruitSpawnFrequence = frequence;
}

int MainMenu::fruitSpeed() {
    return m_fruitSpeed;
}

int MainMenu::fruitFrequence() {
    return m_fruitSpawnFrequence;
}

void MainMenu::setLives(int l) {
    live = l;
}

int MainMenu::lives() {
    return live;
}