#include <stdio.h>

int main(void)
{
    int stock[10], search, found = 0, i;

    for (i = 0; i < 10; i++)
    {
        printf("Enter stock for shelf %d: ", i);
        scanf("%d", &stock[i]);
    }

    printf("Reverse order:\n");
    for (i = 9; i >= 0; i--)
        printf("Shelf %d: %d\n", i, stock[i]);

    printf("Enter stock count to search: ");
    scanf("%d", &search);

    for (i = 0; i < 10; i++)
    {
        if (stock[i] == search)
        {
            printf("Found at shelf %d\n", i);
            found = 1;
        }
    }

    if (!found)
        printf("Stock count does not exist\n");

    return 0;
}
