#include <stdio.h>
#include <string.h>

void displayMenu(void) {
    printf("\nUniversity Library Management System\n");
    printf("1. Register member\n");
    printf("2. Display available books\n");
    printf("3. Borrow a book\n");
    printf("4. Return a book\n");
    printf("5. Display member record\n");
    printf("6. Exit\n");
    printf("Choose an option: ");
}

void registerMember(char name[], int *studentId, int *memberType) {
    printf("Enter member name: ");
    scanf(" %49[^\n]", name);
    printf("Enter student ID: ");
    scanf("%d", studentId);
    do {
        printf("Enter membership type (1 for Student, 2 for Faculty): ");
        scanf("%d", memberType);
        if (*memberType != 1 && *memberType != 2) {
            printf("Please choose 1 or 2.\n");
        }
    } while (*memberType != 1 && *memberType != 2);
    printf("Member registered successfully.\n");
}

void displayBooks(int bookIds[], char bookTitles[][50], int availableCopies[], int totalBooks) {
    printf("\nAvailable Books\n");
    printf("%-10s %-35s %s\n", "Book ID", "Title", "Copies");
    for (int book = 0; book < totalBooks; book++) {
        printf("%-10d %-35s %d\n", bookIds[book], bookTitles[book], availableCopies[book]);
    }
}

void borrowBook(int bookIds[], char bookTitles[][50], int availableCopies[],
                int totalBooks, int borrowedBookIds[], int *borrowedCount, int memberType) {
    int bookId;
    int keepDays;
    int bookIndex = -1;
    printf("Enter book ID to borrow: ");
    scanf("%d", &bookId);
    for (int book = 0; book < totalBooks; book++) {
        if (bookIds[book] == bookId) {
            bookIndex = book;
            break;
        }
    }
    if (bookIndex == -1) {
        printf("Invalid book ID.\n");
        return;
    }
    if (availableCopies[bookIndex] == 0) {
        printf("No copies of this book are available.\n");
        return;
    }
    if (*borrowedCount >= 3) {
        printf("You cannot borrow more than three books at a time.\n");
        return;
    }
    printf("Enter intended borrowing days (maximum %d): ", memberType == 1 ? 14 : 30);
    scanf("%d", &keepDays);
    while (keepDays <= 0) {
        printf("The number of days must be positive. Enter again: ");
        scanf("%d", &keepDays);
    }
    borrowedBookIds[*borrowedCount] = bookId;
    (*borrowedCount)++;
    availableCopies[bookIndex]--;
    printf("Book borrowed: %s\n", bookTitles[bookIndex]);
    printf("A fine may apply if the book is kept beyond the permitted period.\n");
}

float returnBook(int bookIds[], int availableCopies[], int totalBooks,
                 int borrowedBookIds[], int *borrowedCount, int memberType, float *totalFine) {
    int bookId;
    int actualDays;
    int borrowedIndex = -1;
    int bookIndex = -1;
    printf("Enter book ID to return: ");
    scanf("%d", &bookId);
    for (int index = 0; index < *borrowedCount; index++) {
        if (borrowedBookIds[index] == bookId) {
            borrowedIndex = index;
            break;
        }
    }
    if (borrowedIndex == -1) {
        printf("This member has not borrowed that book.\n");
        return 0.0f;
    }
    for (int book = 0; book < totalBooks; book++) {
        if (bookIds[book] == bookId) {
            bookIndex = book;
            break;
        }
    }
    printf("Enter actual number of days kept: ");
    scanf("%d", &actualDays);
    while (actualDays <= 0) {
        printf("The number of days must be positive. Enter again: ");
        scanf("%d", &actualDays);
    }

    int allowedDays = memberType == 1 ? 14 : 30;
    int extraDays = actualDays > allowedDays ? actualDays - allowedDays : 0;
    float fineBeforeWaiver = extraDays * (memberType == 1 ? 20.0f : 10.0f);
    float finePayable = fineBeforeWaiver;
    char membershipCode[20];

    if (fineBeforeWaiver > 0) {
        printf("Enter membership code for a possible 50%% waiver: ");
        scanf("%19s", membershipCode);
        if (strcmp(membershipCode, "LIB2026") == 0) {
            finePayable *= 0.5f;
            printf("Correct code. A 50%% waiver was applied.\n");
        } else {
            printf("Incorrect code. No waiver was applied.\n");
        }
    }

    availableCopies[bookIndex]++;
    for (int index = borrowedIndex; index < *borrowedCount - 1; index++) {
        borrowedBookIds[index] = borrowedBookIds[index + 1];
    }
    (*borrowedCount)--;
    *totalFine += fineBeforeWaiver;
    printf("Book returned successfully.\n");
    printf("Fine before waiver: Rs. %.2f\n", fineBeforeWaiver);
    printf("Fine payable for this return: Rs. %.2f\n", finePayable);
    return finePayable;
}

void displayMemberRecord(char name[], int studentId, int memberType,
                         int borrowedBookIds[], int borrowedCount,
                         float totalFine, float fineAfterWaiver) {
    printf("\nMember Record\n");
    printf("Name: %s\n", name);
    printf("Student ID: %d\n", studentId);
    printf("Membership type: %s\n", memberType == 1 ? "Student" : "Faculty");
    printf("Currently borrowed books: ");
    if (borrowedCount == 0) {
        printf("None");
    } else {
        for (int index = 0; index < borrowedCount; index++) {
            printf("%d%s", borrowedBookIds[index], index == borrowedCount - 1 ? "" : ", ");
        }
    }
    printf("\nTotal fine before waivers: Rs. %.2f\n", totalFine);
    printf("Final fine payable after waivers: Rs. %.2f\n", fineAfterWaiver);
}

int main(void) {
    int bookIds[] = {101, 102, 103, 104, 105};
    char bookTitles[][50] = {
        "Introduction to Algorithms",
        "C Programming Fundamentals",
        "Data Structures in C",
        "Computer Networks",
        "Database Systems"
    };
    int availableCopies[] = {3, 4, 2, 3, 2};
    int totalBooks = 5;
    char memberName[50] = "";
    int studentId = 0;
    int memberType = 0;
    int borrowedBookIds[3];
    int borrowedCount = 0;
    float totalFine = 0.0f;
    float fineAfterWaiver = 0.0f;
    int choice;

    do {
        displayMenu();
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                registerMember(memberName, &studentId, &memberType);
                break;
            case 2:
                displayBooks(bookIds, bookTitles, availableCopies, totalBooks);
                break;
            case 3:
                if (memberType == 0) {
                    printf("Please register a member first.\n");
                } else {
                    borrowBook(bookIds, bookTitles, availableCopies, totalBooks,
                               borrowedBookIds, &borrowedCount, memberType);
                }
                break;
            case 4:
                if (memberType == 0) {
                    printf("Please register a member first.\n");
                } else {
                    fineAfterWaiver += returnBook(bookIds, availableCopies, totalBooks,
                                                  borrowedBookIds, &borrowedCount,
                                                  memberType, &totalFine);
                }
                break;
            case 5:
                if (memberType == 0) {
                    printf("Please register a member first.\n");
                } else {
                    displayMemberRecord(memberName, studentId, memberType,
                                        borrowedBookIds, borrowedCount,
                                        totalFine, fineAfterWaiver);
                }
                break;
            case 6:
                printf("Thank you for using the library system.\n");
                break;
            default:
                printf("Invalid choice. Please select an option from 1 to 6.\n");
        }
    } while (choice != 6);

    return 0;
}
