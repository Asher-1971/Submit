#include <stdio.h>

struct Employee
{
    int id;
    char name[30];
    float salary;
};

int main(void)
{
    struct Employee employees[3];
    int index;

    for (index = 0; index < 3; index++)
    {
        printf("Enter the ID of employee %d: ", index + 1);
        scanf("%d", &employees[index].id);
        printf("Enter the name of employee %d: ", index + 1);
        scanf("%29s", employees[index].name);
        printf("Enter the salary of employee %d: ", index + 1);
        scanf("%f", &employees[index].salary);

        if (employees[index].salary < 50000)
            employees[index].salary += employees[index].salary * 0.10f;
    }

    printf("\n--- Updated Salaries ---\n");
    for (index = 0; index < 3; index++)
        printf("%d  %s  %.2f\n",
               employees[index].id, employees[index].name, employees[index].salary);

    return 0;
}
