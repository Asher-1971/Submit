#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char itemName[100];
    char location[100];
    char contactID[50];
} LostFoundRecord;

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

int readRequiredLine(const char *prompt, char *value, int size)
{
    char *start;
    char *end;
    size_t length;

    while (1)
    {
        if (!readLine(prompt, value, size))
            return 0;

        start = value;
        while (isspace((unsigned char)*start))
            start++;

        end = start + strlen(start);
        while (end > start && isspace((unsigned char)end[-1]))
            end--;

        length = (size_t)(end - start);
        memmove(value, start, length);
        value[length] = '\0';

        if (value[0] == '\0' || strchr(value, '|') != NULL)
        {
            printf("Enter a nonblank value without the | character.\n");
            continue;
        }

        return 1;
    }
}

int readRecord(FILE *file, LostFoundRecord *record)
{
    char line[260];

    if (fgets(line, sizeof(line), file) == NULL)
        return 0;

    return sscanf(line, "%99[^|]|%99[^|]|%49[^\r\n]",
                  record->itemName, record->location, record->contactID) == 3;
}

void displayRecords(void)
{
    FILE *file = fopen("lostfound.txt", "r");
    LostFoundRecord record;
    int found = 0;

    if (file == NULL)
    {
        perror("Could not open lostfound.txt");
        return;
    }

    printf("\nSaved lost and found records:\n");
    while (readRecord(file, &record))
    {
        printf("Item: %s | Location: %s | Contact ID: %s\n",
               record.itemName, record.location, record.contactID);
        found = 1;
    }

    if (ferror(file))
        perror("Could not read lostfound.txt");
    else if (!found)
        printf("No records have been saved.\n");

    if (fclose(file) != 0)
        perror("Could not close lostfound.txt");
}

void searchRecords(const char *itemName)
{
    FILE *file = fopen("lostfound.txt", "r");
    LostFoundRecord record;
    int found = 0;

    if (file == NULL)
    {
        perror("Could not open lostfound.txt");
        return;
    }

    while (readRecord(file, &record))
    {
        if (strcmp(record.itemName, itemName) == 0)
        {
            printf("\nMatching record:\n");
            printf("Item: %s\n", record.itemName);
            printf("Location: %s\n", record.location);
            printf("Contact ID: %s\n", record.contactID);
            found = 1;
        }
    }

    if (ferror(file))
        perror("Could not read lostfound.txt");
    else if (!found)
        printf("\nNo matching record was found.\n");

    if (fclose(file) != 0)
        perror("Could not close lostfound.txt");
}

int main(void)
{
    FILE *file;
    int recordCount;
    int index;
    LostFoundRecord record;
    char searchName[100];

    if (!readInt("How many records do you want to add? ", &recordCount) ||
        recordCount < 1)
    {
        printf("Please enter a valid number of records.\n");
        return 1;
    }

    file = fopen("lostfound.txt", "a");
    if (file == NULL)
    {
        perror("Could not open lostfound.txt");
        return 1;
    }

    for (index = 0; index < recordCount; index++)
    {
        printf("\nRecord %d\n", index + 1);
        if (!readRequiredLine("Item name: ", record.itemName, sizeof(record.itemName)) ||
            !readRequiredLine("Location: ", record.location, sizeof(record.location)) ||
            !readRequiredLine("Student contact ID: ", record.contactID, sizeof(record.contactID)))
        {
            printf("Please enter a complete record.\n");
            fclose(file);
            return 1;
        }

        if (fprintf(file, "%s|%s|%s\n", record.itemName,
                    record.location, record.contactID) < 0)
        {
            perror("Could not save a record");
            fclose(file);
            return 1;
        }
    }

    if (fclose(file) != 0)
    {
        perror("Could not close lostfound.txt");
        return 1;
    }

    displayRecords();

    if (!readRequiredLine("\nEnter an item name to search for: ",
                          searchName, sizeof(searchName)))
        return 1;

    searchRecords(searchName);

    return 0;
}
