#include "menuscene.h"
#include <QVBoxLayout>

MenuScene::MenuScene(QWidget *parent) : QWidget(parent) {
   playButton = new QPushButton("Play", this);
   connect(playButton, &QPushButton::clicked, this, &MenuScene::playClicked);
}