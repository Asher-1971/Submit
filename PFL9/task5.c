#include <stdio.h>

float calculateTotal(float prices[], int count)
{
    if (count == 0)
        return 0;
    return prices[count - 1] + calculateTotal(prices, count - 1);
}

int main(void)
{
    float prices[100];
    float total;
    int productCount;
    int index;

    printf("Enter the number of products: ");
    scanf("%d", &productCount);

    if (productCount <= 0 || productCount > 100)
    {
        printf("Please enter a number from 1 to 100.\n");
        return 1;
    }

    for (index = 0; index < productCount; index++)
    {
        printf("Enter the price of product %d: ", index + 1);
        scanf("%f", &prices[index]);
    }

    total = calculateTotal(prices, productCount);
    printf("Total bill: Rs.%.2f\n", total);
    printf("Average price: Rs.%.2f\n", total / productCount);

    return 0;
}
