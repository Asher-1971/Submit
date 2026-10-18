#include <stdio.h>

int main(void)
{
    int rooms[4][6];
    int i, j, vacancies, max_vacancies = -1, floor_with_most = 0;
    int consecutive;

    for (i = 0; i < 4; i++)
    {
        for (j = 0; j < 6; j++)
        {
            printf("Enter status for floor %d room %d (1 occupied, 0 vacant): ", i + 1, j + 1);
            scanf("%d", &rooms[i][j]);
        }
    }

    for (i = 0; i < 4; i++)
    {
        vacancies = 0;
        for (j = 0; j < 6; j++)
            if (rooms[i][j] == 0)
                vacancies++;
        if (vacancies > max_vacancies)
        {
            max_vacancies = vacancies;
            floor_with_most = i;
        }
    }

    printf("\nFloor with the most vacancies: Floor %d (%d vacancies)\n",
           floor_with_most + 1, max_vacancies);
    printf("Floors with 3 or more consecutive vacant rooms:\n");
    for (i = 0; i < 4; i++)
    {
        consecutive = 0;
        for (j = 0; j < 6; j++)
        {
            if (rooms[i][j] == 0)
            {
                consecutive++;
                if (consecutive == 3)
                    printf("Floor %d, starting room %d\n", i + 1, j - 1);
            }
            else
                consecutive = 0;
        }
    }

    return 0;
}
