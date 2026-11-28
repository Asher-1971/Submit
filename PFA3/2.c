#include <stdio.h>
#include <stdlib.h>

static int **allocateGrid(int size)
{
    int **grid;
    int row;

    if (size <= 0)
        return NULL;
    if ((size_t)size > (size_t)-1 / sizeof(*grid) ||
        (size_t)size > (size_t)-1 / sizeof(**grid))
    {
        fprintf(stderr, "Grid dimensions are too large to allocate.\n");
        return NULL;
    }

    grid = malloc((size_t)size * sizeof(*grid));
    if (grid == NULL)
    {
        perror("Could not allocate a grid");
        return NULL;
    }

    for (row = 0; row < size; row++)
        grid[row] = NULL;

    for (row = 0; row < size; row++)
    {
        grid[row] = malloc((size_t)size * sizeof(**grid));
        if (grid[row] == NULL)
        {
            perror("Could not allocate a grid row");
            while (row > 0)
            {
                row--;
                free(grid[row]);
                grid[row] = NULL;
            }
            free(grid);
            grid = NULL;
            return NULL;
        }
    }

    return grid;
}

static void freeGrid(int **grid, int size)
{
    int row;

    if (grid == NULL)
        return;

    for (row = 0; row < size; row++)
    {
        free(grid[row]);
        grid[row] = NULL;
    }
    free(grid);
}

static void printGrid(int **grid, int size)
{
    int row;
    int column;

    for (row = 0; row < size; row++)
    {
        for (column = 0; column < size; column++)
            printf("%d", grid[row][column]);
        printf("\n");
    }
}

int main(int argc, char *argv[])
{
    FILE *input = NULL;
    int **curr_grid = NULL;
    int **next_grid = NULL;
    int size = 0;
    int generations = 0;
    int generation;
    int row;
    int column;
    int status = 1;
    char extraCharacter;

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <input-file>\n", argv[0]);
        return 1;
    }

    input = fopen(argv[1], "r");
    if (input == NULL)
    {
        perror("Could not open the input file");
        return 1;
    }

    if (fscanf(input, "%d%d", &size, &generations) != 2 ||
        size <= 0 || generations < 0)
    {
        fprintf(stderr, "The file must start with a positive grid size and a non-negative generation count.\n");
        goto cleanup;
    }

    curr_grid = allocateGrid(size);
    if (curr_grid == NULL)
        goto cleanup;
    next_grid = allocateGrid(size);
    if (next_grid == NULL)
        goto cleanup;

    for (row = 0; row < size; row++)
    {
        for (column = 0; column < size; column++)
        {
            int cell;

            if (fscanf(input, "%1d", &cell) != 1 || (cell != 0 && cell != 1))
            {
                fprintf(stderr, "The grid must contain exactly %d rows of %d binary cells.\n",
                        size, size);
                goto cleanup;
            }
            curr_grid[row][column] = cell;
        }
    }

    if (fscanf(input, " %c", &extraCharacter) == 1)
    {
        fprintf(stderr, "Unexpected extra data after the grid.\n");
        goto cleanup;
    }
    if (ferror(input))
    {
        perror("Could not read the input file");
        goto cleanup;
    }

    printf("Initial grid:\n");
    printGrid(curr_grid, size);

    for (generation = 0; generation < generations; generation++)
    {
        for (row = 0; row < size; row++)
        {
            for (column = 0; column < size; column++)
            {
                int neighborCount = 0;
                int rowOffset;
                int columnOffset;

                for (rowOffset = -1; rowOffset <= 1; rowOffset++)
                {
                    for (columnOffset = -1; columnOffset <= 1; columnOffset++)
                    {
                        int neighborRow = row + rowOffset;
                        int neighborColumn = column + columnOffset;

                        if ((rowOffset != 0 || columnOffset != 0) &&
                            neighborRow >= 0 && neighborRow < size &&
                            neighborColumn >= 0 && neighborColumn < size)
                            neighborCount += curr_grid[neighborRow][neighborColumn];
                    }
                }

                if (curr_grid[row][column] == 1)
                    next_grid[row][column] =
                        (neighborCount == 2 || neighborCount == 3) ? 1 : 0;
                else
                    next_grid[row][column] = (neighborCount == 3) ? 1 : 0;
            }
        }

        {
            int **temporary = curr_grid;
            curr_grid = next_grid;
            next_grid = temporary;
        }
    }

    printf("Grid after %d generation(s):\n", generations);
    printGrid(curr_grid, size);
    status = 0;

cleanup:
    freeGrid(curr_grid, size);
    curr_grid = NULL;
    freeGrid(next_grid, size);
    next_grid = NULL;
    if (fclose(input) != 0)
    {
        perror("Could not close the input file");
        status = 1;
    }
    input = NULL;
    return status;
}
