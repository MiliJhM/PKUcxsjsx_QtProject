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

void GameManager::weaponPosUpd() {
	weapon->updatePos(); weapon->show();
	return;
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

	end_sce = new QGraphicsScene(this);
	end_sce->setSceneRect(0, 0, 1280, 720);

	QPixmap backgroundPixmap("./images/GameBg.png");
	m_background = new QGraphicsPixmapItem;
	m_background->setPixmap(backgroundPixmap);
	m_background->setScale(0.5);
	main_sce->addItem(m_background);

	QPixmap endBackgroundPixmap("./images/MenuBg.png");
	end_m_background = new QGraphicsPixmapItem;
	end_m_background->setPixmap(endBackgroundPixmap);
	end_m_background->setScale(0.5);
	end_sce->addItem(end_m_background);

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

	animation = new QPropertyAnimation(player, "pos", this);
	animation->setDuration(750);
	animation->setLoopCount(1);
	animation->setEasingCurve(QEasingCurve::InOutExpo);
	connect(animation, &QPropertyAnimation::finished, this, &GameManager::weaponPosUpd);
	connect(player, &PlayerPiece::playerDeath, this, &GameManager::lose);

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

	pb_pause_end = new QPushButton("Exit");
	connect(pb_pause_end, &QPushButton::clicked, this, &GameManager::returnToMenu);
	pb_pause_end->setStyleSheet(style_sqr_pb);
	pb_pause_end->move(1000, 600);
	pb_pause_end->resize(100, 100);
	end_sce->addWidget(pb_pause_end);

	pb_restart_end = new QPushButton("Restart");
	connect(pb_restart_end, &QPushButton::clicked, this, &GameManager::restart);
	pb_restart_end->setStyleSheet(style_sqr_pb);
	pb_restart_end->move(1150, 600);
	pb_restart_end->resize(100, 100);
	end_sce->addWidget(pb_restart_end);
	
	QFont titleFont("fusion pixel proportional", 64, 100);
	lb_end = new QLabel();
	lb_end->setAlignment(Qt::AlignCenter);
	lb_end->move(320, 180);
	lb_end->setFont(titleFont);
	lb_end->resize(640, 360);
	lb_end->setStyleSheet("color:white;background-color: rgba(255, 255, 255, 10);");
	
	end_sce->addWidget(lb_end);

	QFont contFont("fusion pixel proportional", 16, 50);

	lb_hpnow = new QLabel();
	std::stringstream ss;
	ss << playerHp << " / " << playerHpmax;
	lb_hpnow->setText(ss.str().c_str());
	ss.str(std::string());
	ss.clear();
	ss.flush();
	lb_hpnow->setFont(contFont);
	lb_hpnow->setStyleSheet("color:white;background-color: transparent;");
	lb_hpnow->resize(300, 50);
	lb_hpnow->move(100, 125);
	main_sce->addWidget(lb_hpnow);
	lb_atk = new QLabel();
	lb_atk->setFont(contFont);
	lb_atk->setNum(playerAtk);
	lb_atk->setStyleSheet("color:white;background-color: transparent;");
	lb_atk->resize(100, 50);
	lb_atk->move(100, 215);
	main_sce->addWidget(lb_atk);
	lb_def = new QLabel();
	lb_def->setFont(contFont);
	lb_def->setNum(playerDef);
	lb_def->resize(100, 50);
	lb_def->setStyleSheet("color:white;background-color: transparent;");
	lb_def->move(260, 215);
	main_sce->addWidget(lb_def);
	lb_dodge = new QLabel();
	lb_dodge->setFont(contFont);
	lb_dodge->setNum(playerDodge);
	lb_dodge->resize(100, 50);
	lb_dodge->setStyleSheet("color:white;background-color: transparent;");
	lb_dodge->move(100, 305);
	main_sce->addWidget(lb_dodge);
	lb_scAngle = new QLabel();
	lb_scAngle->setFont(contFont);
	lb_scAngle->resize(100, 50);
	lb_scAngle->setNum(playerScatterAngle);
	lb_scAngle->setStyleSheet("color:white;background-color: transparent;");
	lb_scAngle->move(100, 395);
	main_sce->addWidget(lb_scAngle);
	lb_bulletNum = new QLabel();
	lb_bulletNum->setFont(contFont);
	lb_bulletNum->setNum(playerBulletNum);
	lb_bulletNum->resize(100, 50);
	lb_bulletNum->setStyleSheet("color:white;background-color: transparent;");
	lb_bulletNum->move(260, 395);
	main_sce->addWidget(lb_bulletNum);

	lb_level = new QLabel();
	lb_level->setFont(contFont);
	lb_level->setNum(level);
	lb_level->resize(100, 50);
	lb_level->setStyleSheet("color:white;background-color: transparent;");
	lb_level->move(1050, 125);
	main_sce->addWidget(lb_level);
	lb_expnow = new QLabel();
	ss << expnow << " / " << expneed;
	lb_expnow->setFont(contFont);
	lb_expnow->setText(ss.str().c_str());
	lb_expnow->resize(250, 50);
	lb_expnow->setStyleSheet("color:white;background-color: transparent;");
	lb_expnow->move(1050, 215);
	main_sce->addWidget(lb_expnow);
	ss.str(std::string());
	ss.clear();
	ss.flush();
	lb_killCounter = new QLabel();
	lb_killCounter->setFont(contFont);
	lb_killCounter->setNum(killCounter);
	lb_killCounter->resize(100, 50);
	lb_killCounter->setStyleSheet("color:white;background-color: transparent;");
	lb_killCounter->move(1050, 305);
	main_sce->addWidget(lb_killCounter);
	lb_diff = new QLabel();
	lb_diff->setFont(contFont);
	lb_diff->setNum(difficulty);
	lb_diff->setStyleSheet("color:white;background-color: transparent;");
	lb_diff->move(1050, 395);
	main_sce->addWidget(lb_diff);

	connect(player, &PlayerPiece::playerHurt, this, [=]() {setHpPrinter(); });

	weapon = new Shotgun(player, main_sce, this);
	weapon->updatePos();
	weapon->setGraphicsEffect(effHurted);
	main_sce->addItem(weapon);

	RoundTime = difficulty > 1 ? 6 : 8;

	/*
	chessboard[0][0] = new BotBase(100, 2, 1500, this);
	chessboard[0][0]->setXY(0, 0);
	chessboard[0][0]->setPos(390, 138);
	connect(chessboard[0][0], &BotBase::botDeath, this, &GameManager::enemyDeathProcess);
	main_sce->addItem(chessboard[0][0]);
	*/
}

void GameManager::enemyDeathProcess(const int& expWhenDie, int x, int y) {
	killCounter++;
	expGet(expWhenDie);
	setAllPrinter();
	chessboard[x][y] = nullptr;
	if (killCounter % 10 == 0)
		enemyStrength++;
	if (killCounter >= 200) {
		win();
	}
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
	if (pesudoTime % RoundTime == 0) {
		moveRound();
		generateRound();
	}
	qDebug() << pesudoTime;
	pesudoTime++;
}

void GameManager::moveRound() {
	qDebug() << "moveRound";
	int y = 7;
	int x = 7;
	for (; y >= 0; y--) {
		for (x = 7; x >= 0; x--) {
			if (chessboard[x][y] != nullptr) {
				qDebug() << "enemy" << x << ' ' << y;
				BotBase*& enemy = chessboard[x][y];
				if (enemy->attackableCheck()) {
					qreal damage = enemy->attack(player->pos());
					playerHp -= (damage - playerDef)>0? (damage - playerDef):0;
					player->hurt(damage - playerDef);
					if (playerHp <= 0) {
						player->death();
					}
					setHpPrinter();
				}
				else {
					//enemy->moveRound();
				}
			}
		}
	}
}

void GameManager::generateRound() {
	qDebug() << "generateRound";
	int enemySum = 1 + (difficulty > 3 ? 1 : 0) + (enemyStrength > 3 ? 1 : 0);
	int knightP = 0 + (enemyStrength > 0 ? 20 : 0);
	int kingP = 0 + (enemyStrength > 8 ? 20 : 0);
	int queenP = 0 + (enemyStrength > 5 ? 10 : 0);
	int rookP = 0 + (enemyStrength > 2 ? 10 : 0);
	int bishopP = 0 + (enemyStrength > 2 ? 20 : 0);
	while (enemySum--) {
		BotBase* ret = nullptr;
		int randomResult = QRandomGenerator::global()->bounded(1, 100);
		bool generated = 0;
		randomResult -= knightP;
		if (randomResult <= 0 && !generated) { ret = enemyGenerate(1); generated = 1; }
		randomResult -= rookP;
		if (randomResult <= 0 && !generated) { ret = enemyGenerate(2); generated = 1; }
		randomResult -= bishopP;
		if (randomResult <= 0 && !generated) { ret = enemyGenerate(3); generated = 1; }
		randomResult -= queenP;
		if (randomResult <= 0 && !generated) { ret = enemyGenerate(4); generated = 1; }
		randomResult -= kingP;
		if (randomResult <= 0 && !generated) { ret = enemyGenerate(5); generated = 1; }
		if (!generated) ret = enemyGenerate(0);

		qDebug() << "generate a bot" << hex << unsigned(ret);
		QVector<int> vec{0, 1, 2, 3, 4, 5, 6, 7};
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::shuffle(vec.begin(), vec.end(), std::default_random_engine(seed));
		qDebug() << vec;
		for (size_t i = 0; i < 8; i++)
		{
			if (playerx == vec[i] && playery == 0)
				continue;
			BotBase*& tar = chessboard[vec[i]][0];
			if (tar == nullptr) {
				ret->setXY(vec[i], 0);
				tar = ret;
				tar->setPos(390+vec[i]*62.5, 138);
				connect(tar, &BotBase::botDeath, this, &GameManager::enemyDeathProcess);
				qDebug() << "enemy generated at" << vec[i] << ' ' << 0;
				main_sce->addItem(tar);
				break;
			}
		}
	}
	return;
}

BotBase* GameManager::enemyGenerate(const int& kind) {
	qreal baseHp = (difficulty>3?15:(difficulty*5)) + enemyStrength * 15;
	qreal baseAtk = difficulty * 2 + enemyStrength * 4;
	qreal baseExpGiven = 5 + (enemyStrength) * 5;
	BotBase* ret = nullptr;
	switch (kind)
	{
	case 0:
		ret = new BotBase(baseHp, baseAtk, baseExpGiven);
		break;
	case 1:
		ret = new BotBase(baseHp*1.5, baseAtk, baseExpGiven*1.5);
		break;
	case 2:
		ret = new BotBase(baseHp*2, baseAtk*0.5, baseExpGiven*1.5);
		break;
	case 3:
		ret = new BotBase(baseHp*0.2, baseAtk*2, baseExpGiven*1.5);
		break;
	case 4:
		ret = new BotBase(baseHp*0.8, baseAtk*1.2, baseExpGiven*3);
		break;
	case 5:
		ret = new BotBase(baseHp*5, baseAtk*2, baseExpGiven*5);
		break;
	}
	return ret;
}

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
			if (chessboard[newX][newY] != nullptr) {
				chessboard[newX][newY]->hurt(99999);
			}
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
	// chessboard[0][0]->attack(event->pos());
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
	qDebug() << "playerMove";
	animation->setStartValue(player->pos());
	targKeeper = QPointF(403 + 62.5 * newX, 125 + 62.5 * newY);
	animation->setEndValue(targKeeper);
	weapon->hide();
	animation->start();
	fireFlag = 1;
	fireTimer->start(750);
	// player->setPos(403 + 62.5 * newX, 125 + 62.5 * newY);
	playerx = newX, playery = newY;
	return;
}

void GameManager::fireCd() {
	fireFlag = 0;
	effHurted->setStrength(0);
}

void GameManager::win() {
	lb_end->setText("You Win!");
	setScene(end_sce);
}

void GameManager::lose() {
	lb_end->setText("You Lose!");
	setScene(end_sce);
}