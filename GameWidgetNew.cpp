#include "GameWidgetNew.h"

GameWidgetNew::GameWidgetNew(QWidget* parent) {

	setMouseTracking(true);
	setFixedSize(1280, 720);

	setWindowTitle("Game Main");
	ptr_startMenu = new StartMenuNew(this);

	connect(ptr_startMenu, &StartMenuNew::difficultySet, this, &GameWidgetNew::setDiff);
	connect(ptr_startMenu, &StartMenuNew::gameStarted, this, &GameWidgetNew::startGameMan);


	ptr_startMenu->show();
}

void GameWidgetNew::setDiff(int diff) {
	gameDiff = diff;
	return;
}

void GameWidgetNew::initGameMan() {

	return;
}

void GameWidgetNew::startGameMan() {

	return;
}