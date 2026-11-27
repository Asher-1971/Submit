#include <stdio.h>

#define MAX_SIZE 100

int countEven(const int values[], int size)
{
    int count = 0;
    int index;

    for (index = 0; index < size; index++)
    {
        if (values[index] % 2 == 0)
            count++;
    }

    return count;
}

int main(void)
{
    int values[MAX_SIZE];
    int size;
    int index;

    printf("Enter the number of elements (1-%d): ", MAX_SIZE);
    if (scanf("%d", &size) != 1 || size < 1 || size > MAX_SIZE)
    {
        printf("Please enter a valid array size.\n");
        return 1;
    }

    for (index = 0; index < size; index++)
    {
        printf("Element %d: ", index + 1);
        if (scanf("%d", &values[index]) != 1)
        {
            printf("Please enter valid integers.\n");
            return 1;
        }
    }

    printf("Number of even elements: %d\n", countEven(values, size));
    return 0;
}
