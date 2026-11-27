#include <stdio.h>

unsigned long long sumDigits(unsigned long long number)
{
    if (number < 10)
        return number;

    return number % 10 + sumDigits(number / 10);
}

int main(void)
{
    long long number;
    unsigned long long magnitude;

    printf("Enter an integer: ");
    if (scanf("%lld", &number) != 1)
    {
        printf("Please enter a valid integer.\n");
        return 1;
    }

    if (number < 0)
        magnitude = (unsigned long long)(-(number + 1)) + 1;
    else
        magnitude = (unsigned long long)number;

    printf("Sum of digits: %llu\n", sumDigits(magnitude));
    return 0;
}
