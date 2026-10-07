#include <stdio.h>

int main(void)
{
    int choice;
    float total = 0, price;

    do
    {
        printf("\n1. Add Item\n");
        printf("2. Remove Item\n");
        printf("3. View Total\n");
        printf("4. Checkout\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            printf("Enter item price: ");
            scanf("%f", &price);
            total += price;
        }
        else if (choice == 2)
        {
            printf("Enter item price to remove: ");
            scanf("%f", &price);
            total -= price;
            if (total < 0)
                total = 0;
        }
        else if (choice == 3)
        {
            printf("Total: Rs. %.2f\n", total);
        }
        else if (choice == 4)
        {
            printf("Checkout total: Rs. %.2f\n", total);
        }
        else
        {
            printf("Invalid choice\n");
        }
    } while (choice != 4);

    return 0;
}
