#include "StartMenuNew.h"

const QString FONTDIR = "./Fonts/fusion-pixel-proportional.ttf";

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

	QPixmap background("./images/MenuBg.png");
	sce_main->addPixmap(background);

	// 样式表
	QFile rectPb("./Qss/RectButton.qss");
	rectPb.open(QFile::ReadOnly);
	QString style_main_pb;
	if (rectPb.isOpen()) {
		style_main_pb = QLatin1String(rectPb.readAll());
		rectPb.close();
	}

	start_button = new QPushButton("Start Game", this);
	start_button->setStyleSheet(style_main_pb);
	difficulty_button = new QPushButton("Set Difficulty", this);
	difficulty_button->setStyleSheet(style_main_pb);
	load_button = new QPushButton("Load Archive", this);
	load_button->setStyleSheet(style_main_pb);
	difficulty_label = new QLabel(this);
	difficulty_label->setNum(difficulty);
	QFont font("fusion pixel proportional", 32, 50);
	difficulty_label->setFont(font);
	difficulty_label->setStyleSheet("color:white;");
	start_button->move(450, 200);
	start_button->resize(380, 110);

	difficulty_button->move(450, 330);
	difficulty_button->resize(380, 110);

	difficulty_label->move(940, 330);
	difficulty_label->resize(55, 110);

	load_button->move(450, 460);
	load_button->resize(380, 110);

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