// game.cpp : This file contains the 'main' function. 
// Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include "Board.h"
#include "Player.h"

// framerate
// screen refresh (clear screen)
// user controls

char const QUIT_KEY = 'q';
char const JUMP_KEY = ' ';
char const RIGHT_KEY = 'd';
char const LEFT_KEY = 'a';
char const CHARACTER_KEY = '#';
int const SCREEN_HEIGHT = 15;
int const SCREEN_WIDTH = 40;
int const CHARACTER_START_X = 0;
int const CHARACTER_START_Y = SCREEN_HEIGHT-1;

char input() {
    return _getch();
}

void logic() {

}

int main()
{
    Board board(SCREEN_WIDTH, SCREEN_HEIGHT);
    Player player(CHARACTER_START_X, CHARACTER_START_Y, CHARACTER_KEY);
    // @todo: change coordinate system to velocity
    Coord playerCoord;

    board.player = &player;

    std::cout << "Welcome to our game!\n";
    char userInput;
    do
    {
        // input ////////////////////////////////////////
        userInput = input();

        // logic ////////////////////////////////////////
        playerCoord = player.getCoord();
        if (userInput == JUMP_KEY) {
            // @todo: only if on ground
            playerCoord.y--;
        }
        else if (userInput == RIGHT_KEY) {
            // @todo: check right boundary
            playerCoord.x++;
        }
        else if (userInput == LEFT_KEY) {
            // @todo: check left boundary
            playerCoord.x--;
        }
        player.setCoord(playerCoord);
        logic();

        // draw ////////////////////////////////////////
        board.draw();

    } while (!_kbhit() && userInput != QUIT_KEY);
    std::cout << "\nGame Over!\n";
    system("pause");
}