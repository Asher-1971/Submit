#include <stdio.h>

void modify(int values[])
{
    values[0] = values[0] + 5;
    values[1] = values[1] * 2;
}

int main(void)
{
    int values[3] = {2, 3, 4};
    int x = 0;
    int index;
    int row;
    int column;

    modify(values);

    printf("Output of the array-modification program: ");
    for (index = 0; index < 3; index++)
        printf("%d ", values[index]);
    printf("\n");

    printf("Output of the nested-loop program: ");
    for (row = 1; row <= 4; row++)
    {
        for (column = 1; column <= row; column++)
            x += column;

        printf("%d ", x);
    }
    printf("\n");

    return 0;
}
