#include <stdio.h>

int main(void)
{
    int x, y, z, w, largest;

    printf("Enter X: ");
    scanf("%d", &x);
    printf("Enter Y: ");
    scanf("%d", &y);
    printf("Enter Z: ");
    scanf("%d", &z);
    printf("Enter W: ");
    scanf("%d", &w);

    if (x > y)
    {
        if (x > z)
        {
            if (x > w)
                largest = x;
            else
                largest = w;
        }
        else
        {
            if (z > w)
                largest = z;
            else
                largest = w;
        }
    }
    else
    {
        if (y > z)
        {
            if (y > w)
                largest = y;
            else
                largest = w;
        }
        else
        {
            if (z > w)
                largest = z;
            else
                largest = w;
        }
    }

    printf("Largest: %d\n", largest);
    return 0;
}