#include <stdio.h>

int main(void) {
    int rowCount;
    int seatCount;

    printf("Cinema Hall Seat Booking System\n");
    printf("Enter number of rows: ");
    scanf("%d", &rowCount);
    printf("Enter seats per row: ");
    scanf("%d", &seatCount);

    while (rowCount <= 0 || seatCount <= 0) {
        printf("Rows and seats must be greater than zero.\n");
        printf("Enter number of rows: ");
        scanf("%d", &rowCount);
        printf("Enter seats per row: ");
        scanf("%d", &seatCount);
    }

    int seats[rowCount][seatCount];
    int row;
    int seat;
    int availableCount;

    printf("Enter seating status using 0 for available and 1 for booked.\n");
    for (row = 0; row < rowCount; row++) {
        for (seat = 0; seat < seatCount; seat++) {
            do {
                printf("Row %d, seat %d: ", row, seat);
                scanf("%d", &seats[row][seat]);
                if (seats[row][seat] != 0 && seats[row][seat] != 1) {
                    printf("Please enter only 0 or 1.\n");
                }
            } while (seats[row][seat] != 0 && seats[row][seat] != 1);
        }
    }

    printf("\nCurrent Seating Arrangement\n    ");
    for (seat = 0; seat < seatCount; seat++) {
        printf("%2d ", seat);
    }
    printf("\n");
    for (row = 0; row < rowCount; row++) {
        printf("%2d  ", row);
        for (seat = 0; seat < seatCount; seat++) {
            printf("%2c ", seats[row][seat] == 0 ? '_' : 'X');
        }
        printf("\n");
    }

    availableCount = 0;
    printf("\nSeat Availability Report\n");
    for (row = 0; row < rowCount; row++) {
        int rowAvailable = 0;
        for (seat = 0; seat < seatCount; seat++) {
            if (seats[row][seat] == 0) {
                rowAvailable++;
            }
        }
        availableCount += rowAvailable;
        printf("Row %d: %d available seat(s)\n", row, rowAvailable);
    }
    printf("Total available seats: %d\n", availableCount);

    int groupSize;
    printf("\nEnter number of customers who want to sit together: ");
    scanf("%d", &groupSize);
    while (groupSize <= 0 || groupSize > seatCount) {
        printf("Group size must be between 1 and %d. Enter again: ", seatCount);
        scanf("%d", &groupSize);
    }

    int selectedRow = -1;
    int selectedStart = -1;
    int middleRow = rowCount / 2;
    int distance;

    for (distance = 0; distance < rowCount && selectedRow == -1; distance++) {
        int candidateRows[2];
        int candidateCount = 0;
        int lowerRow = middleRow - distance;
        int upperRow = middleRow + distance;
        if (lowerRow >= 0) {
            candidateRows[candidateCount++] = lowerRow;
        }
        if (distance > 0 && upperRow < rowCount) {
            candidateRows[candidateCount++] = upperRow;
        }
        for (int candidateIndex = 0; candidateIndex < candidateCount && selectedRow == -1; candidateIndex++) {
            int currentRow = candidateRows[candidateIndex];
            int consecutiveSeats = 0;
            for (seat = 0; seat < seatCount; seat++) {
                if (seats[currentRow][seat] == 0) {
                    consecutiveSeats++;
                    if (consecutiveSeats == groupSize) {
                        selectedRow = currentRow;
                        selectedStart = seat - groupSize + 1;
                        break;
                    }
                } else {
                    consecutiveSeats = 0;
                }
            }
        }
    }

    if (selectedRow == -1) {
        printf("No row has %d consecutive available seats. No booking was made.\n", groupSize);
    } else {
        for (seat = selectedStart; seat < selectedStart + groupSize; seat++) {
            seats[selectedRow][seat] = 1;
        }
        printf("Booking confirmed in row %d for seats %d through %d.\n",
               selectedRow, selectedStart, selectedStart + groupSize - 1);
        availableCount -= groupSize;
        printf("Remaining available seats: %d\n", availableCount);
        printf("\nUpdated Seating Arrangement\n    ");
        for (seat = 0; seat < seatCount; seat++) {
            printf("%2d ", seat);
        }
        printf("\n");
        for (row = 0; row < rowCount; row++) {
            printf("%2d  ", row);
            for (seat = 0; seat < seatCount; seat++) {
                printf("%2c ", seats[row][seat] == 0 ? '_' : 'X');
            }
            printf("\n");
        }
    }

    return 0;
}
