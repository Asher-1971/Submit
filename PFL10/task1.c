#include <stdio.h>
#include <string.h>

int readLine(const char *prompt, char *value, int size)
{
    int character;

    printf("%s", prompt);
    if (fgets(value, size, stdin) == NULL)
        return 0;

    if (strchr(value, '\n') == NULL)
    {
        while ((character = getchar()) != '\n' && character != EOF)
        {
        }
    }

    value[strcspn(value, "\r\n")] = '\0';
    return 1;
}

int readInt(const char *prompt, int *value)
{
    char input[100];

    if (!readLine(prompt, input, sizeof(input)))
        return 0;

    return sscanf(input, "%d", value) == 1;
}

int readAmount(const char *prompt, double *amount)
{
    char input[100];

    if (!readLine(prompt, input, sizeof(input)))
        return 0;

    return sscanf(input, "%lf", amount) == 1;
}

int main(void)
{
    FILE *file;
    int expenseCount;
    int index;
    char description[100];
    double amount;
    char line[200];

    if (!readInt("How many expenses do you want to enter? ", &expenseCount) ||
        expenseCount < 1)
    {
        printf("Please enter a valid number of expenses.\n");
        return 1;
    }

    file = fopen("expenses.txt", "w");
    if (file == NULL)
    {
        perror("Could not open expenses.txt");
        return 1;
    }

    for (index = 0; index < expenseCount; index++)
    {
        printf("\nExpense %d\n", index + 1);
        if (!readLine("Description: ", description, sizeof(description)) ||
            !readAmount("Amount: ", &amount))
        {
            printf("Please enter a valid expense.\n");
            fclose(file);
            return 1;
        }

        if (fprintf(file, "%s | %.2f\n", description, amount) < 0)
        {
            perror("Could not save an expense");
            fclose(file);
            return 1;
        }
    }

    if (fclose(file) != 0)
    {
        perror("Could not close expenses.txt");
        return 1;
    }

    file = fopen("expenses.txt", "r");
    if (file == NULL)
    {
        perror("Could not read expenses.txt");
        return 1;
    }

    printf("\nSaved expenses:\n");
    while (fgets(line, sizeof(line), file) != NULL)
        printf("%s", line);

    if (ferror(file))
    {
        perror("Could not read expenses.txt");
        fclose(file);
        return 1;
    }

    if (fclose(file) != 0)
    {
        perror("Could not close expenses.txt");
        return 1;
    }

    return 0;
}
