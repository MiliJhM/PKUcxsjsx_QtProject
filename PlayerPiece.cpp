#include "PlayerPiece.h"

PlayerPiece::PlayerPiece(QObject *parent)
	: QObject(parent)
{
	QPixmap* playerPng = new QPixmap("./Images/PlayerPiece.png");
	setPixmap(*playerPng);
	hurtTimer = new QTimer(this);
	connect(hurtTimer, &QTimer::timeout, this, &PlayerPiece::endHurt);
	sfxHurted = new QSoundEffect(this);
	sfxHurted->setSource(QUrl::fromLocalFile("./Sounds/HurtPlayer.wav"));
	sfxHurted->setVolume(0.5);
	effHurt = new QGraphicsColorizeEffect(this);
	effHurt->setColor(QColor(192, 0, 0));
	effHurt->setStrength(0);
	// setGraphicsEffect(effHurt);
}

void PlayerPiece::hurt(qreal damage) {
	sfxHurted->play();
	effHurt->setStrength(0.8);
	hurtTimer->start(50);
	emit playerHurt();
}

void PlayerPiece::endHurt() {
	effHurt->setStrength(0);
}

void PlayerPiece::death() {
	emit playerDeath();
}