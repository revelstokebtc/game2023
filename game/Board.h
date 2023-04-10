#pragma once

#include <vector>
#include <string>
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
	std::string getBoard();

	// pointer to player
	Player* player;

private:
	int width;
	int height;
	std::vector<std::vector<char>> screen;
	void initScreen();
};

