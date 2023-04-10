#include "Player.h"

Player::Player()
{
	x = 0;
	y = 0;
	sprite = 'X';
}

Player::Player(int x, int y, char sprite)
{
	// -> = * + .
	this->x = x;
	this->y = y;
	this->sprite = sprite;
}

void Player::setCoord(Coord c)
{
	this->x = c.x;
	this->y = c.y;
}

Coord Player::getCoord()
{
	Coord c;
	c.x = this->x;
	c.y = this->y;
	return c;
}

char Player::getSprite()
{
	return this->sprite;
}