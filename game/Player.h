#pragma once
#include "Coord.h";

class Player
{
public:
	Player(int x, int y, char sprite) : vx(0), vy(0), x(x), y(y), sprite(sprite) {};
	char getSprite();
	Coord getCoord();
	void setCoord(Coord);

	// New Methods
	void jump();
	void addGravity();
	void updatePosition();
	bool onGround();

	// Velocity
	double vx, vy;

	// Position
	int x, y;

private:
	char sprite;
};

