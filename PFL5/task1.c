#include <stdio.h>

int main(void)
{
    float bill, discount, payable;
    int member;

    printf("Enter total bill amount: ");
    scanf("%f", &bill);
    printf("Enter membership status (1 for member, 0 for non-member): ");
    scanf("%d", &member);

    if (bill >= 5000)
    {
        if (member == 1)
            discount = bill * 0.20f;
        else
            discount = bill * 0.10f;
    }
    else
    {
        if (member == 1)
            discount = bill * 0.10f;
        else
            discount = 0;
    }

    payable = bill - discount;
    printf("Original Bill: Rs. %.2f\n", bill);
    printf("Discount Amount: Rs. %.2f\n", discount);
    printf("Final Payable Amount: Rs. %.2f\n", payable);

    return 0;
}