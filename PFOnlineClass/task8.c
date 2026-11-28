#include <stdio.h>

void modify(int values[])
{
    values[0] = values[0] + 5;
    values[1] = values[1] * 2;
}

int main(void)
{
    int values[3] = {2, 3, 4};
    int index;

    modify(values);

    for (index = 0; index < 3; index++)
        printf("%d ", values[index]);
    printf("\n");

    return 0;
}
