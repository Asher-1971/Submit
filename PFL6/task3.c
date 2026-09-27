#include <stdio.h>

int main(void)
{
    int units;
    char type;
    float bill;

    scanf("%d %c", &units, &type);

    if (type == 'D' || type == 'd')
    {
        if (units <= 100)
            bill = units * 10.0f;
        else
        {
            if (units <= 300)
                bill = units * 15.0f;
            else
                bill = units * 20.0f;
        }
    }
    else
    {
        if (units <= 100)
            bill = units * 15.0f;
        else
        {
            if (units <= 300)
                bill = units * 20.0f;
            else
                bill = units * 25.0f;
        }
    }

    printf("Total Bill: %.2f\n", bill);
    return 0;
}