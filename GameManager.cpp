#include "GameManager.h"

const QString FONTDIR = "./Fonts/fusion-pixel-proportional.ttf";

GameManager::GameManager(const QString& dir_archive):enemyGenCount(0), level(0) {
	QFontDatabase::addApplicationFont(FONTDIR);
	setFixedSize(1280, 720);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	main_sce = new QGraphicsScene(this);
	main_sce->setSceneRect(0, 0, 1280, 720);
	setScene(main_sce);

	QPixmap backgroundPixmap("./images/GameBg.png");
	m_background = new QGraphicsPixmapItem;
	m_background->setPixmap(backgroundPixmap);
	m_background->setScale(0.5);
	main_sce->addItem(m_background);

	player = new PlayerPiece(this);
	playerx = 4;
	playery = 7;

	// connect(player, &PlayerPiece::death, this, &GameManager::lose);


}

GameManager::GameManager(const int& difficulty) :enemyGenCount(0), level(0), difficulty(difficulty) {
	QFontDatabase::addApplicationFont(FONTDIR);
	setFixedSize(1280, 720);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	main_sce = new QGraphicsScene(this);
	main_sce->setSceneRect(0, 0, 1280, 720);
	setScene(main_sce);

	QPixmap backgroundPixmap("./images/GameBg.png");
	m_background = new QGraphicsPixmapItem;
	m_background->setPixmap(backgroundPixmap);
	m_background->setScale(0.5);
	main_sce->addItem(m_background);

	player = new PlayerPiece(this);
	player->setParent(this);
	playerx = 4;
	playery = 7;
	main_sce->addItem(player);
	player->setScale(0.075);
	player->setPos(403+62.5*playerx, 125+62.5*playery);
	player->show();
	// connect(player, &PlayerPiece::death, this, &GameManager::lose);

	playerHpmax = playerHp = 25;
	playerDef = 0;
	playerAtk = 5;
	playerDodge = 0;
	playerScatterAngle = 45;

	level = 0;
	expnow = 0;
	expneed = 10;

	enemyGenCount = 0;
	pesudoTime = 0;

	QFile sqrPb("./Qss/SqrButton.qss");
	sqrPb.open(QFile::ReadOnly);
	QString style_sqr_pb;
	if (sqrPb.isOpen()) {
		style_sqr_pb = QLatin1String(sqrPb.readAll());
		sqrPb.close();
	}

	pb_pause = new QPushButton("Exit", this);
	connect(pb_pause, &QPushButton::clicked, this, [=]() {returnToMenu();});
	pb_pause->setStyleSheet(style_sqr_pb);
	pb_pause->move(1000, 600);
	pb_pause->resize(100, 100);

	pb_restart = new QPushButton("Restart", this);
	connect(pb_restart, &QPushButton::clicked, this, [=]() {restart(); });
	pb_restart->setStyleSheet(style_sqr_pb);
	pb_restart->move(1150, 600);
	pb_restart->resize(100, 100);
	main_sce->addWidget(pb_restart);
}



void GameManager::returnToMenu() {
	emit gameEnd();
	this->hide();
	return;
}

