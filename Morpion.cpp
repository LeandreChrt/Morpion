#include <iostream>
#include <cmath>
#include <cctype>

using namespace std;

bool display(int board[][3], int turn, int row, int col);
bool win(int board[][3], int col, int row, int modif_col, int modif_row, int turn, int line, bool reverse = false);
bool in_array(char array[], int position);
bool in_array(int array[], int position);

int main()
{

    const string play = "Où voulez vous jouer ?";
    int board[3][3] = {
        {0, 0, 0},
        {0, 0, 0},
        {0, 0, 0}};
    char letters[3] = {65, 66, 67};
    int numbers[3] = {1, 2, 3};
    int turn = 2;
    int count = 0;
    bool win = display(board, turn, 3, 3);
    string position;
    do
    {
        turn = turn == 2 ? 1 : 2;
        int number_pos;
        int letter_pos;
        bool loop;
        do
        {
            cout << play << " (Joueur " << turn << ")\n";
            cin >> position;
            number_pos = position[1] - '0';
            letter_pos = int(toupper(position[0]));
            if (!in_array(numbers, number_pos) || !in_array(letters, letter_pos))
            {
                cout << "Case inexistante\n";
                loop = true;
            }
            else if (board[number_pos - 1][letter_pos - 65] != 0)
            {
                cout << "Case déjà occupé\n";
                loop = true;
            }
            else
            {
                loop = false;
            }
        } while (loop);
        board[number_pos - 1][letter_pos - 65] = turn;
        win = display(board, turn, number_pos - 1, letter_pos - 65);
        count++;
    } while (win == false && count < 9);
    if (win)
    {
        cout << "Gagnant : Joueur " << turn << "\n";
    }
    else {
        cout << "Partie nulle\n";
    }
}

bool in_array(char array[], int position)
{
    for (int i = 0; i < 3; i++)
    {
        if (array[i] == position)
        {
            return true;
        }
    }
    return false;
}

bool in_array(int array[], int position)
{
    for (int j = 0; j < 3; j++)
    {
        if (array[j] == position)
        {
            return true;
        }
    }
    return false;
}

bool display(int board[][3], int turn, int row, int col)
{
    cout << "\033[2J\033[1;1H";
    string test1[9] = {"", "", "", "", "", "", "", "", ""};
    string test2[9] = {"", "", "", "", "", "", "", "", ""};
    if (row * col != 9)
    {
        int pos = 3 * row + col;
        test1[pos] = "\033[1;31m";
        test2[pos] = "\033[0m";
    }
    cout << "   A B C \n";
    cout << "  +-+-+-+\n";
    cout << "1 |" << test1[0] << board[0][0] << test2[0] << "|" << test1[1] << board[0][1] << test2[1] << "|" << test1[2] << board[0][2] << test2[2] << "|\n";
    cout << "  +-+-+-+\n";
    cout << "2 |" << test1[3] << board[1][0] << test2[3] << "|" << test1[4] << board[1][1] << test2[4] << "|" << test1[5] << board[1][2] << test2[5] << "|\n";
    cout << "  +-+-+-+\n";
    cout << "3 |" << test1[6] << board[2][0] << test2[6] << "|" << test1[7] << board[2][1] << test2[7] << "|" << test1[8] << board[2][2] << test2[8] << "|\n";
    cout << "  +-+-+-+\n";
    if (row != 3 && col != 3)
    {
        if (win(board, col, row, 1, 0, turn, 1, false))
        {
            return true;
        }
        else if (win(board, col, row, 0, 1, turn, 1, false))
        {
            return true;
        }
        else if (win(board, col, row, 1, 1, turn, 1, false))
        {
            return true;
        }
        else if (win(board, col, row, 1, -1, turn, 1, false))
        {
            return true;
        }
    }
    return false;
}

bool win(int board[][3], int col, int row, int modif_col, int modif_row, int turn, int line, bool reverse)
{
    if (col + modif_col < 3 && col + modif_col > -1 && row + modif_row < 3 && row + modif_row > -1 && board[row + modif_row][col + modif_col] == turn)
    {
        if (line == 1)
        {
            return win(board, col, row, modif_col * 2, modif_row * 2, turn, 2, reverse);
        }
        else
        {
            return true;
        }
    }
    else if (!reverse)
    {
        modif_col = modif_col != 0 ? modif_col / abs(modif_col) * -1 : 0;
        modif_row = modif_row != 0 ? modif_row / abs(modif_row) * -1 : 0;
        return win(board, col, row, modif_col, modif_row, turn, line, true);
    }
    else
    {
        return false;
    }
}