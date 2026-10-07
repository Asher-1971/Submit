#include <stdio.h>

int main(void)
{
    unsigned long long level;
    int hours = 0;

    printf("Enter starting water level: ");
    scanf("%llu", &level);

    while (level != 1)
    {
        printf("Hour %d: %llu liters\n", hours, level);
        if (level % 2 == 0)
            level /= 2;
        else
            level = level * 3 + 1;
        hours++;
    }

    printf("Hour %d: 1 liter\n", hours);
    printf("Total hours: %d\n", hours);
    return 0;
}
