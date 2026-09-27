#include <stdio.h>

int main(void)
{
    int age;
    char day;
    float price;

    printf("Enter age: ");
    scanf("%d", &age);
    printf("Enter day (W for weekday, H for holiday): ");
    scanf(" %c", &day);

    if (age < 12)
    {
        if (day == 'W' || day == 'w')
            price = 300;
        else
            price = 400;
    }
    else
    {
        if (age > 60)
        {
            if (day == 'W' || day == 'w')
                price = 300;
            else
                price = 400;
        }
        else
        {
            if (day == 'W' || day == 'w')
                price = 500;
            else
                price = 700;
        }
    }

    printf("Ticket Price: %.2f\n", price);
    return 0;
}