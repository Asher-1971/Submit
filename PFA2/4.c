#include <stdio.h>

int getValidDays(void) {
    int numberOfDays;
    printf("Enter festival duration in days (1-7): ");
    scanf("%d", &numberOfDays);
    while (numberOfDays < 1 || numberOfDays > 7) {
        printf("Please enter a number from 1 to 7: ");
        scanf("%d", &numberOfDays);
    }
    return numberOfDays;
}

float calculateDailySales(int dayNumber) {
    int orderCount;
    float orderAmount;
    float totalSales = 0.0f;
    float highestOrder = 0.0f;

    printf("\nDay %d - Number of orders: ", dayNumber);
    scanf("%d", &orderCount);
    while (orderCount < 1) {
        printf("Enter at least one order: ");
        scanf("%d", &orderCount);
    }
    for (int order = 1; order <= orderCount; order++) {
        printf("Order %d amount (Rs.): ", order);
        scanf("%f", &orderAmount);
        while (orderAmount <= 0) {
            printf("Amount must be greater than zero. Enter again: ");
            scanf("%f", &orderAmount);
        }
        totalSales += orderAmount;
        if (orderAmount > highestOrder) {
            highestOrder = orderAmount;
        }
    }
    printf("Total sales: Rs. %.2f\n", totalSales);
    printf("Average order amount: Rs. %.2f\n", totalSales / orderCount);
    printf("Highest order amount: Rs. %.2f\n", highestOrder);
    return totalSales;
}

int findHighestSalesDay(float dailySales[], int numberOfDays) {
    int highestDay = 0;
    for (int day = 1; day < numberOfDays; day++) {
        if (dailySales[day] > dailySales[highestDay]) {
            highestDay = day;
        }
    }
    return highestDay + 1;
}

void displayBarChart(float dailySales[], int numberOfDays) {
    printf("\nDaily Sales Bar Chart\n");
    for (int day = 0; day < numberOfDays; day++) {
        int barLength = (int) (dailySales[day] / 100.0f);
        printf("Day %d: ", day + 1);
        for (int star = 0; star < barLength; star++) {
            printf("*");
        }
        printf(" (Rs. %.2f)\n", dailySales[day]);
    }
}

int main(void) {
    float dailySales[7];
    int numberOfDays = getValidDays();
    float festivalSales = 0.0f;

    for (int day = 0; day < numberOfDays; day++) {
        dailySales[day] = calculateDailySales(day + 1);
        festivalSales += dailySales[day];
    }

    int highestDay = findHighestSalesDay(dailySales, numberOfDays);
    printf("\nFestival total sales: Rs. %.2f\n", festivalSales);
    printf("Highest sales were on day %d: Rs. %.2f\n", highestDay, dailySales[highestDay - 1]);
    displayBarChart(dailySales, numberOfDays);
    return 0;
}
