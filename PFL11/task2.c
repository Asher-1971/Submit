#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *votes = NULL;
    int candidateCount;
    int voterCount;
    int index;
    int vote;
    int winner = 0;

    printf("Enter number of candidates: ");
    if (scanf("%d", &candidateCount) != 1 || candidateCount <= 0 ||
        (size_t)candidateCount > (size_t)-1 / sizeof(*votes))
    {
        printf("Please enter a valid positive number of candidates.\n");
        return 1;
    }

    printf("Enter number of voters: ");
    if (scanf("%d", &voterCount) != 1 || voterCount < 0)
    {
        printf("Please enter a valid non-negative number of voters.\n");
        return 1;
    }

    votes = calloc((size_t)candidateCount, sizeof(*votes));
    if (votes == NULL)
    {
        perror("Could not allocate memory for vote counts");
        return 1;
    }

    printf("\nInitial vote counts: ");
    for (index = 0; index < candidateCount; index++)
        printf("%d ", votes[index]);
    printf("\n");

    printf("Enter %d votes (1-%d): ", voterCount, candidateCount);
    for (index = 0; index < voterCount; index++)
    {
        if (scanf("%d", &vote) != 1)
        {
            printf("Please enter valid integer votes.\n");
            free(votes);
            votes = NULL;
            return 1;
        }

        if (vote >= 1 && vote <= candidateCount)
            votes[vote - 1]++;
    }

    printf("\n--- Election Result ---\n");
    for (index = 0; index < candidateCount; index++)
    {
        printf("Candidate %d: %d vote(s)\n", index + 1, votes[index]);
        if (votes[index] > votes[winner])
            winner = index;
    }
    printf("Winner: Candidate %d\n", winner + 1);

    free(votes);
    votes = NULL;
    return 0;
}
