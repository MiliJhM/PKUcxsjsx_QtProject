#include "Shotgun.h"

Shotgun::Shotgun(PlayerPiece* pl, QGraphicsScene* scene, QObject* parent) : QObject{ parent }, ptr_player(pl), sce(scene)
{
	px = new QPixmap("./Images/Shotgun.png");
	QImage img = QImage("./Images/Shotgun.png");
	
	px_rotated = new QPixmap;
	*px_rotated = QPixmap::fromImage(img.mirrored(0, 1));
	setPixmap(*px);
	setScale(0.075);
	
	sfxFire = new QSoundEffect(this);
	sfxFire->setSource(QUrl::fromLocalFile("./Sounds/Fire.wav"));
	sfxFire->setVolume(0.3);

}

void Shotgun::updatePos() {
	double dx = ptr_player->pos().x() + 20;
	double dy = ptr_player->pos().y() + 35;
	setPos(dx, dy);
	return;
}

void Shotgun::rotateToCursor(const QPointF& target) {
	QPointF weaponPos = mapToScene(transformOriginPoint());
	double dx = target.x() - weaponPos.x() - 15;
	double dy = target.y() - weaponPos.y() - 15;
	if (dx >= 0) {
		setRotation(-qRadiansToDegrees(qAtan2(dx, dy)) + 90);
		setPixmap(*px);
	}
	else {
		setRotation(-qRadiansToDegrees(qAtan2(dx, dy)) + 90);
		setPixmap(*px_rotated);
	}
	return;
}

void Shotgun::fire(qreal damage, const QPointF& target, int bulletcnt, int penetration, qreal spread) {
	sfxFire->play();
	for (int i = 0; i < bulletcnt; ++i) {
		Bullet* bullet = new Bullet(pos(), rotation(), damage, penetration, sce, parent());
		bullet->setRotation(bullet->rotation() + (QRandomGenerator::global()->bounded((int)(-spread * 5), (int)(spread * 5)) * 0.1));
		bullet->setParentItem(parentItem());
		bullet->setScale(3);
		sce->addItem(bullet);
	}
}