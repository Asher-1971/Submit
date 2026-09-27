#include <stdio.h>

int main(void)
{
    float a, b, c;

    scanf("%f %f %f", &a, &b, &c);

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