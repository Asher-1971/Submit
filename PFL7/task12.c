#include <stdio.h>

int main(void)
{
    int codes[5], speeds[5], high = 0, medium = 0, normal = 0, i;
    int left, right;

    for (i = 0; i < 5; i++)
    {
        printf("Enter priority code for vehicle %d: ", i + 1);
        scanf("%d", &codes[i]);
        printf("Enter speed for vehicle %d: ", i + 1);
        scanf("%d", &speeds[i]);
    }

    for (i = 0; i < 5; i++)
    {
        left = codes[i] << 2;
        right = codes[i] >> 1;
        printf("\nVehicle %d\n", i + 1);
        printf("Original: %d\n", codes[i]);
        printf("Left shift: %d\n", left);
        printf("Right shift: %d\n", right);
        printf("Speed: %d km/h\n", speeds[i]);

        if (left > 20 && speeds[i] >= 80)
        {
            printf("High Priority\n");
            high++;
        }
        else if (left > 10 && speeds[i] >= 60)
        {
            printf("Medium Priority\n");
            medium++;
        }
        else
        {
            printf("Normal Priority\n");
            normal++;
        }
    }

    printf("\nHigh: %d\nMedium: %d\nNormal: %d\n", high, medium, normal);
    return 0;
}
