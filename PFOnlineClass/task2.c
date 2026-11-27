#include <stdio.h>

#define ARRAY_SIZE 5

int secondLargest(const int values[])
{
    int largest = values[0];
    int second = values[1];
    int index;

    if (second > largest)
    {
        int temporary = largest;
        largest = second;
        second = temporary;
    }

    for (index = 2; index < ARRAY_SIZE; index++)
    {
        if (values[index] > largest)
        {
            second = largest;
            largest = values[index];
        }
        else if (values[index] > second)
        {
            second = values[index];
        }
    }

    return second;
}

int main(void)
{
    int values[ARRAY_SIZE];
    int index;
    int earlier;

    printf("Enter %d distinct integers:\n", ARRAY_SIZE);
    for (index = 0; index < ARRAY_SIZE; index++)
    {
        printf("Element %d: ", index + 1);
        if (scanf("%d", &values[index]) != 1)
        {
            printf("Please enter valid integers.\n");
            return 1;
        }

        for (earlier = 0; earlier < index; earlier++)
        {
            if (values[earlier] == values[index])
            {
                printf("All five integers must be distinct.\n");
                return 1;
            }
        }
    }

    printf("Second-largest element: %d\n", secondLargest(values));
    return 0;
}
