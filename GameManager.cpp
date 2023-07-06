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
	playerx = 4;
	playery = 7;

	// connect(player, &PlayerPiece::death, this, &GameManager::lose);


}