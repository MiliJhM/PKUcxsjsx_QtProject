#include "Bullet.h"
#include<QtMath>

QTimer* Bullet::bulletTimerStatic = nullptr;

Bullet::Bullet(QPointF pos, qreal angle, qreal damage, int penetration, QGraphicsScene* scene, QObject* parent) : damage(damage), penetration(penetration), ptr_sce(scene),hurtcount(0), QObject{ parent }
{
	QPixmap* Png = new QPixmap("./Images/Bullet.png");
	setPixmap(*Png);
	setPos(pos);
	setRotation(angle);
	connect(bulletTimerStatic, &QTimer::timeout, this, [=](){enemyHitCheck(); move(); });
	ptr_sce->addItem(this);
}

void Bullet::enemyHitCheck() {
	QList<QGraphicsItem*> collid = this->collidingItems();
	for (QGraphicsItem* it : collid) {
		BotBase* enemy = dynamic_cast<BotBase*>(it);
		if (enemy==nullptr) continue;
		bool state = 0;
		for (auto p : hitted) {
			if (p == enemy) state = 1;
		}
		if (state) return;

		enemy->hurt(damage);
		hitted.append(enemy);
		hurtcount++;
		if (hurtcount >= penetration) {
			ptr_sce->removeItem(this);
			deleteLater();
		}
	}
}

void Bullet::move() {
	qreal angle = rotation();
	qreal rad = qDegreesToRadians(angle);
	qreal dis = 10;
	qreal dy = dis * qSin(rad);
	qreal dx = dis * qCos(rad);

	moveBy(dx, dy);
	if (pos().x() < 390 || pos().x() > 890 || pos().y() < 140 || pos().y() > 640) {
		ptr_sce->removeItem(this);
		deleteLater();
	}
}