#include "QGameWindow.h"
#define pass  

QGameWindow::QGameWindow(QWidget* parent) {
	ui.setupUi(this); 
	// TODO: ����ۺ����Ĳ��á���ť/��ʾ�������źŵ�����
	
	connect(ui.exitButton, &QPushButton::clicked, this, &QGameWindow::exitToMenu);
	connect(ui.pauseButton, &QPushButton::clicked, this, &QGameWindow::pause);
	connect(ui.saveButton, &QPushButton::clicked, this, &QGameWindow::saveSL);

	//
}

void QGameWindow::newGameInit(const int& difficulty) {
	// TODO: ��ʼ������

	//
	qDebug("[INFO]: GameInitCompleted");
	emit startupCompleted(*this);
}


void QGameWindow::loadGame(const QFile& binSL) {
	// TODO: �浵����
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