#include "GameWidgetNew.h"

GameWidgetNew::GameWidgetNew(QWidget* parent) {

	setMouseTracking(true);
	setFixedSize(1280, 720);

	setWindowTitle("Game Main");
	initMenu();
	initGameMan();
}

void GameWidgetNew::initMenu() {
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
	ptr_gameMan = new GameManager();
	return;
}

void GameWidgetNew::startGameMan() {
	ptr_startMenu->hide();
	ptr_gameMan->show();
	ptr_gameMan->setFocus();
	return;
}