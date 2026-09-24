#include <stdio.h>

int main(void)
{
    float shopping_amount, distance, delivery_charges = 0;

    printf("Enter shopping amount: ");
    scanf("%f", &shopping_amount);
    printf("Enter delivery distance in kilometers: ");
    scanf("%f", &distance);

    if (shopping_amount <= 0 || distance <= 0)
    {
        printf("Invalid Input\n");
    }
    else
    {
        if (shopping_amount < 5000)
        {
            if (distance <= 5)
                delivery_charges = 150;
            else if (distance <= 10)
                delivery_charges = 250;
            else if (distance <= 20)
                delivery_charges = 400;
            else
                delivery_charges = 600;
        }

        printf("Shopping Amount: Rs. %.2f\n", shopping_amount);
        printf("Delivery Charges: Rs. %.2f\n", delivery_charges);
        printf("Total Payable Amount: Rs. %.2f\n", shopping_amount + delivery_charges);
    }

    return 0;
}