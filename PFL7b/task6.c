#include <stdio.h>

int main(void)
{
    char board[3][3];
    char winner = '-';
    int i, j;

    printf("Enter the finished board using X, O, or -:\n");
    for (i = 0; i < 3; i++)
        for (j = 0; j < 3; j++)
            scanf(" %c", &board[i][j]);

    for (i = 0; i < 3; i++)
    {
        if (board[i][0] != '-' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            winner = board[i][0];
        if (board[0][i] != '-' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            winner = board[0][i];
    }
    if (board[0][0] != '-' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        winner = board[0][0];
    if (board[0][2] != '-' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        winner = board[0][2];

    if (winner != '-')
        printf("Winner: %c\n", winner);
    else
        printf("Draw\n");

    return 0;
}
