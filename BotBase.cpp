#include "BotBase.h"

QSoundEffect* BotBase::sfxEnemyHurt = nullptr;

BotBase::BotBase(int x, int y, qreal hpmax, qreal atk, qreal expgiven, QObject* parent) : posx(x), posy(y), hpmax(hpmax), hp(hpmax), atk(atk), expWhenDie(expgiven), QObject{ parent } {
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
	QPointF nowPos = pos(), posDist;
	posDist = targ - nowPos;
	QTimer timer;
	int cnt=0;
	while (cnt<10) {
		if (timer.isActive()) {
			continue;
		}
		cnt++;
		timer.start(10 / cnt);
		moveBy(posDist.x()/10, posDist.y() / 10);
	}
	cnt = 0;
	while (cnt < 10) {
		if (timer.isActive()) {
			continue;
		}
		cnt++;
		timer.start(10 / cnt);
		moveBy(( - posDist.x()) / 10, (-posDist.y()) / 10);
	}
	return atk;
}

void BotBase::endHurt() {
	effHurted->setStrength(0);
}