#include "BoardGame_Classes.hpp"
#include <iostream>

X_O_5_Board::X_O_5_Board()
{
    n_rows = n_cols = 5;
    board = new char *[n_rows];
    for (int i = 0; i < n_rows; i++)
    {
        board[i] = new char[n_cols];
        for (int j = 0; j < n_cols; j++)
            board[i][j] = ' ';
    }
}

// Return true  if move is valid and put it on board
// within board boundaries in empty cell
// Return false otherwise
bool X_O_5_Board::update_board(int x, int y, char mark)
{
    // Only update if move is valid
    if (!(x < 0 || x > 5 || y < 0 || y > 5) && (board[x][y] == ' '))
    {
        board[x][y] = toupper(mark);
        n_moves++;
        return true;
    }
    else
        return false;
}

// Display the board and the pieces on it
void X_O_5_Board::display_board()
{
    for (int i : {0, 1, 2, 3, 4})
    {
        cout << "\n| ";
        for (int j : {0, 1, 2, 3, 4})
        {
            if (board[i][j] == ' ')
            {
                cout << "(" << i << "," << j << ")"
                     << " |";
            }
            else
            {
                cout << setw(2) << board[i][j] << " |";
            }
        }
        cout << "\n-----------------------------";
    }
    cout << endl;
}

// now we make function that have counter for each symbol and the counter checks if there is 3 X or O in a row
// and checks if there is 3 X or O in a column or in a diagonal and if there is it increments the counter for the symbol
// and when the game is over it checks which symbol has the highest counter and returns the winner

bool X_O_5_Board::is_winner()
{
    if (n_moves != 25)
    {
        return false;
    }

    int counterX = 0;
    int counterO = 0;
    char row_win[5], col_win[5], diag_win[2];
    for (int i : {0, 1, 2, 3, 4})
    {
        row_win[i] = board[i][0] & board[i][1] & board[i][2] & board[i][3] & board[i][4];
        col_win[i] = board[0][i] & board[1][i] & board[2][i] & board[3][i] & board[4][i];
    }
    diag_win[0] = board[0][0] & board[1][1] & board[2][2] & board[3][3] & board[4][4];
    diag_win[1] = board[0][4] & board[1][3] & board[2][2] & board[3][1] & board[4][0];
    for (int i : {0, 1, 2, 3, 4})
    {
        if (row_win[i] == 'X')
        {
            counterX++;
        }
        else if (row_win[i] == 'O')
        {
            counterO++;
        }
        if (col_win[i] == 'X')
        {
            counterX++;
        }
        else if (col_win[i] == 'O')
        {
            counterO++;
        }
    }
    if (diag_win[0] == 'X')
    {
        counterX++;
    }
    else if (diag_win[0] == 'O')
    {
        counterO++;
    }
    if (diag_win[1] == 'X')
    {
        counterX++;
    }
    else if (diag_win[1] == 'O')
    {
        counterO++;
    }
    if (counterX > counterO)
    {
        cout << "X is the winner" << endl;
        return true;
    }
    else if (counterO > counterX)
    {
        cout << "O is the winner" << endl;
        return true;
    }
    else
    {
        cout << "It's a draw" << endl;
        return false;
    }
}

// Return true if 25 moves are done and no winner
bool X_O_5_Board::is_draw()
{
    return (n_moves == 25 && !is_winner());
}

bool X_O_5_Board::game_is_over()
{
    return n_moves >= 25;
}