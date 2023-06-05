// game.cpp : This file contains the 'main' function. 
// Program execution begins and ends there.
//

#include <ShlObj.h>
#include <fstream>
#include <iostream>
#include <conio.h>
#include <chrono>
#include <thread>
#include "windows.h"
#include "Board.h"
#include "Player.h"
#include "Constants.h"

enum PlayerAction { NONE, JUMP, MOVE_RIGHT, MOVE_LEFT, SAVE, LOAD };

char input() {
    if (_kbhit()) {
        return _getch();
    }
    else {
        return 0;
    }
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
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);

    Board board(SCREEN_WIDTH, SCREEN_HEIGHT);
    Player player(CHARACTER_START_X, CHARACTER_START_Y, CHARACTER_KEY);

    board.player = &player;

    std::cout << "Welcome to our game!\n";
    char userInput;
    PlayerAction action = NONE;

    std::chrono::milliseconds frameDuration(FRAME_DURATION);

    do
    {
        auto frameStart = std::chrono::high_resolution_clock::now();

        // input ////////////////////////////////////////
        userInput = input();
        if (userInput != 0) {
            switch (userInput) {
            case JUMP_KEY:
                action = JUMP;
                break;
            case RIGHT_KEY:
                action = MOVE_RIGHT;
                break;
            case LEFT_KEY:
                action = MOVE_LEFT;
                break;
            case SAVE_KEY:
                action = SAVE;
                break;
            case LOAD_KEY:
                action = LOAD;
                break;
            default:
                action = NONE;
                break;
            }
        }
        else {
            action = NONE;
        }

        // logic ////////////////////////////////////////
        switch (action) {
        case JUMP:
            // @todo: only if on ground
            player.jump();
            break;
        case MOVE_RIGHT:
            // @todo: check right boundary
            player.vx = 1;
            break;
        case MOVE_LEFT:
            // @todo: check left boundary
            player.vx = -1;
            break;
        case SAVE:
            save(board, player);
            break;
        case LOAD:
            load();
            break;
        case NONE:
        default:
            break;
        }

        // Gravity and movement
        player.addGravity();
        player.updatePosition();

        // reset horizontal velocity
        player.vx = 0;

        // draw ////////////////////////////////////////
        board.draw();

        auto frameEnd = std::chrono::high_resolution_clock::now();

        // Calculate how long this frame took
        auto frameTime = std::chrono::duration_cast<std::chrono::milliseconds>(frameEnd - frameStart);

        // If the frame finished quicker than frameDuration, sleep for the remaining time
        if (frameTime < frameDuration)
        {
            std::this_thread::sleep_for(frameDuration - frameTime);
        }

        if (userInput == QUIT_KEY)
        {
            break;
        }
    } while (true);
    std::cout << "\nGame Over!\n";
    system("pause");
}