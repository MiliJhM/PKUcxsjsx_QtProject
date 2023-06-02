#include "QGameWindow.h"
#define pass  

QGameWindow::QGameWindow(QWidget* parent) {
	ui.setupUi(this); 
	// TODO: 该类槽函数的布置、按钮/显示和主类信号的连接
	
	connect(ui.exitButton, &QPushButton::clicked, this, &QGameWindow::exitToMenu);
	connect(ui.pauseButton, &QPushButton::clicked, this, &QGameWindow::pause);
	connect(ui.saveButton, &QPushButton::clicked, this, &QGameWindow::saveSL);

	//
}

void QGameWindow::newGameInit(const int& difficulty) {
	// TODO: 初始化棋盘

	//
	qDebug("[INFO]: GameInitCompleted");
	emit startupCompleted(*this);
}


void QGameWindow::loadGame(const QFile& binSL) {
	// TODO: 存档加载
	pass;
	//
	qDebug("[INFO]: GameLoadedCompleted");
	emit startupCompleted(*this);
}

void QGameWindow::pause() {
	pass;
	qDebug("[INFO]: Paused");
}

void QGameWindow::exitToMenu() {
	pass;
	qDebug("[INFO]: ExitClicked, exitToMenu");
	emit menuReopen(*this);
}

void QGameWindow::saveSL() {
	pass;
	qDebug("[INFO]: Save as %s", "meizuowan.dat");
}