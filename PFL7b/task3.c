#include <stdio.h>

int main(void)
{
    int temp[7][4];
    int i, j, hottest_day = 0, hottest_time = 0;
    int coldest_day = 0, coldest_time = 0;
    int noon_total = 0;
    float noon_average;
    const char *time_slots[4] = {"Morning", "Noon", "Evening", "Night"};

    for (i = 0; i < 7; i++)
    {
        for (j = 0; j < 4; j++)
        {
            printf("Enter temperature for day %d, %s: ", i + 1, time_slots[j]);
            scanf("%d", &temp[i][j]);
            noon_total += j == 1 ? temp[i][j] : 0;
        }
    }

    for (i = 0; i < 7; i++)
    {
        for (j = 0; j < 4; j++)
        {
            if (temp[i][j] > temp[hottest_day][hottest_time])
            {
                hottest_day = i;
                hottest_time = j;
            }
            if (temp[i][j] < temp[coldest_day][coldest_time])
            {
                coldest_day = i;
                coldest_time = j;
            }
        }
    }

    noon_average = noon_total / 7.0f;
    printf("\nHottest reading: %d on day %d during %s\n",
           temp[hottest_day][hottest_time], hottest_day + 1, time_slots[hottest_time]);
    printf("Coldest reading: %d on day %d during %s\n",
           temp[coldest_day][coldest_time], coldest_day + 1, time_slots[coldest_time]);
    printf("Weekly noon average: %.2f\n", noon_average);
    printf("Days with noon temperature above the weekly noon average:\n");
    for (i = 0; i < 7; i++)
    {
        if (temp[i][1] > noon_average)
            printf("Day %d\n", i + 1);
    }

    return 0;
}
