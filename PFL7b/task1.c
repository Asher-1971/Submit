#include <stdio.h>

int main(void)
{
    int seats[5][8];
    int i, j, free_seats, total_free = 0;

    for (i = 0; i < 5; i++)
    {
        for (j = 0; j < 8; j++)
        {
            printf("Enter status for row %d seat %d (0 empty, 1 booked): ", i + 1, j + 1);
            scanf("%d", &seats[i][j]);
        }
    }

    printf("\nSeating map:\n");
    for (i = 0; i < 5; i++)
    {
        free_seats = 0;
        for (j = 0; j < 8; j++)
        {
            if (seats[i][j] == 0)
            {
                printf(". ");
                free_seats++;
            }
            else
                printf("X ");
        }
        total_free += free_seats;
        printf("  Free seats in row %d: %d\n", i + 1, free_seats);
    }

    printf("Total free seats: %d\n", total_free);
    return 0;
}
