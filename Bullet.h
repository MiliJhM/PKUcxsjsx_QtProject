#pragma once


#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QTimer>
#include <QList>

#include"BotBase.h"
class Bullet : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

public:
	Bullet(QPointF pos, qreal angle, qreal damage, int penetration, QGraphicsScene* scene, QObject* parent = nullptr);
	static QTimer* bulletTimerStatic;
protected:
	void enemyHitCheck();
	void move();

	QGraphicsScene* ptr_sce;
	qreal damage;
	int penetration;
	int hurtcount;
	QList<BotBase*> hitted;
};

