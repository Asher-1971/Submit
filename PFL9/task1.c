#include <stdio.h>

int totalCalories(int steps)
{
    if (steps == 0)
        return 0;
    return steps * 5 + totalCalories(steps - 1);
}

int main(void)
{
    int steps;

    printf("Enter the number of steps: ");
    scanf("%d", &steps);

    if (steps < 0)
        printf("The number of steps cannot be negative.\n");
    else
        printf("Total calories burned: %d\n", totalCalories(steps));

    return 0;
}
