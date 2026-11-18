#include <stdio.h>

int processExits(int parkedVehicles, int vehiclesToExit)
{
    if (vehiclesToExit == 0)
        return parkedVehicles;

    parkedVehicles--;
    printf("Vehicles remaining after exit %d: %d\n",
           vehiclesToExit, parkedVehicles);
    return processExits(parkedVehicles, vehiclesToExit - 1);
}

int main(void)
{
    int parkedVehicles;
    int vehiclesToExit;
    int remainingVehicles;

    printf("Enter the number of parked vehicles: ");
    scanf("%d", &parkedVehicles);
    printf("Enter the number of vehicles leaving: ");
    scanf("%d", &vehiclesToExit);

    if (parkedVehicles < 0 || vehiclesToExit < 0 ||
        vehiclesToExit > parkedVehicles)
    {
        printf("Please enter valid vehicle counts.\n");
        return 1;
    }

    remainingVehicles = processExits(parkedVehicles, vehiclesToExit);
    printf("Total vehicles exited: %d\n", vehiclesToExit);
    printf("Vehicles remaining: %d\n", remainingVehicles);

    if (remainingVehicles == 0)
        printf("The parking area is empty.\n");
    else
        printf("The parking area is not empty.\n");

    return 0;
}
