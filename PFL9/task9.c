#include <stdio.h>

struct Employee
{
    int id;
    char name[50];
    float salary;
};

void addEmployees(void)
{
    FILE *file;
    struct Employee employee;
    int employeeCount;
    int index;

    file = fopen("employees.dat", "wb");
    if (file == NULL)
    {
        printf("Unable to open employees.dat.\n");
        return;
    }

    printf("Enter the number of employees (at least 5): ");
    scanf("%d", &employeeCount);

    if (employeeCount < 5)
    {
        printf("At least five employees are required.\n");
        fclose(file);
        return;
    }

    for (index = 0; index < employeeCount; index++)
    {
        printf("Enter employee ID: ");
        scanf("%d", &employee.id);
        printf("Enter employee name: ");
        scanf("%49s", employee.name);
        printf("Enter monthly salary: ");
        scanf("%f", &employee.salary);
        fwrite(&employee, sizeof(employee), 1, file);
    }

    fclose(file);
    printf("Employee records saved.\n");
}

void displayEmployees(void)
{
    FILE *file;
    struct Employee employee;
    float totalSalary = 0;
    int recordFound = 0;

    file = fopen("employees.dat", "rb");
    if (file == NULL)
    {
        printf("No employee records were found.\n");
        return;
    }

    printf("\n--- Employee Records ---\n");
    while (fread(&employee, sizeof(employee), 1, file) == 1)
    {
        printf("ID: %d, Name: %s, Monthly salary: %.2f\n",
               employee.id, employee.name, employee.salary);
        totalSalary += employee.salary;
        recordFound = 1;
    }

    if (recordFound)
        printf("Total monthly salary: %.2f\n", totalSalary);
    else
        printf("The employee file is empty.\n");

    fclose(file);
}

void searchEmployee(void)
{
    FILE *file;
    struct Employee employee;
    int searchId;
    int found = 0;

    file = fopen("employees.dat", "rb");
    if (file == NULL)
    {
        printf("No employee records were found.\n");
        return;
    }

    printf("Enter the employee ID to search for: ");
    scanf("%d", &searchId);

    while (fread(&employee, sizeof(employee), 1, file) == 1)
    {
        if (employee.id == searchId)
        {
            printf("Employee found: ID: %d, Name: %s, Monthly salary: %.2f\n",
                   employee.id, employee.name, employee.salary);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("No employee with that ID was found.\n");

    fclose(file);
}

int main(void)
{
    int choice;

    do
    {
        printf("\n1. Create employee records\n");
        printf("2. Display employee records\n");
        printf("3. Search for an employee\n");
        printf("4. Delete all records\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1)
            addEmployees();
        else if (choice == 2)
            displayEmployees();
        else if (choice == 3)
            searchEmployee();
        else if (choice == 4)
        {
            if (remove("employees.dat") == 0)
                printf("All employee records deleted.\n");
            else
                printf("No employee file was found.\n");
        }
        else if (choice != 5)
            printf("Please choose a valid option.\n");
    } while (choice != 5);

    return 0;
}
