#include <stdio.h>

int main(void)
{
    int number = 1;
    int row;
    int column;

    for (row = 1; row <= 4; row++)
    {
        for (column = 1; column <= row; column++)
            printf("%d", number++);

        printf("\n");
    }

    return 0;
}
