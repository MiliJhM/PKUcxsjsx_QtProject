#pragma once
#pragma once

#include <QObject>
#include <QVector2D>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QFont>
#include <QPixmap>
#include <QTimer>
#include <QMovie>
#include <QSoundEffect>
#include <QUrl>
#include <QGraphicsEffect>
#include <QPropertyAnimation>
class BotBase : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT
	Q_PROPERTY(QPointF pos READ pos WRITE setPos)

public:
	BotBase(qreal hpmax, qreal atk, qreal expgiven, QObject* parent=nullptr);
	void setXY(int x, int y);
	bool attackableCheck();
	qreal attack(const QPointF& targ);
	void moveRound();
	void moveToEffect(int x, int y);
	void hurt(qreal damage);
	void endHurt();
	void resetPos();
	static QSoundEffect* sfxEnemyHurt;
	QGraphicsColorizeEffect *effHurted;
	QTimer* hurtTimer;
	QPropertyAnimation* animation;

protected:
	QPointF posKeeper;
	qreal hpmax;
	qreal hp;
	qreal atk;
	int expWhenDie;
	QPixmap pic;
	int posx;
	int posy;



signals:
	void botDeath(const int& expWhenDie, int x, int y);
};

