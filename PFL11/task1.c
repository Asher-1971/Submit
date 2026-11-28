#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *marks = NULL;
    int studentCount;
    int index;
    int highest;
    int lowest;
    long long total = 0;
    double average;

    printf("Enter number of students: ");
    if (scanf("%d", &studentCount) != 1 || studentCount <= 0 ||
        (size_t)studentCount > (size_t)-1 / sizeof(*marks))
    {
        printf("Please enter a valid positive number of students.\n");
        return 1;
    }

    marks = malloc((size_t)studentCount * sizeof(*marks));
    if (marks == NULL)
    {
        perror("Could not allocate memory for marks");
        return 1;
    }

    printf("Enter %d marks: ", studentCount);
    for (index = 0; index < studentCount; index++)
    {
        if (scanf("%d", &marks[index]) != 1)
        {
            printf("Please enter valid integer marks.\n");
            free(marks);
            marks = NULL;
            return 1;
        }
    }

    highest = marks[0];
    lowest = marks[0];
    for (index = 0; index < studentCount; index++)
    {
        total += marks[index];
        if (marks[index] > highest)
            highest = marks[index];
        if (marks[index] < lowest)
            lowest = marks[index];
    }

    average = (double)total / studentCount;
    printf("\n--- Result Summary ---\n");
    printf("Average marks: %.2f\n", average);
    printf("Highest marks: %d\n", highest);
    printf("Lowest marks: %d\n", lowest);

    free(marks);
    marks = NULL;
    return 0;
}
