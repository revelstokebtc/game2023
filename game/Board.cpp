#include "Board.h"

#include <iostream>

Board::Board() {
    this->width = 20;
    this->height = 10;
    initScreen();
}

Board::Board(int width, int height)
{
    this->width = width;
    this->height = height;
    initScreen();
}

void Board::draw()
{
    // add player drawing
    screen[this->player->getCoord().x][this->player->getCoord().y] = this->player->getSprite();
    system("cls");
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            std::cout << screen[x][y];
        }
        std::cout << "\n";
    }
    for (int x = 0; x < width; x++) {
        std::cout << ground;
    }
    // reset player space
    screen[this->player->getCoord().x][this->player->getCoord().y] = ' ';
}

void Board::initScreen()
{
    for (int x = 0; x < width; x++) {
        std::vector<char> column;
        for (int y = 0; y < height; y++) {
            column.push_back(' ');
        }
        screen.push_back(column);
    }
}
