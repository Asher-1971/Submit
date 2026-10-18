#include <stdio.h>

int main(void)
{
    int marks[3][4][5];
    int i, j, k, total, department_total;
    int topper = 0, topper_total, highest_department = 0;
    int highest_department_total = -1;
    float average, department_average;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 4; j++)
        {
            for (k = 0; k < 5; k++)
            {
                printf("Enter marks for department %d student %d subject %d: ",
                       i + 1, j + 1, k + 1);
                scanf("%d", &marks[i][j][k]);
            }
        }
    }

    printf("\nStudent results:\n");
    for (i = 0; i < 3; i++)
    {
        department_total = 0;
        topper_total = -1;
        for (j = 0; j < 4; j++)
        {
            total = 0;
            for (k = 0; k < 5; k++)
                total += marks[i][j][k];
            average = total / 5.0f;
            printf("Department %d, Student %d - Average: %.2f",
                   i + 1, j + 1, average);
            for (k = 0; k < 5; k++)
                if (marks[i][j][k] < 40)
                    break;
            if (k < 5)
                printf(" - FAIL");
            printf("\n");
            department_total += total;
            if (total > topper_total)
            {
                topper_total = total;
                topper = j;
            }
        }
        department_average = department_total / 20.0f;
        printf("Topper of department %d: Student %d (Average: %.2f)\n",
               i + 1, topper + 1, topper_total / 5.0f);
        if (department_total > highest_department_total)
        {
            highest_department_total = department_total;
            highest_department = i;
        }
        printf("Department %d overall average: %.2f\n", i + 1, department_average);
    }

    printf("Department with the highest overall average: Department %d\n",
           highest_department + 1);
    return 0;
}
