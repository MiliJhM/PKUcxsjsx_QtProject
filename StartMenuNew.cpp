#include "StartMenuNew.h"
#include "ResSettings.h"

StartMenuNew::StartMenuNew(QWidget *parent)
	: QGraphicsView(parent)
{
	QFontDatabase::addApplicationFont(FONTDIR);

	// 窗口策略
	setFixedSize(1280, 720);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	// 主菜单场景初始化
	sce_main = new QGraphicsScene(this);
	sce_main->setSceneRect(0, 0, 1280, 720);
	// sce_main->addPixmap("background")

	start_button = new QPushButton("Start Game", this);
	difficulty_button = new QPushButton("Set Difficulty", this);
	load_button = new QPushButton("Load Archive", this);
	difficulty_label = new QLabel(this);
	difficulty_label->setNum(difficulty);
	start_button->move(530, 200);
	start_button->resize(220, 110);

	difficulty_button->move(530, 330);
	difficulty_button->resize(220, 110);

	difficulty_label->move(800, 330);
	difficulty_label->resize(55, 110);

	load_button->move(530, 460);
	load_button->resize(220, 110);

	sce_main->addWidget(start_button);
	connect(start_button, &QPushButton::clicked, this, &StartMenuNew::startGame);
	sce_main->addWidget(difficulty_button);
	connect(difficulty_button, &QPushButton::clicked, this, &StartMenuNew::changeDiff);
	sce_main->addWidget(load_button);
	sce_main->addWidget(difficulty_label);
	connect(this, &StartMenuNew::difficultySet, difficulty_label, QOverload<int>::of(&QLabel::setNum));
	setScene(sce_main);
}


int StartMenuNew::changeDiff() {
	difficulty %= 5;
	difficulty += 1;
	emit difficultySet(difficulty);
	return difficulty;
	
}

void StartMenuNew::startGame() {
	emit gameStarted();
	return;
}