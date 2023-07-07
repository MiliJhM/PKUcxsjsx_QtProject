#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QPushButton>
#include <QToolButton>
#include <QGraphicsEffect>
#include <QFontDatabase>
#include <QSettings>
#include <QRadioButton>
#include <QButtonGroup>
#include <QSoundEffect>
#include <QEvent>
#include <QFile>
#include <QUrl>
#include <QLabel>



class StartMenuNew  : public QGraphicsView
{
	Q_OBJECT

public:
	StartMenuNew(QWidget* parent);
	int changeDiff();
	void startGame();


signals:
	void gameStarted();
	void difficultySet(int diff);
	void archiveLoaded(QString& dir);


private:
	QGraphicsScene* sce_main;
	int difficulty = 1;
	
	QPushButton* start_button;
	QPushButton* difficulty_button;
	QPushButton* load_button;
	QLabel* difficulty_label;

};
