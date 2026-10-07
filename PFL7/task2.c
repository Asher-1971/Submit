#include <stdio.h>

int main(void)
{
    int n, score, total = 0, i;
    float average;

    printf("Enter number of students: ");
    scanf("%d", &n);

    for (i = 1; i <= n; i++)
    {
        printf("Enter score for student %d: ", i);
        scanf("%d", &score);
        total += score;
    }

    average = (float) total / n;
    printf("Total score: %d\n", total);
    printf("Average score: %.2f\n", average);

    return 0;
}
