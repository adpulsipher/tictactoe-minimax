/**
 * @file tictactoe.cpp
 * @author alex pulsipher
 * @brief Unbeatable TicTacToe using Minimax
 */

#include <iostream>
#include <algorithm>

using namespace std;

// Function prototypes
void printBoard(char board[3][3]);
void initializeBoard(char board[3][3]);
int checkWin(char board[3][3]);
int miniMax(char board[3][3], bool isAIturn);
void findBestMove(char board[3][3]);
bool selectTile(int tile, char board[3][3]);

int main() {

    char board[3][3];
    char again;

    do {

        initializeBoard(board);
        printBoard(board);

        int gameState = 2; // 2 = ongoing

        while (gameState == 2) {

            // -------------------
            // HUMAN TURN (X)
            // -------------------
            int userChoice;
            bool valid;

            cout << "Your move (X). Choose 1-9: ";

            do {
                cin >> userChoice;
                valid = selectTile(userChoice, board);
            } while (!valid);

            int row = (userChoice - 1) / 3;
            int col = (userChoice - 1) % 3;
            board[row][col] = 'X';

            printBoard(board);
            gameState = checkWin(board);
            if (gameState != 2) break;

            // -------------------
            // AI TURN (O)
            // -------------------
            cout << "AI is thinking...\n";
            findBestMove(board);

            printBoard(board);
            gameState = checkWin(board);
        }

        // Game result
        if (gameState == 1)
            cout << "AI (O) wins!\n";
        else if (gameState == -1)
            cout << "You (X) win!\n";
        else
            cout << "Cat's game (Draw).\n";

        cout << "Play again? (y/n): ";
        cin >> again;

    } while (again == 'y' || again == 'Y');

    return 0;
}

// -------------------------------------------

void initializeBoard(char board[3][3]) {

    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            board[r][c] = '-';
}

// -------------------------------------------

void printBoard(char board[3][3]) {

    cout << "\n";

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++)
            cout << board[r][c] << " ";
        cout << endl;
    }

    cout << "\n";
}

// -------------------------------------------

bool selectTile(int tile, char board[3][3]) {

    if (tile < 1 || tile > 9) {
        cout << "Invalid tile. Choose 1-9: ";
        return false;
    }

    int row = (tile - 1) / 3;
    int col = (tile - 1) % 3;

    if (board[row][col] == '-') {
        return true;
    }

    cout << "Spot taken. Choose again: ";
    return false;
}

// -------------------------------------------
// checkWin return values:
//  1  = O wins
// -1  = X wins
//  0  = draw
//  2  = game ongoing
// -------------------------------------------

int checkWin(char board[3][3]) {

    // Rows
    for (int r = 0; r < 3; r++) {
        if (board[r][0] == board[r][1] &&
            board[r][1] == board[r][2] &&
            board[r][0] != '-') {

            return (board[r][0] == 'O') ? 1 : -1;
        }
    }

    // Columns
    for (int c = 0; c < 3; c++) {
        if (board[0][c] == board[1][c] &&
            board[1][c] == board[2][c] &&
            board[0][c] != '-') {

            return (board[0][c] == 'O') ? 1 : -1;
        }
    }

    // Diagonals
    if (board[0][0] == board[1][1] &&
        board[1][1] == board[2][2] &&
        board[0][0] != '-') {

        return (board[0][0] == 'O') ? 1 : -1;
    }

    if (board[0][2] == board[1][1] &&
        board[1][1] == board[2][0] &&
        board[0][2] != '-') {

        return (board[0][2] == 'O') ? 1 : -1;
    }

    // Check for empty spaces
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            if (board[r][c] == '-')
                return 2;

    return 0; // draw
}

// -------------------------------------------

int miniMax(char board[3][3], bool isAIturn) {

    int result = checkWin(board);

    if (result != 2)
        return result;

    if (isAIturn) {

        int bestScore = -10000;

        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {

                if (board[r][c] == '-') {

                    board[r][c] = 'O';

                    int score = miniMax(board, false);

                    board[r][c] = '-';

                    bestScore = max(bestScore, score);
                }
            }
        }

        return bestScore;
    }
    else {

        int bestScore = 10000;

        for (int r = 0; r < 3; r++) {
            for (int c = 0; c < 3; c++) {

                if (board[r][c] == '-') {

                    board[r][c] = 'X';

                    int score = miniMax(board, true);

                    board[r][c] = '-';

                    bestScore = min(bestScore, score);
                }
            }
        }

        return bestScore;
    }
}

// -------------------------------------------

void findBestMove(char board[3][3]) {

    int bestScore = -10000;
    int bestRow = -1;
    int bestCol = -1;

    for (int r = 0; r < 3; r++) {
        for (int c = 0; c < 3; c++) {

            if (board[r][c] == '-') {

                board[r][c] = 'O';

                int score = miniMax(board, false);

                board[r][c] = '-';

                if (score > bestScore) {
                    bestScore = score;
                    bestRow = r;
                    bestCol = c;
                }
            }
        }
    }

    board[bestRow][bestCol] = 'O';
}