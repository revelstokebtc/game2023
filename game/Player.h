#pragma once
#include "Coord.h";

class Player
{
public:
	Player();
	Player(int x, int y, char sprite);
	char getSprite();
	Coord getCoord();
	void setCoord(Coord);

private:
	char sprite;
	int x;
	int y;
};

