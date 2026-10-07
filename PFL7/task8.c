#include <stdio.h>

int main(void)
{
    int temperatures[8], hottest, coldest, second, i;

    for (i = 0; i < 8; i++)
    {
        printf("Enter temperature %d: ", i + 1);
        scanf("%d", &temperatures[i]);
    }

    hottest = temperatures[0];
    coldest = temperatures[0];
    second = temperatures[0];

    for (i = 1; i < 8; i++)
    {
        if (temperatures[i] > hottest)
            hottest = temperatures[i];
        if (temperatures[i] < coldest)
            coldest = temperatures[i];
    }

    for (i = 0; i < 8; i++)
        if (temperatures[i] < hottest && temperatures[i] > second)
            second = temperatures[i];

    printf("Hottest: %d\n", hottest);
    printf("Coldest: %d\n", coldest);
    printf("Second hottest: %d\n", second);
    return 0;
}
