#include "GameManager.h"
#include <iostream>
#include <sstream>
#include <string>

const QString FONTDIR = "./Fonts/fusion-pixel-proportional.ttf";



GameManager::GameManager(const QString& dir_archive):enemyGenCount(0), level(0) {

	//Deprecated
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

	//
}

GameManager::GameManager(const int& difficulty, QWidget* parent) : QGraphicsView(parent), enemyGenCount(0), level(0), difficulty(difficulty) {
	QFontDatabase::addApplicationFont(FONTDIR);
	setFixedSize(1280, 720);
	setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	//qDebug() << "Sec1"<<this->parent();
	setMouseTracking(true);
	main_sce = new QGraphicsScene(this);
	main_sce->setSceneRect(0, 0, 1280, 720);
	setScene(main_sce);

	QPixmap backgroundPixmap("./images/GameBg.png");
	m_background = new QGraphicsPixmapItem;
	m_background->setPixmap(backgroundPixmap);
	m_background->setScale(0.5);
	main_sce->addItem(m_background);

	mainTimer = new QTimer(this);
	Bullet::bulletTimerStatic = mainTimer;
	mainTimer->start(10);
	fireTimer = new QTimer(this);
	connect(fireTimer, &QTimer::timeout, this, [=]() {fireCd(); });

	player = new PlayerPiece(this);
	player->setParent(this);
	playerx = 4;
	playery = 7;
	main_sce->addItem(player);
	player->setScale(0.075);
	player->setPos(403+62.5*playerx, 125+62.5*playery);
	player->show();
	// connect(player, &PlayerPiece::death, this, &GameManager::lose);

	sfxMove = new QSoundEffect(this);
	sfxMove->setSource(QUrl::fromLocalFile("./Sounds/move.wav"));
	sfxMove->setVolume(0.5);

	BotBase::sfxEnemyHurt = new QSoundEffect(this);
	BotBase::sfxEnemyHurt->setSource(QUrl::fromLocalFile("./Sounds/Hurt.wav"));
	BotBase::sfxEnemyHurt->setVolume(0.1);

	effReadyToMove = new QGraphicsOpacityEffect(this);
	effReadyToMove->setOpacity(1);
	player->setGraphicsEffect(effReadyToMove);
	

	effHurted = new QGraphicsColorizeEffect(this);
	effHurted->setColor(QColor(192, 0, 0));
	effHurted->setStrength(0);
	

	playerHpmax = playerHp = 25;
	playerDef = 0;
	playerAtk = 5;
	playerDodge = 0;
	playerScatterAngle = 45;
	playerBulletNum = 5;

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

	QFont titleFont("fusion pixel proportional", 16, 50);
	QFont contFont("fusion pixel proportional", 16, 50);

	lb_hpnow = new QLabel(this);
	std::stringstream ss;
	ss << playerHp << " / " << playerHpmax;
	lb_hpnow->setText(ss.str().c_str());
	ss.str(std::string());
	ss.clear();
	ss.flush();
	lb_hpnow->setFont(contFont);
	lb_hpnow->setStyleSheet("color:white;");
	lb_hpnow->resize(300, 50);
	lb_hpnow->move(100, 125);
	main_sce->addWidget(lb_hpnow);
	lb_atk = new QLabel(this);
	lb_atk->setFont(contFont);
	lb_atk->setNum(playerAtk);
	lb_atk->setStyleSheet("color:white;");
	lb_atk->resize(100, 50);
	lb_atk->move(100, 215);
	main_sce->addWidget(lb_atk);
	lb_def = new QLabel(this);
	lb_def->setFont(contFont);
	lb_def->setNum(playerDef);
	lb_def->resize(100, 50);
	lb_def->setStyleSheet("color:white;");
	lb_def->move(260, 215);
	main_sce->addWidget(lb_def);
	lb_dodge = new QLabel(this);
	lb_dodge->setFont(contFont);
	lb_dodge->setNum(playerDodge);
	lb_dodge->resize(100, 50);
	lb_dodge->setStyleSheet("color:white;");
	lb_dodge->move(100, 305);
	main_sce->addWidget(lb_dodge);
	lb_scAngle = new QLabel(this);
	lb_scAngle->setFont(contFont);
	lb_scAngle->resize(100, 50);
	lb_scAngle->setNum(playerScatterAngle);
	lb_scAngle->setStyleSheet("color:white;");
	lb_scAngle->move(100, 395);
	main_sce->addWidget(lb_scAngle);
	lb_bulletNum = new QLabel(this);
	lb_bulletNum->setFont(contFont);
	lb_bulletNum->setNum(playerBulletNum);
	lb_bulletNum->resize(100, 50);
	lb_bulletNum->setStyleSheet("color:white;");
	lb_bulletNum->move(260, 395);
	main_sce->addWidget(lb_bulletNum);

	lb_level = new QLabel(this);
	lb_level->setFont(contFont);
	lb_level->setNum(level);
	lb_level->resize(100, 50);
	lb_level->setStyleSheet("color:white;");
	lb_level->move(1050, 125);
	main_sce->addWidget(lb_level);
	lb_expnow = new QLabel(this);
	ss << expnow << " / " << expneed;
	lb_expnow->setFont(contFont);
	lb_expnow->setText(ss.str().c_str());
	lb_expnow->resize(250, 50);
	lb_expnow->setStyleSheet("color:white;");
	lb_expnow->move(1050, 215);
	main_sce->addWidget(lb_expnow);
	ss.str(std::string());
	ss.clear();
	ss.flush();
	lb_killCounter = new QLabel(this);
	lb_killCounter->setFont(contFont);
	lb_killCounter->setNum(killCounter);
	lb_killCounter->resize(100, 50);
	lb_killCounter->setStyleSheet("color:white;");
	lb_killCounter->move(1050, 305);
	main_sce->addWidget(lb_killCounter);
	lb_diff = new QLabel(this);
	lb_diff->setFont(contFont);
	lb_diff->setNum(difficulty);
	lb_diff->setStyleSheet("color:white;");
	lb_diff->move(1050, 395);
	main_sce->addWidget(lb_diff);

	connect(player, &PlayerPiece::playerHurt, this, [=]() {setHpPrinter(); });

	weapon = new Shotgun(player, main_sce, this);
	weapon->updatePos();
	weapon->setGraphicsEffect(effHurted);
	main_sce->addItem(weapon);

	chessboard[0][0] = new BotBase(0, 0, 100, 2, 1500, this);
	chessboard[0][0]->setPos(390, 138);
	connect(chessboard[0][0], &BotBase::botDeath, this, &GameManager::enemyDeathProcess);
	main_sce->addItem(chessboard[0][0]);

}

void GameManager::enemyDeathProcess(const int& expWhenDie, int x, int y) {
	killCounter++;
	expGet(expWhenDie);
	setAllPrinter();
	chessboard[x][y] = nullptr;
}

void GameManager::setAllPrinter() {
	setHpPrinter();
	setExpPrinter();
	lb_atk->setNum(playerAtk);
	lb_def->setNum(playerDef);
	lb_dodge->setNum(playerDodge);
	lb_scAngle->setNum(playerScatterAngle);
	lb_bulletNum->setNum(playerBulletNum);
	lb_level->setNum(level);
	lb_killCounter->setNum(killCounter);
	return;
}

void GameManager::returnToMenu() {
	emit gameEnd();
	this->hide();
	return;
}

void GameManager::setHpPrinter() {
	std::stringstream ss;
	ss << playerHp << " / " << playerHpmax;
	lb_hpnow->setText(ss.str().c_str());
	ss.str(std::string());
	ss.clear();
	ss.flush();
	return;
}

void GameManager::setExpPrinter() {
	std::stringstream ss;
	ss << expnow << " / " << expneed;
	// qDebug() << ss.str().c_str();
	lb_expnow->setText(ss.str().c_str());
	ss.str(std::string());
	ss.clear();
	ss.flush();
	return;
}

void GameManager::levelUp() {
	// QList<int> upgradeList = rougeGenerator();
	// QGraphicsScene* m_scene;
	qreal playerHprest = (playerHp / playerHpmax);
	playerHpmax += 5;
	playerAtk += 1;
	if (level % 4 == 0) {
		playerDef += 1;
		playerBulletNum += 1;
	}
	if (level % 10 == 0) {
		playerScatterAngle -= 5;
		playerDodge += 10;
	}
	playerHp = playerHpmax;
	// qDebug() << playerHp << ' ' << playerHprest;
}

void GameManager::levelCheck() {
	while (expnow >= expneed) {
		expnow -= expneed;
		expneed = 1.2 * expneed;
		qDebug() << expneed<<' ' << level;
		level++;
		levelUp();
	}
}

void GameManager::expGet(const int& x) {
	expnow += x;
	levelCheck();
	return;
}

void GameManager::timerRun() {
	if (pesudoTime % normalRoundTime == 0) {
		//normalMoveRound();
	}
	if (pesudoTime % eliteRoundTime == 0) {
		//eliteMoveRound();
	}
	if (pesudoTime % generateRoundTime == 0) {
		//generateRound();
	}
	pesudoTime++;
}

void GameManager::generateRound() {
	int enemySum = 10 + difficulty * 2;

	return;
}
/*
BotBase* GameManager::enemyGenerate(int& sum) {
	int randomResult = QRandomGenerator::global()->bounded(1, 100);

	return ;
}
*/

void GameManager::mouseMoveEvent(QMouseEvent *event) {
	weapon->rotateToCursor(event->pos());
	QGraphicsView::mouseMoveEvent(event);
}

void GameManager::mousePressEvent(QMouseEvent* event) {
	const QPointF& pt1 = event->pos();
	const QPointF& pt2 = player->pos();
	if (sqrt(double((pt2.x() - pt1.x()+20) * (pt2.x() - pt1.x()+20) + (pt2.y() - pt1.y()+35) * (pt2.y() - pt1.y()+35))) <= 30 && !mouseFlag) {
		mouseFlag = 1;
		effReadyToMove->setOpacity(0.7);
		return;
	}
	if (mouseFlag) {
		int newX = (pt1.x() - 390) / 62.5;
		int newY = (pt1.y() - 137) / 62.5;
		if (playerMoveCheck(newX, newY)) {
			playerMove(newX, newY);
			sfxMove->play();
		}
		mouseFlag = 0;
		effReadyToMove->setOpacity(1);
		timerRun();
		return;
	}
	if(!fireFlag){
		weapon->fire(playerAtk, event->pos(), playerBulletNum, 1, playerScatterAngle);
		fireFlag = 1;
		effHurted->setStrength(0.6);
		timerRun();
		fireTimer->start(1000);
	}

	QGraphicsView::mousePressEvent(event);
}

void GameManager::mouseReleaseEvent(QMouseEvent* event) {
	QGraphicsView::mouseReleaseEvent(event);
}

bool GameManager::playerMoveCheck(int newX, int newY) {
	if (!(newX>=0&&newX<=7&&newY>=0&&newY<=7))
		return false;
	if (abs(newX - playerx) > 1 || abs(newY - playery) > 1)
		return false;
	return true;
}

void GameManager::playerMove(int newX, int newY) {
	player->setPos(403 + 62.5 * newX, 125 + 62.5 * newY);
	playerx = newX, playery = newY;
	weapon->updatePos();
	return;
}

void GameManager::fireCd() {
	fireFlag = 0;
	effHurted->setStrength(0);
}