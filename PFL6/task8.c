#include <stdio.h>

int main(void)
{
    int vehicleType, age, hasPass, isWeekend, isPeakHour, hours;
    int validVehicle = 1;
    double originalFee = 0, surcharge = 0, discount = 0, finalAmount;

    printf("Enter vehicle type (1 for Car, 2 for Motorcycle, 3 for Electric Vehicle): ");
    scanf("%d", &vehicleType);
    printf("Enter driver age: ");
    scanf("%d", &age);
    printf("Has a valid parking pass? (1 for yes, 0 for no): ");
    scanf("%d", &hasPass);
    printf("Is today a weekend? (1 for yes, 0 for no): ");
    scanf("%d", &isWeekend);
    printf("Is this a peak hour? (1 for yes, 0 for no): ");
    scanf("%d", &isPeakHour);
    printf("Enter parking hours: ");
    scanf("%d", &hours);

    if (vehicleType < 1)
        validVehicle = 0;
    else
    {
        if (vehicleType > 3)
            validVehicle = 0;
    }

    if (validVehicle == 0)
        printf("Invalid vehicle type\n");
    else
    {
        if (age < 18)
            printf("Driver is under 18\n");
        else
        {
            if (hasPass == 1)
                validVehicle = 1;
            else
            {
                if (isWeekend == 0)
                    validVehicle = 1;
                else
                {
                    if (vehicleType == 3)
                        validVehicle = 1;
                    else
                        validVehicle = 0;
                }
            }

            if (validVehicle == 0)
                printf("Parking entry conditions not satisfied\n");
            else
            {
                if (vehicleType == 3)
                {
                    if (hours <= 3)
                        originalFee = 0;
                    else
                        originalFee = (hours - 3) * 100;
                }
                else
                {
                    if (vehicleType == 2)
                        originalFee = hours * 100;
                    else
                        originalFee = hours * 200;
                }

                if (isWeekend == 1)
                {
                    if (isPeakHour == 1)
                        surcharge = originalFee * 0.20;
                }

                if (hasPass == 1)
                    discount = (originalFee + surcharge) * 0.25;

                finalAmount = originalFee + surcharge - discount;
                printf("Entry allowed\n");
                if (vehicleType == 1)
                    printf("Vehicle Type: Car\n");
                else
                {
                    if (vehicleType == 2)
                        printf("Vehicle Type: Motorcycle\n");
                    else
                        printf("Vehicle Type: Electric Vehicle\n");
                }
                printf("Parking Hours: %d\n", hours);
                printf("Original Parking Fee: %.2f\n", originalFee);
                printf("Surcharge: %.2f\n", surcharge);
                printf("Discount: %.2f\n", discount);
                printf("Final Amount: %.2f\n", finalAmount);
            }
        }
    }

    return 0;
}