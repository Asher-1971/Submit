#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *donations = NULL;
    int *resizedDonations;
    int donationCount;
    int additionalCount;
    int totalCount;
    int index;
    long long total = 0;

    printf("Enter number of donations: ");
    if (scanf("%d", &donationCount) != 1 || donationCount <= 0 ||
        (size_t)donationCount > (size_t)-1 / sizeof(*donations))
    {
        printf("Please enter a valid positive number of donations.\n");
        return 1;
    }

    donations = malloc((size_t)donationCount * sizeof(*donations));
    if (donations == NULL)
    {
        perror("Could not allocate memory for donations");
        return 1;
    }

    printf("Enter %d donation amounts: ", donationCount);
    for (index = 0; index < donationCount; index++)
    {
        if (scanf("%d", &donations[index]) != 1 || donations[index] < 0)
        {
            printf("Please enter non-negative integer donation amounts.\n");
            free(donations);
            donations = NULL;
            return 1;
        }
    }

    printf("Enter number of additional donations: ");
    if (scanf("%d", &additionalCount) != 1 || additionalCount < 0 ||
        additionalCount > INT_MAX - donationCount)
    {
        printf("Please enter a valid non-negative number of additional donations.\n");
        free(donations);
        donations = NULL;
        return 1;
    }

    totalCount = donationCount + additionalCount;
    if ((size_t)totalCount > (size_t)-1 / sizeof(*donations))
    {
        printf("The donation list is too large.\n");
        free(donations);
        donations = NULL;
        return 1;
    }

    resizedDonations = realloc(donations, (size_t)totalCount * sizeof(*donations));
    if (resizedDonations == NULL)
    {
        perror("Could not enlarge the donation list");
        free(donations);
        donations = NULL;
        return 1;
    }
    donations = resizedDonations;
    resizedDonations = NULL;

    if (additionalCount > 0)
    {
        printf("Enter %d more amounts: ", additionalCount);
        for (index = donationCount; index < totalCount; index++)
        {
            if (scanf("%d", &donations[index]) != 1 || donations[index] < 0)
            {
                printf("Please enter non-negative integer donation amounts.\n");
                free(donations);
                donations = NULL;
                return 1;
            }
        }
    }

    printf("\nAll donations: ");
    for (index = 0; index < totalCount; index++)
    {
        printf("%d ", donations[index]);
        total += donations[index];
    }
    printf("\nTotal collected: %lld\n", total);

    free(donations);
    donations = NULL;
    return 0;
}
