#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int bookID;
    char title[100];
    char author[100];
    int availableCopies;
} Book;

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

int findBook(int bookID, Book *result)
{
    FILE *file = fopen("books.dat", "rb");
    Book book;
    int found = 0;

    if (file == NULL)
    {
        if (errno == ENOENT)
            return 0;
        perror("Could not open books.dat");
        return -1;
    }

    while (fread(&book, sizeof(Book), 1, file) == 1)
    {
        if (book.bookID == bookID)
        {
            if (result != NULL)
                *result = book;
            found = 1;
            break;
        }
    }

    if (ferror(file))
    {
        perror("Could not read books.dat");
        found = -1;
    }

    if (fclose(file) != 0)
    {
        perror("Could not close books.dat");
        found = -1;
    }

    return found;
}

int readBook(Book *book)
{
    if (!readInt("Book ID: ", &book->bookID) ||
        !readLine("Title: ", book->title, sizeof(book->title)) ||
        !readLine("Author: ", book->author, sizeof(book->author)) ||
        !readInt("Available copies: ", &book->availableCopies))
        return 0;

    if (book->bookID <= 0 || book->availableCopies < 0)
    {
        printf("Book ID must be positive and copies cannot be negative.\n");
        return -1;
    }

    return 1;
}

void displayBook(const Book *book)
{
    printf("Book ID: %d\n", book->bookID);
    printf("Title: %s\n", book->title);
    printf("Author: %s\n", book->author);
    printf("Available copies: %d\n", book->availableCopies);
}

void addBooks(void)
{
    FILE *file;
    int bookCount;
    int index;
    int result;
    Book book;

    if (!readInt("How many books do you want to add? ", &bookCount) ||
        bookCount < 1)
    {
        printf("Please enter a valid number of books.\n");
        return;
    }

    file = fopen("books.dat", "ab");
    if (file == NULL)
    {
        perror("Could not open books.dat");
        return;
    }

    for (index = 0; index < bookCount; index++)
    {
        printf("\nBook %d\n", index + 1);
        result = readBook(&book);
        if (result != 1)
        {
            if (result == 0)
                printf("Book entry was cancelled.\n");
            break;
        }

        result = findBook(book.bookID, NULL);
        if (result == 1)
        {
            printf("That book ID already exists. This book was not added.\n");
            continue;
        }
        if (result == -1)
            break;

        if (fwrite(&book, sizeof(Book), 1, file) != 1)
        {
            perror("Could not save the book");
            break;
        }

        if (fflush(file) != 0)
        {
            perror("Could not save the book");
            break;
        }
    }

    if (fclose(file) != 0)
        perror("Could not close books.dat");
}

void displayBooks(void)
{
    FILE *file = fopen("books.dat", "rb");
    Book book;
    int found = 0;

    if (file == NULL)
    {
        if (errno == ENOENT)
            printf("No books have been saved.\n");
        else
            perror("Could not open books.dat");
        return;
    }

    while (fread(&book, sizeof(Book), 1, file) == 1)
    {
        printf("\n");
        displayBook(&book);
        found = 1;
    }

    if (ferror(file))
        perror("Could not read books.dat");
    else if (!found)
        printf("No books have been saved.\n");

    if (fclose(file) != 0)
        perror("Could not close books.dat");
}

void searchBook(void)
{
    int bookID;
    int result;
    Book book;

    if (!readInt("Enter the book ID to search for: ", &bookID))
    {
        printf("Please enter a valid book ID.\n");
        return;
    }

    result = findBook(bookID, &book);
    if (result == 1)
        displayBook(&book);
    else if (result == 0)
        printf("No book with that ID was found.\n");
}

void updateBook(void)
{
    FILE *file;
    Book book;
    int bookID;
    int copies;
    int found = 0;

    if (!readInt("Enter the book ID to update: ", &bookID) ||
        !readInt("Enter the new number of available copies: ", &copies) ||
        copies < 0)
    {
        printf("Please enter a valid book ID and non-negative copy count.\n");
        return;
    }

    file = fopen("books.dat", "r+b");
    if (file == NULL)
    {
        if (errno == ENOENT)
            printf("No book with that ID was found.\n");
        else
            perror("Could not open books.dat");
        return;
    }

    while (fread(&book, sizeof(Book), 1, file) == 1)
    {
        if (book.bookID == bookID)
        {
            book.availableCopies = copies;
            if (fseek(file, -(long)sizeof(Book), SEEK_CUR) != 0 ||
                fwrite(&book, sizeof(Book), 1, file) != 1)
                perror("Could not update the book");
            else
            {
                printf("Book record updated.\n");
                found = 1;
            }
            break;
        }
    }

    if (ferror(file))
        perror("Could not read books.dat");
    else if (!found)
        printf("No book with that ID was found.\n");

    if (fclose(file) != 0)
        perror("Could not close books.dat");
}

void deleteBook(void)
{
    FILE *source;
    FILE *temporary;
    Book book;
    int bookID;
    int found = 0;
    int failed = 0;

    if (!readInt("Enter the book ID to delete: ", &bookID))
    {
        printf("Please enter a valid book ID.\n");
        return;
    }

    source = fopen("books.dat", "rb");
    if (source == NULL)
    {
        if (errno == ENOENT)
            printf("No book with that ID was found.\n");
        else
            perror("Could not open books.dat");
        return;
    }

    temporary = fopen("books.tmp", "wb");
    if (temporary == NULL)
    {
        perror("Could not create a temporary book file");
        fclose(source);
        return;
    }

    while (fread(&book, sizeof(Book), 1, source) == 1)
    {
        if (book.bookID == bookID)
            found = 1;
        else if (fwrite(&book, sizeof(Book), 1, temporary) != 1)
        {
            perror("Could not write a temporary book record");
            failed = 1;
            break;
        }
    }

    if (ferror(source))
    {
        perror("Could not read books.dat");
        failed = 1;
    }

    if (fclose(source) != 0)
    {
        perror("Could not close books.dat");
        failed = 1;
    }

    if (fclose(temporary) != 0)
    {
        perror("Could not close the temporary book file");
        failed = 1;
    }

    if (failed)
    {
        remove("books.tmp");
        return;
    }

    if (!found)
    {
        printf("No book with that ID was found.\n");
        remove("books.tmp");
        return;
    }

    if (remove("books.bak") != 0 && errno != ENOENT)
    {
        perror("Could not remove the previous backup");
        remove("books.tmp");
        return;
    }

    if (rename("books.dat", "books.bak") != 0)
    {
        perror("Could not preserve the current book file");
        remove("books.tmp");
        return;
    }

    if (rename("books.tmp", "books.dat") != 0)
    {
        perror("Could not replace the book file");
        if (rename("books.bak", "books.dat") != 0)
            perror("Could not restore the original book file");
        return;
    }

    if (remove("books.bak") != 0)
        perror("Book was deleted, but the backup file could not be removed");
    else
        printf("Book record deleted.\n");
}

int main(void)
{
    int choice;

    while (1)
    {
        printf("\nLibrary Book Record System\n");
        printf("1. Add books\n");
        printf("2. Display all books\n");
        printf("3. Search for a book\n");
        printf("4. Update available copies\n");
        printf("5. Delete a book\n");
        printf("6. Exit\n");

        if (!readInt("Choose an option: ", &choice))
        {
            printf("Please enter a valid option.\n");
            continue;
        }

        if (choice == 1)
            addBooks();
        else if (choice == 2)
            displayBooks();
        else if (choice == 3)
            searchBook();
        else if (choice == 4)
            updateBook();
        else if (choice == 5)
            deleteBook();
        else if (choice == 6)
            break;
        else
            printf("Please choose an option from 1 to 6.\n");
    }

    return 0;
}
