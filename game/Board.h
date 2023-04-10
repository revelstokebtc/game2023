#pragma once

#include <vector>
#include "Player.h"

class Board
{
public:
	// constructor
	Board();
	Board(int width, int height);

	// class properties
	char ground = '~';

	// class methods
	void draw();

	// pointer to player
	Player* player;

private:
	int width;
	int height;
	std::vector<std::vector<char>> screen;
	void initScreen();
};

