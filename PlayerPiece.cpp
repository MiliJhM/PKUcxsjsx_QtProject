#include "PlayerPiece.h"

PlayerPiece::PlayerPiece(QObject *parent)
	: QObject(parent)
{
	QPixmap* playerPng = new QPixmap("./Images/PlayerPiece.png");
	setPixmap(*playerPng);

	sfxHurted = new QSoundEffect(this);
	sfxHurted->setSource(QUrl::fromLocalFile("./Sounds/HurtPlayer.wav"));
	sfxHurted->setVolume(0.5);
}

