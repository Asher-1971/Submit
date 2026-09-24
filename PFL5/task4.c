#include <stdio.h>

int main(void)
{
    int category, item;

    printf("1. Fast Food\n");
    printf("2. Pakistani Food\n");
    printf("3. Drinks\n");
    printf("Enter category choice: ");
    scanf("%d", &category);

    switch (category)
    {
        case 1:
            printf("1. Burger\n");
            printf("2. Pizza\n");
            printf("3. Fries\n");
            printf("Enter item number: ");
            scanf("%d", &item);
            switch (item)
            {
                case 1: printf("You selected: Burger\n"); break;
                case 2: printf("You selected: Pizza\n"); break;
                case 3: printf("You selected: Fries\n"); break;
                default: printf("Invalid Item Choice\n");
            }
            break;
        case 2:
            printf("1. Biryani\n");
            printf("2. Karahi\n");
            printf("3. Nihari\n");
            printf("Enter item number: ");
            scanf("%d", &item);
            switch (item)
            {
                case 1: printf("You selected: Biryani\n"); break;
                case 2: printf("You selected: Karahi\n"); break;
                case 3: printf("You selected: Nihari\n"); break;
                default: printf("Invalid Item Choice\n");
            }
            break;
        case 3:
            printf("1. Coke\n");
            printf("2. Pepsi\n");
            printf("3. Juice\n");
            printf("Enter item number: ");
            scanf("%d", &item);
            switch (item)
            {
                case 1: printf("You selected: Coke\n"); break;
                case 2: printf("You selected: Pepsi\n"); break;
                case 3: printf("You selected: Juice\n"); break;
                default: printf("Invalid Item Choice\n");
            }
            break;
        default:
            printf("Invalid Category Choice\n");
    }

    return 0;
}