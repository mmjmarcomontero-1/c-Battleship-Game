/************************************************************
 * AUTHOR       : Marco Montero Justiniano
 * Assignment   : Final Project – Battleship
 * CLASS        : CS002 – Pasadena City College
 * DUE DATE     : December 4, 2025
 ************************************************************/
/************************************************************
 * BATTLESHIP PROGRAM
 * __________________________________________________________
 * This program simulates the classic Battleship board game.
 * It allows:
 *   1) Player vs Player
 *   2) Player vs CPU (Random)
 *   3) Player vs CPU (Smart / Intelligent search)
 *
 * The program uses:
 *   - Structs (Point, Ship, PlayerBoard)
 *   - 2D arrays for player boards
 *   - Vectors to store ship positions
 *   - Global constants for fleet configuration
 *   - Functions for ship placement, validation, attack logic,
 *     hit/miss processing, CPU AI behavior, and win detection.
 *
 * __________________________________________________________
 * INPUT:
 *   • User-entered coordinates for ship placement.
 *   • Attack coordinates (A5, B7, etc.)
 *   • Menu selection for game mode.
 *
 * OUTPUT:
 *   • Two side-by-side 10×10 game boards.
 *   • Ship placement visualization.
 *   • Hit/Miss messages.
 *   • “Ship Sunk” notifications.
 *   • Winner announcement for human or CPU.
 ************************************************************/


/************************************************************
 * FUNCTION DEFINITIONS
 ************************************************************/


/************************************************************
 * displayBoards
 * ----------------------------------------------------------
 * Displays the Player board and Enemy board side-by-side.
 * Shows:
 *   - Board labels A–J
 *   - Columns 1–10
 *   - Contents (ships, hits, misses)
 ************************************************************/
#ifndef HEADER_H
#define HEADER_H
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


const int FLEET_SIZE=5;

struct Point{
    int row;
    int col;
};

struct Ship{

    string name;
    int size;
    int hitcount;
    vector<Point> positions;
};

struct PlayerBoard{

    char board[10][10];
    Ship fleet[FLEET_SIZE];
};

void displayBoards(char P[][10],char E[][10]);

void initFleet(PlayerBoard& pb);

bool spaceOcupied(PlayerBoard& pb,int row,int col,char orientation,int size);


void getValidshipInfo(int& row,int& col,char& orientation,PlayerBoard& pb,int shipIndex);

void placeShip(PlayerBoard& pb,int shipIndex);


void boardSetup(PlayerBoard& p1, PlayerBoard& p2);

bool attack(PlayerBoard& attacker,PlayerBoard& defender);

bool checkWinner(PlayerBoard& p1, PlayerBoard& p2);

void playGame(PlayerBoard& p1,PlayerBoard& p2);

void boardSetupCPU(PlayerBoard& cpu);

bool cpuAttack(PlayerBoard& cpu, PlayerBoard& human);

void playGameCPU(PlayerBoard& human, PlayerBoard& cpu);

bool cpuAttackSmart(PlayerBoard& cpu, PlayerBoard& human,vector<Point>& targets, vector<Point>& frontier);

void playGameSmartCPU(PlayerBoard& human, PlayerBoard& cpu);

#endif // HEADER_H
