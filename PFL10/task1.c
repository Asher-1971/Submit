#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
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
    char *end;
    long parsedValue;

    if (!readLine(prompt, input, sizeof(input)))
        return 0;

    errno = 0;
    parsedValue = strtol(input, &end, 10);
    if (end == input || errno == ERANGE ||
        parsedValue < INT_MIN || parsedValue > INT_MAX)
        return 0;

    while (isspace((unsigned char)*end))
        end++;

    if (*end != '\0')
        return 0;

    *value = (int)parsedValue;
    return 1;
}

int readAmount(const char *prompt, double *amount)
{
    char input[100];
    char *end;
    double parsedAmount;

    if (!readLine(prompt, input, sizeof(input)))
        return 0;

    errno = 0;
    parsedAmount = strtod(input, &end);
    if (end == input || errno == ERANGE || !isfinite(parsedAmount) ||
        parsedAmount < 0.0)
        return 0;

    while (isspace((unsigned char)*end))
        end++;

    if (*end != '\0')
        return 0;

    *amount = parsedAmount;
    return 1;
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
