#include <stdio.h>
#include <string.h>

void addRecords(void)
{
    FILE *file;
    char name[50];
    int rollNumber;
    char status[10];
    int recordCount;
    int index;

    file = fopen("attendance.txt", "a");
    if (file == NULL)
    {
        printf("Unable to open attendance.txt.\n");
        return;
    }

    printf("How many student records do you want to add? ");
    scanf("%d", &recordCount);

    for (index = 0; index < recordCount; index++)
    {
        printf("Enter student name: ");
        scanf(" %49[^\n]", name);
        printf("Enter roll number: ");
        scanf("%d", &rollNumber);
        printf("Enter attendance status (Present or Absent): ");
        scanf("%9s", status);
        fprintf(file, "%d %s|%s\n", rollNumber, name, status);
    }

    fclose(file);
    printf("Attendance records saved.\n");
}

void displayRecords(void)
{
    FILE *file;
    char name[50];
    char status[10];
    int rollNumber;

    file = fopen("attendance.txt", "r");
    if (file == NULL)
    {
        printf("No attendance records were found.\n");
        return;
    }

    printf("\n--- Attendance Records ---\n");
    while (fscanf(file, "%d %49[^|]|%9s", &rollNumber, name, status) == 3)
        printf("Roll number: %d, Name: %s, Status: %s\n", rollNumber, name, status);

    fclose(file);
}

int main(void)
{
    int choice;

    do
    {
        printf("\n1. Add records\n");
        printf("2. Display records\n");
        printf("3. Delete all records\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1)
            addRecords();
        else if (choice == 2)
            displayRecords();
        else if (choice == 3)
        {
            if (remove("attendance.txt") == 0)
                printf("All attendance records deleted.\n");
            else
                printf("No attendance file was found.\n");
        }
        else if (choice != 4)
            printf("Please choose a valid option.\n");
    } while (choice != 4);

    return 0;
}
