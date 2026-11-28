#include <ctype.h>
#include <errno.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book
{
    int id;
    char *title;
    float price;
    int quantity;
};

struct Book *allocateBooks(int n)
{
    struct Book *books;
    int index;

    if (n <= 0 || (size_t)n > (size_t)-1 / sizeof(*books))
        return NULL;

    books = malloc((size_t)n * sizeof(*books));
    if (books == NULL)
        return NULL;

    for (index = 0; index < n; index++)
        books[index].title = NULL;

    return books;
}

static void releaseBooks(struct Book *books, int n)
{
    int index;

    if (books == NULL)
        return;

    for (index = 0; index < n; index++)
    {
        free(books[index].title);
        books[index].title = NULL;
    }
    free(books);
}

static int readInteger(const char *prompt, int *value)
{
    char line[128];
    char *end;
    long parsedValue;

    while (1)
    {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL)
            return 0;

        errno = 0;
        parsedValue = strtol(line, &end, 10);
        if (end != line && errno != ERANGE &&
            parsedValue >= INT_MIN && parsedValue <= INT_MAX)
        {
            while (isspace((unsigned char)*end))
                end++;
            if (*end == '\0')
            {
                *value = (int)parsedValue;
                return 1;
            }
        }

        printf("Please enter a valid integer.\n");
    }
}

static int readPrice(const char *prompt, float *price)
{
    char line[128];
    char *end;
    double parsedPrice;

    while (1)
    {
        printf("%s", prompt);
        if (fgets(line, sizeof(line), stdin) == NULL)
            return 0;

        errno = 0;
        parsedPrice = strtod(line, &end);
        if (end != line && errno != ERANGE && isfinite(parsedPrice) &&
            parsedPrice >= 0.0 && parsedPrice <= FLT_MAX)
        {
            while (isspace((unsigned char)*end))
                end++;
            if (*end == '\0')
            {
                *price = (float)parsedPrice;
                return 1;
            }
        }

        printf("Please enter a valid non-negative price.\n");
    }
}

static int readTitle(char **title)
{
    size_t capacity = 64;
    size_t length = 0;
    char *buffer = malloc(capacity);
    int character;

    if (buffer == NULL)
    {
        perror("Could not allocate memory for a book title");
        return -1;
    }

    while (1)
    {
        character = getchar();
        if (character == EOF || character == '\n')
            break;
        if (character == '\r')
            continue;

        if (length + 1 >= capacity)
        {
            size_t newCapacity;
            char *resizedBuffer;

            if (capacity > (size_t)-1 / 2)
            {
                free(buffer);
                fprintf(stderr, "Book title is too long to store.\n");
                return -1;
            }

            newCapacity = capacity * 2;
            resizedBuffer = realloc(buffer, newCapacity);
            if (resizedBuffer == NULL)
            {
                perror("Could not grow the book title");
                free(buffer);
                return -1;
            }
            buffer = resizedBuffer;
            capacity = newCapacity;
        }

        buffer[length++] = (char)character;
    }

    if (character == EOF && length == 0)
    {
        free(buffer);
        return 0;
    }

    buffer[length] = '\0';
    *title = buffer;
    return 1;
}

static void trimTitle(char *title)
{
    char *start = title;
    size_t length;

    while (isspace((unsigned char)*start))
        start++;

    length = strlen(start);
    while (length > 0 && isspace((unsigned char)start[length - 1]))
        length--;

    memmove(title, start, length);
    title[length] = '\0';
}

static void stopInput(struct Book *books, int n)
{
    fprintf(stderr, "Input ended or memory allocation failed before all books were entered.\n");
    releaseBooks(books, n);
    exit(EXIT_FAILURE);
}

void inputBooks(struct Book *books, int n)
{
    int index;

    for (index = 0; index < n; index++)
    {
        int titleStatus;

        printf("\nBook %d:\n", index + 1);
        if (!readInteger("ID: ", &books[index].id))
            stopInput(books, n);

        do
        {
            printf("Title: ");
            titleStatus = readTitle(&books[index].title);
            if (titleStatus != 1)
                stopInput(books, n);
            trimTitle(books[index].title);
            if (books[index].title[0] == '\0')
            {
                free(books[index].title);
                books[index].title = NULL;
                printf("Title cannot be empty.\n");
            }
        } while (books[index].title == NULL);

        if (!readPrice("Price in rupees: ", &books[index].price) ||
            !readInteger("Quantity in stock: ", &books[index].quantity))
            stopInput(books, n);

        while (books[index].quantity < 0)
        {
            printf("Quantity cannot be negative.\n");
            if (!readInteger("Quantity in stock: ", &books[index].quantity))
                stopInput(books, n);
        }

    }
}

void displayBooks(struct Book *books, int n)
{
    int index;

    printf("\nID    Title                            Price       Qty\n");
    printf("------------------------------------------------------\n");
    for (index = 0; index < n; index++)
    {
        printf("%-5d %-32s Rs. %9.2f %7d\n",
               books[index].id, books[index].title,
               books[index].price, books[index].quantity);
    }
}

float calculateTotalValue(struct Book *books, int n)
{
    double total = 0.0;
    int index;

    for (index = 0; index < n; index++)
        total += (double)books[index].price * books[index].quantity;

    return (float)total;
}

int findMostExpensive(struct Book *books, int n)
{
    int mostExpensive = 0;
    int index;

    for (index = 1; index < n; index++)
    {
        if (books[index].price > books[mostExpensive].price)
            mostExpensive = index;
    }

    return mostExpensive;
}

static int comparePrices(const void *left, const void *right)
{
    float first = *(const float *)left;
    float second = *(const float *)right;

    if (first < second)
        return -1;
    if (first > second)
        return 1;
    return 0;
}

float calculateMedianPrice(struct Book *books, int n)
{
    float *prices;
    float median;
    int index;

    if (books == NULL || n <= 0 ||
        (size_t)n > (size_t)-1 / sizeof(*prices))
        return NAN;

    prices = malloc((size_t)n * sizeof(*prices));
    if (prices == NULL)
    {
        perror("Could not allocate memory for median calculation");
        return NAN;
    }

    for (index = 0; index < n; index++)
        prices[index] = books[index].price;

    qsort(prices, (size_t)n, sizeof(*prices), comparePrices);
    if (n % 2 == 1)
        median = prices[n / 2];
    else
        median = (float)(((double)prices[n / 2 - 1] + prices[n / 2]) / 2.0);

    free(prices);
    prices = NULL;
    return median;
}

float calculateReorderCost(struct Book *books, int n, int *reorderCount)
{
    double totalCost = 0.0;
    int index;

    if (reorderCount == NULL)
        return NAN;

    *reorderCount = 0;
    printf("\nReorder report (stock below 5, restock to 10 copies):\n");
    for (index = 0; index < n; index++)
    {
        if (books[index].quantity < 5)
        {
            int copiesToOrder = 10 - books[index].quantity;
            double cost = (double)books[index].price * 0.80 * copiesToOrder;

            printf("%s - order %d copies - Rs. %.2f\n",
                   books[index].title, copiesToOrder, cost);
            totalCost += cost;
            (*reorderCount)++;
        }
    }

    return (float)totalCost;
}

int main(void)
{
    struct Book *books;
    int bookCount;
    int mostExpensive;
    int reorderCount;
    float totalValue;
    float medianPrice;
    float reorderCost;

    while (1)
    {
        if (!readInteger("Number of books: ", &bookCount))
        {
            fprintf(stderr, "Could not read the number of books.\n");
            return 1;
        }
        if (bookCount > 0)
            break;
        printf("Number of books must be greater than zero.\n");
    }

    books = allocateBooks(bookCount);
    if (books == NULL)
    {
        perror("Could not allocate memory for the books");
        return 1;
    }

    inputBooks(books, bookCount);
    displayBooks(books, bookCount);

    totalValue = calculateTotalValue(books, bookCount);
    mostExpensive = findMostExpensive(books, bookCount);
    medianPrice = calculateMedianPrice(books, bookCount);
    if (isnan(medianPrice))
    {
        releaseBooks(books, bookCount);
        books = NULL;
        return 1;
    }

    printf("\nTotal inventory value: Rs. %.2f\n", totalValue);
    printf("Most expensive book: %s (Rs. %.2f)\n",
           books[mostExpensive].title, books[mostExpensive].price);
    printf("Median price: Rs. %.2f\n", medianPrice);

    reorderCost = calculateReorderCost(books, bookCount, &reorderCount);
    if (reorderCount == 0)
        printf("No books need to be reordered.\n");
    else
        printf("Books to reorder: %d\n", reorderCount);
    if (reorderCount > 0)
        printf("Total reorder cost: Rs. %.2f\n", reorderCost);

    releaseBooks(books, bookCount);
    books = NULL;
    return 0;
}
