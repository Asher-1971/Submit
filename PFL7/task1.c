#include <stdio.h>

int main(void)
{
    int show;

    for (show = 1; show <= 10; show++)
        printf("Show %d: Rs. %d\n", show, 500 + (show - 1) * 50);

    return 0;
}
