#include "BotBase.h"

QSoundEffect* BotBase::sfxEnemyHurt = nullptr;

BotBase::BotBase(qreal hpmax, qreal atk, qreal expgiven, QObject* parent) : hpmax(hpmax), hp(hpmax), atk(atk), expWhenDie(expgiven), QObject{ parent } {
	animation = new QPropertyAnimation(this, "pos", parent);
	animation->setDuration(750);
	animation->setLoopCount(1);
	connect(animation, &QPropertyAnimation::finished, this, [=]() {resetPos(); });
	hurtTimer = new QTimer(this);
	connect(hurtTimer, &QTimer::timeout, this, [=]() {endHurt(); });
	effHurted = new QGraphicsColorizeEffect(this);
	effHurted->setColor(QColor(192, 0, 0));
	effHurted->setStrength(0);
	pic = QPixmap("./Images/BotPawn.png");
	setPixmap(pic);
	setScale(0.39);
	setGraphicsEffect(effHurted);
	return;
}

void BotBase::setXY(int x, int y) {
	posx = x;
	posy = y;
	return;
}

bool BotBase::attackableCheck() {
	return true;
}

void BotBase::hurt(qreal damage) {
	if (hp <= 0)
		return;
	hp -= damage;
	sfxEnemyHurt->play();
	effHurted->setStrength(0.8);
	hurtTimer->start(50);
	if (hp <= 0) {
		emit botDeath(expWhenDie, posx, posy);
		qDebug() << "bot died at " << posx << ',' << posy;
		deleteLater();
	}
}

qreal BotBase::attack(const QPointF& targ) {
	qDebug() << "attack" << targ;
	animation->setStartValue(pos());
	posKeeper = pos();
	animation->setEndValue(targ);
	animation->setEasingCurve(QEasingCurve::InExpo);
	animation->start();
	return atk;
}

void BotBase::resetPos() {
	animation->setStartValue(pos());
	animation->setEndValue(posKeeper);
	animation->setEasingCurve(QEasingCurve::OutExpo);
	animation->start();
}

void BotBase::endHurt() {
	effHurted->setStrength(0);
}

void BotBase::moveToEffect(int x, int y) {
	animation->setStartValue(pos());
	animation->setEndValue(QPointF(390 + x * 62.5, 138+y*62.5));
	animation->start();
	setXY(x, y);
}