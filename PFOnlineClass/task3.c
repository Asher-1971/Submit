#include <stdio.h>

int main(void)
{
    int number;
    long long remaining;
    long long reversed = 0;
    int sign = 1;

    printf("Enter an integer: ");
    if (scanf("%d", &number) != 1)
    {
        printf("Please enter a valid integer.\n");
        return 1;
    }

    remaining = number;
    if (remaining < 0)
    {
        sign = -1;
        remaining = -remaining;
    }

    do
    {
        reversed = reversed * 10 + remaining % 10;
        remaining /= 10;
    } while (remaining > 0);

    printf("Reversed integer: %lld\n", sign * reversed);
    return 0;
}
