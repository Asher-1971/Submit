#include <stdio.h>

int main(void)
{
    float balance = 50000, amount;
    int choice;

    printf("1. Check Balance\n");
    printf("2. Deposit Money\n");
    printf("3. Withdraw Money\n");
    printf("4. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            printf("Current Balance: Rs. %.2f\n", balance);
            break;
        case 2:
            printf("Enter deposit amount: ");
            scanf("%f", &amount);
            balance += amount;
            printf("Updated Balance: Rs. %.2f\n", balance);
            break;
        case 3:
            printf("Enter withdrawal amount: ");
            scanf("%f", &amount);
            if (amount <= balance)
            {
                balance -= amount;
                printf("Remaining Balance: Rs. %.2f\n", balance);
            }
            else
            {
                printf("Insufficient Balance\n");
            }
            break;
        case 4:
            printf("Thank you for using the ATM\n");
            break;
        default:
            printf("Invalid Option\n");
    }

    return 0;
}