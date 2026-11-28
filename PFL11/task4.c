#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int id;
    char name[31];
    float salary;
} Employee;

int main(void)
{
    Employee *employees = NULL;
    int employeeCount;
    int index;
    int highestIndex = 0;
    double totalPayroll = 0.0;

    printf("Enter number of employees: ");
    if (scanf("%d", &employeeCount) != 1 || employeeCount <= 0 ||
        (size_t)employeeCount > (size_t)-1 / sizeof(*employees))
    {
        printf("Please enter a valid positive number of employees.\n");
        return 1;
    }

    employees = malloc((size_t)employeeCount * sizeof(*employees));
    if (employees == NULL)
    {
        perror("Could not allocate memory for employees");
        return 1;
    }

    for (index = 0; index < employeeCount; index++)
    {
        printf("Enter ID, Name, Salary of employee %d: ", index + 1);
        if (scanf("%d %30s %f", &employees[index].id,
                  employees[index].name, &employees[index].salary) != 3 ||
            !isfinite(employees[index].salary) || employees[index].salary < 0.0f)
        {
            printf("Please enter a valid ID, name, and non-negative salary.\n");
            free(employees);
            employees = NULL;
            return 1;
        }

        totalPayroll += employees[index].salary;
        if (employees[index].salary > employees[highestIndex].salary)
            highestIndex = index;
    }

    printf("\n--- Employee List ---\n\n");
    for (index = 0; index < employeeCount; index++)
    {
        printf("%d %s Rs.%.2f\n\n", employees[index].id,
               employees[index].name, employees[index].salary);
    }

    printf("Total payroll: Rs.%.2f\n", totalPayroll);
    printf("Highest salary: %s (Rs.%.2f)\n",
           employees[highestIndex].name, employees[highestIndex].salary);

    free(employees);
    employees = NULL;
    return 0;
}
