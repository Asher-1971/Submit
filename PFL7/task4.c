#include <stdio.h>

int main(void)
{
    int pin, copy, digit, sum = 0, reverse = 0;

    printf("Enter a 4 to 6 digit PIN: ");
    scanf("%d", &pin);

    while (pin < 1000 || pin > 999999)
    {
        printf("Enter a valid PIN: ");
        scanf("%d", &pin);
    }

    copy = pin;
    while (copy > 0)
    {
        digit = copy % 10;
        sum += digit;
        reverse = reverse * 10 + digit;
        copy /= 10;
    }

    printf("Digit sum: %d\n", sum);
    printf("Reversed PIN: %d\n", reverse);
    return 0;
}
