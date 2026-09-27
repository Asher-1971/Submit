#include <stdio.h>

int main(void)
{
    char account, transaction;

    printf("Enter account type (1 for Savings, 2 for Current): ");
    scanf(" %c", &account);

    switch (account)
    {
        case '1':
            printf("Enter transaction (1 for Deposit, 2 for Withdraw, 3 for Check Balance): ");
            scanf(" %c", &transaction);
            switch (transaction)
            {
                case '1': printf("Savings account deposit performed\n"); break;
                case '2': printf("Savings account withdrawal performed\n"); break;
                case '3': printf("Savings account balance checked\n"); break;
                default: printf("Invalid transaction choice\n");
            }
            break;
        case '2':
            printf("Enter transaction (1 for Deposit, 2 for Withdraw, 3 for Check Balance): ");
            scanf(" %c", &transaction);
            switch (transaction)
            {
                case '1': printf("Current account deposit performed\n"); break;
                case '2': printf("Current account withdrawal performed\n"); break;
                case '3': printf("Current account balance checked\n"); break;
                default: printf("Invalid transaction choice\n");
            }
            break;
        default: printf("Invalid account choice\n");
    }

    return 0;
}