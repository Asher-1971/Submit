#include <stdio.h>

int main(void)
{
    int stock[3][4][5];
    int i, j, k, building_total, shelf_total;
    int fullest_building = 0, fullest_shelf = 0, fullest_total = -1;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 4; j++)
        {
            for (k = 0; k < 5; k++)
            {
                printf("Enter stock for building %d shelf %d slot %d: ",
                       i + 1, j + 1, k + 1);
                scanf("%d", &stock[i][j][k]);
            }
        }
    }

    printf("\nTotal stock per building:\n");
    for (i = 0; i < 3; i++)
    {
        building_total = 0;
        for (j = 0; j < 4; j++)
            for (k = 0; k < 5; k++)
                building_total += stock[i][j][k];
        printf("Building %d: %d\n", i + 1, building_total);
    }

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 4; j++)
        {
            shelf_total = 0;
            for (k = 0; k < 5; k++)
                shelf_total += stock[i][j][k];
            if (shelf_total > fullest_total)
            {
                fullest_total = shelf_total;
                fullest_building = i;
                fullest_shelf = j;
            }
        }
    }

    printf("Fullest shelf: Building %d, Shelf %d (Total: %d)\n",
           fullest_building + 1, fullest_shelf + 1, fullest_total);
    printf("Slots needing restock:\n");
    for (i = 0; i < 3; i++)
        for (j = 0; j < 4; j++)
            for (k = 0; k < 5; k++)
                if (stock[i][j][k] < 5)
                    printf("[%d][%d][%d]\n", i + 1, j + 1, k + 1);

    return 0;
}
