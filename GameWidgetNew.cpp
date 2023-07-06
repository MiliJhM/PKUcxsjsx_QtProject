#include "GameWidgetNew.h"

GameWidgetNew::GameWidgetNew(QWidget* parent) {

	setMouseTracking(true);
	setFixedSize(1280, 720);

	setWindowTitle("Game Main");
	initMenu();
}

void GameWidgetNew::initMenu() {
	ptr_startMenu = new StartMenuNew(this);
	connect(ptr_startMenu, &StartMenuNew::difficultySet, this, &GameWidgetNew::setDiff);
	connect(ptr_startMenu, &StartMenuNew::gameStarted, this, [=]() {initGameMan(); startGameMan(); });
	ptr_startMenu->show();
}

void GameWidgetNew::setDiff(int diff) {
	gameDiff = diff;
	return;
}

void GameWidgetNew::initGameMan() {
	ptr_gameMan = new GameManager(gameDiff);
	ptr_gameMan->setParent(this);
	connect(ptr_gameMan, &GameManager::gameEnd, this, [=]() {gameEnd(); });
	connect(ptr_gameMan, &GameManager::restart, this, [=]() {gameEnd(); initGameMan(); startGameMan(); });
	ptr_gameMan->hide();
	return;
}

void GameWidgetNew::startGameMan() {
	ptr_startMenu->hide();
	ptr_gameMan->show();
	ptr_gameMan->setFocus();
	return;
}

void GameWidgetNew::gameEnd() {
	ptr_gameMan->hide();
	ptr_startMenu->show();
	ptr_startMenu->setFocus();
	return;
}