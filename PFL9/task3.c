#include <stdio.h>

struct Book
{
    int id;
    char title[50];
    float price;
};

int main(void)
{
    struct Book books[3];
    int index;
    int expensiveIndex = 0;

    for (index = 0; index < 3; index++)
    {
        printf("Enter the ID of book %d: ", index + 1);
        scanf("%d", &books[index].id);
        printf("Enter the title of book %d: ", index + 1);
        scanf("%49s", books[index].title);
        printf("Enter the price of book %d: ", index + 1);
        scanf("%f", &books[index].price);

        if (books[index].price > books[expensiveIndex].price)
            expensiveIndex = index;
    }

    printf("\n--- Book List ---\n");
    for (index = 0; index < 3; index++)
        printf("%d  %s  Rs.%.2f\n", books[index].id, books[index].title, books[index].price);

    printf("\nMost expensive: %s (Rs.%.2f)\n",
           books[expensiveIndex].title, books[expensiveIndex].price);

    return 0;
}
