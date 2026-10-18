#include <stdio.h>

int main(void)
{
    int sales[3][5];
    int i, j, branch_total, product_totals[5] = {0};
    int best_branch = 0, lowest_product = 0;
    int best_branch_total = 0, lowest_product_total;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 5; j++)
        {
            printf("Enter sales for branch %d product %d: ", i + 1, j + 1);
            scanf("%d", &sales[i][j]);
            product_totals[j] += sales[i][j];
        }
    }

    printf("\nTotal sales per branch:\n");
    for (i = 0; i < 3; i++)
    {
        branch_total = 0;
        for (j = 0; j < 5; j++)
            branch_total += sales[i][j];
        printf("Branch %d: %d\n", i + 1, branch_total);
        if (branch_total > best_branch_total)
        {
            best_branch_total = branch_total;
            best_branch = i;
        }
    }

    printf("\nTotal sales per product:\n");
    lowest_product_total = product_totals[0];
    for (j = 0; j < 5; j++)
    {
        printf("Product %d: %d\n", j + 1, product_totals[j]);
        if (product_totals[j] < lowest_product_total)
        {
            lowest_product_total = product_totals[j];
            lowest_product = j;
        }
    }

    printf("Best-selling branch: Branch %d\n", best_branch + 1);
    printf("Product with the lowest sales overall: Product %d\n", lowest_product + 1);
    return 0;
}
