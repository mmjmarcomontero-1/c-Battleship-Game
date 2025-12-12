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


void displayBoards(char P[][10],char E[][10]){


    cout <<"                Your board" << setw(56)<< "Enemy board\n";
    cout << "\n";

    // ----------------- TOP NUMBERS PLAYER -----------------
    for(int j=1;j<=10;j++){

        cout << setw(4)<< j;
    }
    //Space between the Player board and enemy board
    cout << setw(14) << " ";

    // ----------------- TOP NUMBERS ENEMY -----------------

    for(int i=1;i<=10;i++){

        cout << setw(4) << i;
    }

    //ENDL
    cout << endl;



    //DASH LINE
    cout << "  ";
    for(int i=0;i<41;i++){
        cout <<"-";
    }
    cout << setw(12)<< "  ";
    for(int i=0;i<41;i++){

        cout << "-";

    }
    cout << endl;


    //---------------- Rows A-J ----------------
    //Player board
    for(int i=0;i<10;i++){

        char letter='A'+i;

        cout <<letter << " |";
        for(int j=0;j<10;j++){

            cout << " " << P[i][j]<< " |";
        }

        cout << setw(10) << " ";

        //Enemy board

        cout << letter << " |";
        for (int j = 0; j < 10; j++)
        {
            char cell = E[i][j];

            // Show only hits and misses
            if (cell == 'X' || cell == '0')
                cout << " " << cell << " |";
            else
                cout << "   |";  // hide ships
        }
        cout << endl;


        cout << "   ";
        for(int k=0;k<40;k++){
            cout <<"-";
        }
        cout << setw(11)<< " ";
        for(int h=0;h<42;h++){

            cout << "-";
        }
        cout << endl;
    }
}





//----------------Init fleet functions----------------
void initFleet(PlayerBoard& pb){

    int row;
    int col;
    for(row=0;row<10;row++){
        for(col=0;col<10;col++){
            pb.board[row][col]=' ';

        }

    }

    //Battle Ship Names
    pb.fleet[0].name="Carrier";
    pb.fleet[0].size=5;
    pb.fleet[0].hitcount=0;


    pb.fleet[1].name="Battleship";
    pb.fleet[1].size=4;
    pb.fleet[1].hitcount=0;

    pb.fleet[2].name="Cruiser";
    pb.fleet[2].size=4;
    pb.fleet[2].hitcount=0;

    pb.fleet[3].name="Submarine";
    pb.fleet[3].size=3;
    pb.fleet[3].hitcount=0;

    pb.fleet[4].name="Destroyer";
    pb.fleet[4].size=2;
    pb.fleet[4].hitcount=0;
}





//--------------------  Space Ocupied function  --------------------
bool spaceOcupied(PlayerBoard& pb,int row,int col,char orientation,int size){

    // If the ship is placed horizontally,checks cells to the right
    if(orientation=='H'){

        // Loop over the length of the ship
        for(int i=0;i<size;i++){

            // If any position is not empty, placement is invalid
            if(pb.board[row][col+i]!=' ')
                return true;

        }
    }
    else // orientation == 'V'
    {
        // Loop downward vertically through required cells
        for(int i=0;i<size;i++)
        {

            // If ANY of these cells is occupied, placement cannot happen
            if(pb.board[row+i][col]!=' '){
                return true;
            }
        }
    }
    // If the loop ends with no conflicts → the space is free

    return false;
}





void getValidshipInfo(int& row,int& col,char& orientation,PlayerBoard& pb,int shipIndex){

        char letter;
        int number;
        bool valid=false;

        // Loop until a valid placement is received
        while(!valid){



            cout << pb.fleet[shipIndex].name << " size " << pb.fleet[shipIndex].size << endl;



            // ------------------- INPUT COORDINATES -------------------

            cout << "Enter starting coordinate   — Letter first, Number after): ";
            cin >> letter >> number;
            // Convert letter to uppercase
            letter=toupper(letter);

            // Convert 'A'–'J' to 0–9
            row=letter-'A';


            // Convert 1–10 to 0–9
            col=number-1;

            cout << "Orientation: ";
            cin >> orientation;
            orientation=toupper(orientation);


            // ------------------- ERROR CHECKS -------------------
            if(row<0 || row>9 || col<0|| col>9){

                cout << "Invalid coordinate,try again " << endl;
                continue;
            }

            // Must be H or V
            if(orientation!='H' && orientation!='V'){

                cout << "Invalid orientation,use H or V" << endl;
                continue;
            }

            // Check fit inside board
            int size=pb.fleet[shipIndex].size;

            if(orientation=='H' && col+size>10){

                cout << "Error Ship doesn't fit horizontally,try again" << endl;
                continue;
            }
            if(orientation=='V' && row+size>10){

                cout << "Ship doesn't fit vertically,try again" << endl;
                continue;
            }

            // Overlap check
            if(spaceOcupied(pb,row,col,orientation,size)){

                cout << "Space is ocupied" << endl;
                continue;
            }
            // All checks passed ==> valid placement

            valid=true;
        }
    }





//---------- PlaceShip Funct ----------`
void placeShip(PlayerBoard& pb,int shipIndex){

    int row,col;
    char orientation;

    // Get validated coordinates from the user
    getValidshipInfo(row, col, orientation, pb, shipIndex);


    // Reference the correct ship in the fleet
    Ship& s=pb.fleet[shipIndex];



    // Horizontal placement
    if(orientation=='H'){
        for(int o=0;o<s.size;o++){


            // Place ship letter
            pb.board[row][col+o]=s.name[0];


            // Store the exact cell this ship occupies
            Point p;
            p.row=row;
            p.col=col+o;
            s.positions.push_back(p);
        }
    }
    // Vertical placement
    else{
        for(int c=0;c<s.size;c++){

            pb.board[row+c][col]=s.name[0];

            Point p;
            p.row=row+c;
            p.col=col;
            s.positions.push_back(p);
        }
    }
}





void boardSetup(PlayerBoard& p1, PlayerBoard& p2)
{

    // ================================
    //  PLAYER 1: SHIP PLACEMENT PHASE
    // ================================
    cout << "======PLAYER 1 SETUP======" << endl;


    // Loop through all ships in the fleet
    for(int i=0;i<FLEET_SIZE;i++){

        placeShip(p1,i);

        cout << "\n>>> Player 1 has deployed: "
             << p1.fleet[i].name                        // Ask player 1 to place the current ship
             << " (" << p1.fleet[i].size << " cells)\n";
        cout << "----------------------------------------\n";

        displayBoards(p1.board, p2.board);

    }

    // ================================
    //  PLAYER 2: SHIP PLACEMENT PHASE
    // ================================
    cout << "======PLAYER 2 SETUP======" << endl;
    for(int i=0;i<FLEET_SIZE;i++){

        placeShip(p2,i);          // Ask player 2 to place their ship

        cout << "\n>>> Player 2 has deployed: " << p2.fleet[i].name
             << " (" << p2.fleet[i].size << " cells)\n";
        cout << "---------------------------------------------\n";

        displayBoards(p2.board, p1.board);

    }
}




//-----------Attack----------
bool attack(PlayerBoard& attacker,PlayerBoard& defender){

    char letter;
    int number;
    int row,col;
    bool valid=false;


    // Continue asking for coordinates until valid
        while(!valid){

            // Player enters a letter-number coordinate
            cout << "Enter a attack coordinate(e.g A5). ";
            cin>> letter>> number;


            if(!cin){
            cin.clear();
            cin.ignore(1000,'\n');
            cout << "Invalid coorfinte try again" << endl;
            continue;
            }


            // Convert input to row/col indices
            letter=toupper(letter);

            row=letter-'A';

            col=number-1;

            //Check Boundaries
            if(row<0 || row>9 || col<0 || col>9){

                cout << "Invalid coordinate,try again." <<endl;
                continue;
            }
            // Check if already attacked
            if(attacker.board[row][col]=='X' || attacker.board[row][col]=='0'){

                cout << "You already attack there,try another place" << endl;;
                continue;
            }
            valid=true;
    }

        if(defender.board[row][col]!=' '){


            cout << "HIT\n";

            char shipLetter= defender.board[row][col];
            attacker.board[row][col]='X';
            defender.board[row][col]='X';

            // Find which ship was hit
            for(int i=0;i<FLEET_SIZE;i++){
                if(defender.fleet[i].name[0]==shipLetter){

                    defender.fleet[i].hitcount++;

                if(defender.fleet[i].hitcount==defender.fleet[i].size){

                    // Ship destroyed
                    cout << "\n==========================================\n";
                    cout << "🔥  DIRECT HIT! Critical damage detected!\n";
                    cout << "YOU SUNKED THE BOAT: " << defender.fleet[i].name <<endl;
                    cout << "💥  Size: " << defender.fleet[i].size << " cells" << endl;
                    cout << "\n==========================================\n";

                }
                break;
            }

        }
        return true;
        }

    // ========= MISS ========= //
    cout << "MISS!\n";
    attacker.board[row][col] = '0';
    defender.board[row][col] = '0';
    return false;
}




//------------Check Winner----------
bool checkWinner(PlayerBoard& defender){

    for(int i=0;i<FLEET_SIZE;i++){

        if(defender.fleet[i].hitcount!=defender.fleet[i].size){

            return false;
        }

    }

    return true;
}





void playGame(PlayerBoard& p1, PlayerBoard& p2)
{
    bool gameOver = false;
    bool turnP1 = true;

    while (!gameOver)
    {
        if (turnP1)
        {
            cout << "========== PLAYER 1 TURN ==========\n";
            displayBoards(p1.board, p2.board);

            bool hit = attack(p1, p2);

            if (hit) cout << "(Player 1) HIT!\n";
            else     cout << "(Player 1) MISS!\n";

            if (checkWinner(p2))
            {
                cout << "\n🔥🔥 PLAYER 1 WINS THE GAME!! 🔥🔥\n";
                gameOver = true;
            }
        }
        else
        {
            cout << "========== PLAYER 2 TURN ==========\n";
            displayBoards(p2.board, p1.board);

            bool hit = attack(p2, p1);

            if (hit) cout << "(Player 2) HIT!\n";
            else     cout << "(Player 2) MISS!\n";

            if (checkWinner(p1))
            {
                cout << "\n🔥🔥 PLAYER 2 WINS THE GAME!! 🔥🔥\n";
                gameOver = true;
            }
        }

        turnP1 = !turnP1;   // cambia de turno
    }
}






void boardSetupCPU(PlayerBoard& cpu) {

    // Random seed so every game is different
    srand(time(nullptr));

    cout << "====== CPU IS PLACING ITS SHIPS ======\n";

    // Loop through all ships in the fleet
    for(int i = 0; i < FLEET_SIZE; i++) {

        bool placed = false;

        // Try until ship is placed
        while(!placed) {

            // 1. Generate random row/col
            int row = rand() % 10;       // random 0–9
            int col = rand() % 10;

            // 2. Random orientation
            char orientation = (rand() % 2 == 0 ? 'H' : 'V');

            int size = cpu.fleet[i].size;

            // 3. Check: does the ship fit?
            if(orientation == 'H' && col + size > 10) continue;
            if(orientation == 'V' && row + size > 10) continue;

            // 4. Check: space not occupied
            if(spaceOcupied(cpu, row, col, orientation, size)) continue;

            // 5. If all checks passed → place ship
            Ship& ship = cpu.fleet[i];

            if(orientation == 'H') {
                for(int j = 0; j < size; j++) {
                    cpu.board[row][col + j] = ship.name[0];

                    Point p;
                    p.row = row;
                    p.col = col + j;
                    ship.positions.push_back(p);
                }
            }
            else {
                for(int j = 0; j < size; j++) {
                    cpu.board[row + j][col] = ship.name[0];

                    Point p;
                    p.row = row + j;
                    p.col = col;
                    ship.positions.push_back(p);
                }
            }

            placed = true;   // success
        }
    }

    cout << "CPU finished placing ships.\n\n";
}







bool cpuAttack(PlayerBoard& cpu, PlayerBoard& human)
{
    int row, col;

    // Find a NEW valid target
    do {
        row = rand() % 10;
        col = rand() % 10;
    }
    while (cpu.board[row][col] == 'X' || cpu.board[row][col] == '0');
    // <-- uses cpu.board as CPU tracking board

    cout << "CPU attacks: " << char('A' + row) << (col + 1) << endl;

    // HIT
    if (human.board[row][col] != ' ')
    {
        char shipLetter = human.board[row][col];

        cpu.board[row][col]   = 'X';   // CPU's tracking board
        human.board[row][col] = 'X';   // Human loses a ship part

        for (int i = 0; i < FLEET_SIZE; i++)
        {
            if (human.fleet[i].name[0] == shipLetter)
            {
                human.fleet[i].hitcount++;

                if (human.fleet[i].hitcount == human.fleet[i].size)
                    cout << "CPU sunk your " << human.fleet[i].name << "!\n";

                break;
            }
        }

        return true;
    }

    // MISS
    cpu.board[row][col]   = '0';
    human.board[row][col] = '0';

    cout << "CPU MISS!\n";
    return false;
}







void playGameCPU(PlayerBoard& human, PlayerBoard& cpu)
{
    bool gameOver = false;

    while (!gameOver)
    {
        // --- PLAYER TURN ---
        cout << "\n========== PLAYER TURN ==========\n";
        displayBoards(human.board, cpu.board);

        bool hit = attack(human, cpu);
        cout << (hit ? "Player HIT!\n" : "Player MISS!\n");

        if (checkWinner(cpu))
        {
            cout << "\n🔥🔥 PLAYER WINS THE GAME! 🔥🔥\n";
            return;
        }

        // --- CPU TURN ---
        cout << "\n========== CPU TURN ==========\n";

        bool cpuHit = cpuAttack(cpu, human);
        cout << (cpuHit ? "CPU HIT!\n" : "CPU MISS!\n");

        if (checkWinner(human))
        {
            cout << "\n💀💀 CPU WINS THE GAME! 💀💀\n";
            return;
        }
    }
}







bool cpuAttackSmart(PlayerBoard& cpu, PlayerBoard& human,
                    vector<Point>& targets, vector<Point>& frontier)
{
    int row, col;

    // If we have frontier cells (smart mode)
    if (!frontier.empty())
    {
        Point p = frontier.back();
        frontier.pop_back();

        row = p.row;
        col = p.col;

        if (cpu.board[row][col] == 'X' || cpu.board[row][col] == '0')
            return cpuAttackSmart(cpu, human, targets, frontier); // try new
    }
    else
    {
        // Random shot
        do {
            row = rand() % 10;
            col = rand() % 10;
        }
        while (cpu.board[row][col] == 'X' || cpu.board[row][col] == '0');
    }

    cout << "CPU attacks: " << char('A' + row) << (col+1) << endl;

    // HIT
    if (human.board[row][col] != ' ')
    {
        cpu.board[row][col]   = 'X';
        human.board[row][col] = 'X';

        // Save hit point
        targets.push_back({row, col});

        // Add neighbors to frontier
        if (row > 0)    frontier.push_back({row-1, col});
        if (row < 9)    frontier.push_back({row+1, col});
        if (col > 0)    frontier.push_back({row, col-1});
        if (col < 9)    frontier.push_back({row, col+1});

        // Count hit
        char shipLetter = human.board[row][col];
        for (int i = 0; i < FLEET_SIZE; i++)
        {
            if (human.fleet[i].name[0] == shipLetter)
            {
                human.fleet[i].hitcount++;
                if (human.fleet[i].hitcount == human.fleet[i].size)
                {
                    cout << "CPU sunk your " << human.fleet[i].name << "!\n";
                    targets.clear();
                    frontier.clear();
                }
                break;
            }
        }
        return true;
    }

    // MISS
    cpu.board[row][col]   = '0';
    human.board[row][col] = '0';

    cout << "CPU MISS!\n";
    return false;
}








// Runs a full Battleship match: Human vs CPU (Smart AI).
// CPU uses two data structures:
//   - targets: stores confirmed HIT positions
//   - frontier: stores neighboring cells to explore next
// This allows the CPU to attack intelligently and follow the direction of ships.
void playGameSmartCPU(PlayerBoard& human, PlayerBoard& cpu)
{
    bool gameOver = false;   // Controls when the match ends

    vector<Point> targets;   // Stores cells where CPU has already hit a ship
    vector<Point> frontier;  // Stores potential next attack cells around a hit

    while (!gameOver)
    {
        // ===================== PLAYER TURN =====================
        cout << "\n========== PLAYER TURN ==========\n";

        // Display player's board (left) and CPU tracking board (right)
        displayBoards(human.board, cpu.board);

        // Player attacks the CPU board
        bool hit = attack(human, cpu);

        // Provide feedback to player (HIT or MISS)
        cout << (hit ? "Player HIT!\n" : "Player MISS!\n");

        // After player's attack, check if CPU has lost all ships
        if (checkWinner(cpu))
        {
            cout << "\n🔥🔥 PLAYER WINS THE GAME! 🔥🔥\n";
            return;   // Game ends immediately
        }

        // ===================== CPU SMART TURN =====================
        cout << "\n========== CPU SMART TURN ==========\n";

        // CPU performs a strategic attack:
        // If frontier has cells, CPU attacks them first (following ship direction)
        // If frontier is empty, CPU fires randomly
        bool cpuHit = cpuAttackSmart(cpu, human, targets, frontier);

        // After CPU's attack, check if human has lost all ships
        if (checkWinner(human))
        {
            cout << "\n💀💀 CPU WINS THE GAME! 💀💀\n";
            return;   // End match
        }
    }
}
