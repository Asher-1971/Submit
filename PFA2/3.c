#include <stdio.h>

typedef struct {
    int total;
    double average;
    int highest;
    int lowest;
    int criticalCount;
    int warningCount;
    int longestStreak;
} SensorReport;

void inputReadings(int readings[][100], int sensorCount, int hourCount) {
    for (int sensor = 0; sensor < sensorCount; sensor++) {
        printf("\nSensor %d\n", sensor);
        for (int hour = 0; hour < hourCount; hour++) {
            printf("Enter temperature for hour %d: ", hour + 1);
            scanf("%d", &readings[sensor][hour]);
        }
    }
}

SensorReport analyzeSensor(int sensorReadings[], int hourCount) {
    SensorReport report = {0, 0.0, sensorReadings[0], sensorReadings[0], 0, 0, 0};
    int currentStreak = 0;

    for (int hour = 0; hour < hourCount; hour++) {
        int temperature = sensorReadings[hour];
        report.total += temperature;
        if (temperature > report.highest) {
            report.highest = temperature;
        }
        if (temperature < report.lowest) {
            report.lowest = temperature;
        }
        if (temperature >= 40) {
            report.criticalCount++;
        } else if (temperature >= 35) {
            report.warningCount++;
        }
        if (temperature >= 35) {
            currentStreak++;
            if (currentStreak > report.longestStreak) {
                report.longestStreak = currentStreak;
            }
        } else {
            currentStreak = 0;
        }
    }
    report.average = (double) report.total / hourCount;
    return report;
}

int findHighestAverage(SensorReport reports[], int sensorCount) {
    int highestSensor = 0;
    for (int sensor = 1; sensor < sensorCount; sensor++) {
        if (reports[sensor].average > reports[highestSensor].average) {
            highestSensor = sensor;
        }
    }
    return highestSensor;
}

int main(void) {
    int sensorCount;
    int hourCount;

    printf("Greenhouse Temperature Monitoring System\n");
    printf("Enter number of sensors: ");
    scanf("%d", &sensorCount);
    printf("Enter number of hourly readings: ");
    scanf("%d", &hourCount);
    while (sensorCount <= 0 || sensorCount > 100 || hourCount <= 0 || hourCount > 100) {
        printf("Enter values from 1 to 100 for both counts.\n");
        printf("Enter number of sensors: ");
        scanf("%d", &sensorCount);
        printf("Enter number of hourly readings: ");
        scanf("%d", &hourCount);
    }

    int readings[sensorCount][100];
    SensorReport reports[sensorCount];
    inputReadings(readings, sensorCount, hourCount);

    for (int sensor = 0; sensor < sensorCount; sensor++) {
        reports[sensor] = analyzeSensor(readings[sensor], hourCount);
        printf("\nReport for Sensor %d\n", sensor);
        printf("Total: %d\n", reports[sensor].total);
        printf("Average: %.2f C\n", reports[sensor].average);
        printf("Highest: %d C\n", reports[sensor].highest);
        printf("Lowest: %d C\n", reports[sensor].lowest);
        printf("Critical readings: %d\n", reports[sensor].criticalCount);
        printf("Warning readings: %d\n", reports[sensor].warningCount);
        printf("Longest streak at 35 C or above: %d hour(s)\n", reports[sensor].longestStreak);
    }

    int highestSensor = findHighestAverage(reports, sensorCount);
    printf("\nHighest average temperature: Sensor %d with %.2f C\n",
           highestSensor, reports[highestSensor].average);
    return 0;
}
