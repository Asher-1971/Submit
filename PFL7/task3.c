#include <stdio.h>

int main(void)
{
    double money, factor, result;
    int years, i;

    printf("Enter starting amount: ");
    scanf("%lf", &money);
    printf("Enter growth factor: ");
    scanf("%lf", &factor);
    printf("Enter number of years: ");
    scanf("%d", &years);

    result = money;
    for (i = 1; i <= years; i++)
        result *= factor;

    printf("Amount after %d years: %.2f\n", years, result);
    return 0;
}
