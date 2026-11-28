#include <stdio.h>
#include <stdlib.h>

void displayPlaylist(const char *label, const int durations[], int songCount)
{
    int index;
    long long totalDuration = 0;

    for (index = 0; index < songCount; index++)
        totalDuration += durations[index];

    printf("%s: ", label);
    for (index = 0; index < songCount; index++)
        printf("%d ", durations[index]);
    printf("(total %lld minutes)\n", totalDuration);
}

int main(void)
{
    int *durations = NULL;
    int songCount;
    int songsToRemove;
    int index;

    printf("Enter number of songs: ");
    if (scanf("%d", &songCount) != 1 || songCount <= 0 ||
        (size_t)songCount > (size_t)-1 / sizeof(*durations))
    {
        printf("Please enter a valid positive number of songs.\n");
        return 1;
    }

    durations = malloc((size_t)songCount * sizeof(*durations));
    if (durations == NULL)
    {
        perror("Could not allocate memory for the playlist");
        return 1;
    }

    printf("Enter duration (minutes) of %d songs: ", songCount);
    for (index = 0; index < songCount; index++)
    {
        if (scanf("%d", &durations[index]) != 1 || durations[index] < 0)
        {
            printf("Please enter non-negative integer song durations.\n");
            free(durations);
            durations = NULL;
            return 1;
        }
    }

    displayPlaylist("Playlist", durations, songCount);

    printf("Enter number of songs to remove from the end: ");
    if (scanf("%d", &songsToRemove) != 1 || songsToRemove < 0)
    {
        printf("Please enter a valid non-negative number of songs.\n");
        free(durations);
        durations = NULL;
        return 1;
    }

    if (songsToRemove >= songCount)
    {
        printf("Cannot remove that many songs.\n");
        displayPlaylist("Playlist remains", durations, songCount);
    }
    else
    {
        songCount -= songsToRemove;
        displayPlaylist("Playlist after removing", durations, songCount);
    }

    free(durations);
    durations = NULL;
    if (durations == NULL)
        printf("Playlist deleted. Nothing left to play.\n");

    return 0;
}
