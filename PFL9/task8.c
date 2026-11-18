#include <stdio.h>

struct Book
{
    int id;
    char title[50];
    char author[50];
};

void addBooks(void)
{
    FILE *file;
    struct Book book;
    int bookCount;
    int index;

    file = fopen("library.txt", "a");
    if (file == NULL)
    {
        printf("Unable to open library.txt.\n");
        return;
    }

    printf("How many books do you want to add? ");
    scanf("%d", &bookCount);

    for (index = 0; index < bookCount; index++)
    {
        printf("Enter book ID: ");
        scanf("%d", &book.id);
        printf("Enter book title: ");
        scanf("%49s", book.title);
        printf("Enter author name: ");
        scanf("%49s", book.author);
        fprintf(file, "%d %s|%s\n", book.id, book.title, book.author);
    }

    fclose(file);
    printf("Book records saved.\n");
}

void displayBooks(void)
{
    FILE *file;
    struct Book book;

    file = fopen("library.txt", "r");
    if (file == NULL)
    {
        printf("No library records were found.\n");
        return;
    }

    printf("\n--- Library Records ---\n");
    while (fscanf(file, "%d %49[^|]|%49[^\n]", &book.id, book.title, book.author) == 3)
        printf("ID: %d, Title: %s, Author: %s\n",
               book.id, book.title, book.author);

    fclose(file);
}

void searchBook(void)
{
    FILE *file;
    struct Book book;
    int searchId;
    int found = 0;

    file = fopen("library.txt", "r");
    if (file == NULL)
    {
        printf("No library records were found.\n");
        return;
    }

    printf("Enter the book ID to search for: ");
    scanf("%d", &searchId);

    while (fscanf(file, "%d %49[^|]|%49[^\n]", &book.id, book.title, book.author) == 3)
    {
        if (book.id == searchId)
        {
            printf("Book found: ID: %d, Title: %s, Author: %s\n",
                   book.id, book.title, book.author);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("No book with that ID was found.\n");

    fclose(file);
}

int main(void)
{
    int choice;

    do
    {
        printf("\n1. Add books\n");
        printf("2. Display books\n");
        printf("3. Search for a book\n");
        printf("4. Delete all records\n");
        printf("5. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        if (choice == 1)
            addBooks();
        else if (choice == 2)
            displayBooks();
        else if (choice == 3)
            searchBook();
        else if (choice == 4)
        {
            if (remove("library.txt") == 0)
                printf("All library records deleted.\n");
            else
                printf("No library file was found.\n");
        }
        else if (choice != 5)
            printf("Please choose a valid option.\n");
    } while (choice != 5);

    return 0;
}
