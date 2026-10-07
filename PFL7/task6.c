#include <stdio.h>

int main(void)
{
    int mark;

    do
    {
        printf("Enter mark from 0 to 100: ");
        scanf("%d", &mark);
    } while (mark < 0 || mark > 100);

    if (mark >= 50)
        printf("Pass\n");
    else
        printf("Fail\n");

    return 0;
}
