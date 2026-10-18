#include <stdio.h>

int main(void)
{
    int marks[6][4];
    int i, j, total, subject_totals[4] = {0};
    int best_subject = 0;
    float average, best_average = 0;

    for (i = 0; i < 6; i++)
    {
        for (j = 0; j < 4; j++)
        {
            printf("Enter marks for student %d subject %d: ", i + 1, j + 1);
            scanf("%d", &marks[i][j]);
            subject_totals[j] += marks[i][j];
        }
    }

    printf("\nStudent results:\n");
    for (i = 0; i < 6; i++)
    {
        total = 0;
        for (j = 0; j < 4; j++)
            total += marks[i][j];
        average = total / 4.0f;
        printf("Student %d - Total: %d, Average: %.2f\n", i + 1, total, average);
    }

    printf("\nSubject class averages:\n");
    for (j = 0; j < 4; j++)
    {
        average = subject_totals[j] / 6.0f;
        printf("Subject %d: %.2f\n", j + 1, average);
        if (average > best_average)
        {
            best_average = average;
            best_subject = j;
        }
    }

    printf("Best-performing subject: Subject %d\n", best_subject + 1);
    return 0;
}
