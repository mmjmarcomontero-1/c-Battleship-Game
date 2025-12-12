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
#include "header.h"


int main()
{
    PlayerBoard p1, p2;

    cout << "================ BATTLESHIP ================" << endl;
    cout << "Select game mode:\n";
    cout << "1. Player vs Player\n";
    cout << "2. Player vs Computer (Random)\n";
    cout << "3. Player vs Computer (Smart AI)\n";
    cout << "Choose an option: ";

    int option;
    cin >> option;

    if (option == 1)
    {
        // PvP mode
        initFleet(p1);
        initFleet(p2);
        boardSetup(p1, p2);
        playGame(p1, p2);
    }
    else if (option == 2)
    {
        // PvCPU (random)
        initFleet(p1);
        initFleet(p2);

        boardSetup(p1, p2);        // p1 places manually, CPU places randomly

        playGameCPU(p1, p2);       // CPU random attacks
    }
    else if (option == 3)
    {
        // PvCPU (intelligent)
        initFleet(p1);
        initFleet(p2);

        boardSetup(p1, p2);        // p1 places manually, CPU places intelligently
        playGameSmartCPU(p1, p2);
    }
    else
    {
        cout << "Invalid option. Exiting...\n";
    }

    return 0;
}
