#include <stdio.h>

int main(void)
{
    int x, y, z, w, largest;

    scanf("%d %d %d %d", &x, &y, &z, &w);

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