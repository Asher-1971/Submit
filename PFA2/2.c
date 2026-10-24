#include <stdio.h>

int sumProperDivisors(int number) {
    int divisor;
    int divisorSum = 0;
    for (divisor = 1; divisor <= number / 2; divisor++) {
        if (number % divisor == 0) {
            divisorSum += divisor;
        }
    }
    return divisorSum;
}

int main(void) {
    int limit;
    int firstNumber;
    int secondNumber;
    int pairCount = 0;

    printf("Amicable Pair Finder\n");
    printf("Enter a positive upper limit: ");
    scanf("%d", &limit);
    while (limit <= 0) {
        printf("The limit must be positive. Enter again: ");
        scanf("%d", &limit);
    }

    printf("\nAmicable pairs up to %d:\n", limit);
    for (firstNumber = 2; firstNumber <= limit; firstNumber++) {
        secondNumber = sumProperDivisors(firstNumber);
        if (secondNumber > firstNumber && secondNumber <= limit &&
            sumProperDivisors(secondNumber) == firstNumber) {
            printf("(%d, %d)\n", firstNumber, secondNumber);
            pairCount++;
        }
    }

    if (pairCount == 0) {
        printf("No amicable pairs were found.\n");
    } else {
        printf("Total amicable pairs found: %d\n", pairCount);
    }
    return 0;
}
