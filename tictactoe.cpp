/**
 * @file tictactoe.cpp
 * @author alex pulsipher
 * @brief 
 * 
 * A simple tictactoe game using simple console input output, functions, and some tricky 2D arrays!
 * Now with a fun unbeatable AI!
 * 
 * @version 2.0
 * @date 2026-02-24
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>

using namespace std;

//function prototypes
bool selectTile (int tile, char board[3][3], int num);
void printTiles (char board[3][3]);
void playGame (int num, char board[3][3]);
void initializeBoard (char board[3][3]);
int checkWin (char board[3][3]);
int miniMax (char board[3][3], bool isAIturn);

int main () {

    srand(time(NULL));
    char again;
    char board[3][3];

    do {
        //random number 0 or 1 to decide X or O
        //int num = rand () % 2;
        //cout << num << " is the random number between 0 and 1\n";
        
        //starts the game with 'O'
        playGame (0, board);
        cout << "Play again? Enter y/n\n";
        cin >> again;

    } while (again == 'y' || again == 'Y');


    return 0;
}

void playGame (int num, char board[3][3]) {

    int userTile = num;

    initializeBoard(board);
    printTiles(board);

    int gameOver = {};
    do {

        int userSelection = {};
        char tileChar = ' ';

        //if num is 0 it starts with O, otherwise starts with X
        if (userTile == 0) {
            tileChar = 'O';
        } else tileChar = 'X';

        cout << "Which tile will you select? Enter the number (1-9; left to right, up to down): ";
        bool validMove;
        do {
            
            cin >> userSelection;
            validMove = selectTile(userSelection, board, userTile);

        } while (!validMove);

        int row = (userSelection - 1) / 3;
        int col = (userSelection - 1) % 3;
        board[row][col] = tileChar;

        gameOver = checkWin(board);
        printTiles(board);

        userTile = 1 - userTile;
        

    } while (gameOver == 0);
    char tileChar = ' ';
    if (userTile == 1) {
        tileChar = 'O';
    } else {
        tileChar = 'X';
    }
    if (gameOver == 1) {
        cout << tileChar << "'s have won the game!\n";
    } else if (gameOver == 2) {
        cout << "Cat's game, bummer. Better luck next time\n";
    }
}

bool selectTile(int tile, char board[3][3], int num) {

int row = (tile - 1) / 3;
int col = (tile - 1) % 3;

    if (board[row][col] == '-') {
        return true;
    } else {
        cout << "This space is occupied. Enter another number (1-9; left to right, top to bottom): ";
        return false;
    }
}

void printTiles(char board[3][3]) {
    
    cout << string(50, '\n');

    for (int row = {}; row < 3; row++) {
        cout << ((row * 3) + 1) << " > ";
        for (int col = {}; col < 3; col++) {
            cout << board[row][col];
        }
        cout << endl;
    }

    cout << string(3, '\n');
}

void initializeBoard(char board[3][3]) {

    for (int row = {}; row < 3; row++) {
        for (int col = {}; col < 3; col++) {
            board[row][col] = '-';
        }
    }
}

int checkWin(char board[3][3]) {

for (int row = 0; row < 3; row++) {
    if (board[row][0] == board[row][1]
        && board[row][1] == board[row][2]
        && board[row][2] != '-') 
    {
        if (board[row][0] == 'O') {
            return 1; 
        } else return -1;
    }
}
for (int col = 0; col < 3; col++) {
    if (board[0][col] == board[1][col]
        && board[1][col] == board[2][col]
        && board[2][col] != '-') 
    {
        if (board[0][col] == 'O') {
            return 1; 
        } else return -1;
    }
}
if (board[0][0] == board[1][1]
    && board[1][1] == board[2][2]
    && board[2][2] != '-') 
    {
        if (board[0][0] == 'O') {
            return 1; 
        } else return -1;
    }
if (board[0][2] == board[1][1]
    && board[1][1] == board[2][0]
    && board[2][0] != '-') 
    {
        if (board[0][2] == 'O') {
            return 1; 
        } else return -1;
    }
//check for cat's game, if it finds no -, and all win possibilities have been checked, must be a cat's game, therefore return 0 (a draw for minimax alogrithm)
for (int row = 0; row < 3; row++) {
    for (int col = 0; col < 3; col++) {
        if (board[row][col] == '-') {
            return 2;
        }
    }
}
return 0;
}
int miniMax (char board[3][3], bool isAIturn) {

    int result = checkWin(board);

    if (result != 2)  // game over
        return result;

    if (isAIturn) {
        int bestScore = -10000;
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (board[row][col] == '-') {
                    board[row][col] = 'O';
                    int score = miniMax(board, false);
                    board[row][col] = '-';
                    bestScore = max(bestScore, score);
                }
            }
        }
        return bestScore;
    } else
    {
        int bestScore = 10000;
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (board[row][col] == '-') {
                    board[row][col] = 'X';
                    int score = miniMax(board, true);
                    board[row][col] = '-';
                    bestScore = min(bestScore, score);
                }
            }
        }
        return bestScore;
    }
}