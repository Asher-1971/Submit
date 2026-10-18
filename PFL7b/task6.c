#include <stdio.h>

int main(void)
{
    char board[3][3];
    int i, j, x_wins = 0, o_wins = 0;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            do
            {
                printf("Enter row %d, column %d (X, O, or -): ", i + 1, j + 1);
                scanf(" %c", &board[i][j]);
                if (board[i][j] != 'X' && board[i][j] != 'O' && board[i][j] != '-')
                    printf("Invalid input. Enter only X, O, or -.\n");
            } while (board[i][j] != 'X' && board[i][j] != 'O' && board[i][j] != '-');
        }
    }

    for (i = 0; i < 3; i++)
    {
        if (board[i][0] != '-' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
        {
            if (board[i][0] == 'X')
                x_wins = 1;
            else
                o_wins = 1;
        }
        if (board[0][i] != '-' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
        {
            if (board[0][i] == 'X')
                x_wins = 1;
            else
                o_wins = 1;
        }
    }

    if (board[0][0] != '-' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
    {
        if (board[0][0] == 'X')
            x_wins = 1;
        else
            o_wins = 1;
    }
    if (board[0][2] != '-' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
    {
        if (board[0][2] == 'X')
            x_wins = 1;
        else
            o_wins = 1;
    }

    if (x_wins && o_wins)
        printf("Invalid board: both X and O have winning lines.\n");
    else if (x_wins)
        printf("Winner: X\n");
    else if (o_wins)
        printf("Winner: O\n");
    else
        printf("Draw\n");

    return 0;
}
