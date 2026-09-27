#include <stdio.h>

int main(void)
{
    char account, transaction;

    scanf(" %c", &account);

    switch (account)
    {
        case '1':
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