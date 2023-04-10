// game.cpp : This file contains the 'main' function. 
// Program execution begins and ends there.
//

#include <ShlObj.h>
#include <fstream>
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
char const SAVE_KEY = 'e';
char const LOAD_KEY = 'r';
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

std::string getSaveFilePath() {
    WCHAR profilePath[MAX_PATH];
    std::string filePath = "C:";
    HRESULT result = SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, profilePath);
    if (SUCCEEDED(result)) {
        std::wstring ws(profilePath);
        std::string str(ws.begin(), ws.end());
        filePath = str + "\\AppData\\Roaming\\CS132Game";
    }
    return filePath;
}

void load() {
    std::ifstream saveFile;
    saveFile.open(getSaveFilePath() + "\\save.txt");

    std::string line;
    system("cls");
    int i = 0, j = 0;
    std::vector<Coord> coordinates;
    Coord c;
    while (std::getline(saveFile, line, '\t')) {
        // get board state
        if (i <= SCREEN_HEIGHT) {
            std::cout << line << '\n';
            i++;
            //continue;
        }

        // get game state
        if (j++ == 2) {
            c.x = std::stoi(line);
        } else if (j++ == 4) {
            c.y = stoi(line);
            j = 0;
            coordinates.push_back(c);
        }
        else {
            j++;
        }
    }

    system("pause");

    saveFile.close();
}

bool save(Board b, Player p) {
    std::ofstream saveFile;
    saveFile.open(getSaveFilePath() + "\\save.txt");
    // save board state
    saveFile << b.getBoard() << '\n';

    // save player coordinates
    saveFile << "Player Coordinates: \t";
    saveFile << "x\t" << p.getCoord().x << '\t';
    saveFile << "y\t" << p.getCoord().y << '\n';
    saveFile << "Player Coordinates: \t";
    saveFile << "x\t" << p.getCoord().x << '\t';
    saveFile << "y\t" << p.getCoord().y << '\n';
    saveFile << "Player Coordinates: \t";
    saveFile << "x\t" << p.getCoord().x << '\t';
    saveFile << "y\t" << p.getCoord().y << '\n';


    saveFile.close();

    return true;
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
        else if (userInput == SAVE_KEY) {
            save(board, player);
        }
        else if (userInput == LOAD_KEY) {
            load();
        }
        player.setCoord(playerCoord);
        logic();

        // draw ////////////////////////////////////////
        board.draw();

    } while (!_kbhit() && userInput != QUIT_KEY);
    std::cout << "\nGame Over!\n";
    system("pause");
}