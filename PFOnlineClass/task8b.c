#include <stdio.h>

int main(void)
{
    int x = 0;
    int row;
    int column;

    for (row = 1; row <= 4; row++)
    {
        for (column = 1; column <= row; column++)
            x += column;

        printf("%d ", x);
    }
    printf("\n");

    return 0;
}
