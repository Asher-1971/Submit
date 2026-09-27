#include <stdio.h>

int main(void)
{
    float a, b, c;

    printf("Enter side 1: ");
    scanf("%f", &a);
    printf("Enter side 2: ");
    scanf("%f", &b);
    printf("Enter side 3: ");
    scanf("%f", &c);

    if (a + b > c)
    {
        if (a + c > b)
        {
            if (b + c > a)
            {
                if (a == b)
                {
                    if (b == c)
                        printf("Equilateral\n");
                    else
                        printf("Isosceles\n");
                }
                else
                {
                    if (a == c)
                        printf("Isosceles\n");
                    else
                    {
                        if (b == c)
                            printf("Isosceles\n");
                        else
                            printf("Scalene\n");
                    }
                }
            }
            else
                printf("Not a valid triangle\n");
        }
        else
            printf("Not a valid triangle\n");
    }
    else
        printf("Not a valid triangle\n");

    return 0;
}