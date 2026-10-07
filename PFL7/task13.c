#include <stdio.h>

int main(void)
{
    int codes[10], accepted = 0, flagged = 0, highest, i;
    int left, right;

    for (i = 0; i < 10; i++)
    {
        printf("Enter access code for employee %d: ", i + 1);
        scanf("%d", &codes[i]);
    }

    highest = codes[0];
    printf("\nAccess code results:\n");

    for (i = 0; i < 10; i++)
    {
        left = codes[i] << 2;
        right = codes[i] >> 1;
        printf("Code: %d, Left: %d, Right: %d", codes[i], left, right);

        if (left > 100 && right % 2 == 0)
        {
            printf(", Accepted\n");
            accepted++;
        }
        else
        {
            printf(", Flagged\n");
            flagged++;
        }

        if (codes[i] > highest)
            highest = codes[i];
    }

    printf("\nAccepted: %d\n", accepted);
    printf("Flagged: %d\n", flagged);
    printf("Highest original code: %d\n", highest);
    printf("Codes with right shift greater than 20:\n");

    for (i = 0; i < 10; i++)
        if ((codes[i] >> 1) > 20)
            printf("%d\n", codes[i]);

    return 0;
}
