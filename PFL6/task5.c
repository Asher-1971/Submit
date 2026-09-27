#include <stdio.h>
#include <math.h>

int main(void)
{
    char mode, operation;
    double first, second, result;

    printf("Enter mode (1 for Basic Arithmetic, 2 for Power/Root): ");
    scanf(" %c", &mode);

    switch (mode)
    {
        case '1':
            printf("Enter operator (+, -, *, /): ");
            scanf(" %c", &operation);
            printf("Enter first number: ");
            scanf("%lf", &first);
            printf("Enter second number: ");
            scanf("%lf", &second);
            switch (operation)
            {
                case '+': result = first + second; printf("Result: %.2f\n", result); break;
                case '-': result = first - second; printf("Result: %.2f\n", result); break;
                case '*': result = first * second; printf("Result: %.2f\n", result); break;
                case '/':
                    if (second != 0)
                        printf("Result: %.2f\n", first / second);
                    else
                        printf("Cannot divide by zero\n");
                    break;
                default: printf("Invalid operator\n");
            }
            break;
        case '2':
            printf("Enter operation (s for square, r for square root): ");
            scanf(" %c", &operation);
            printf("Enter number: ");
            scanf("%lf", &first);
            switch (operation)
            {
                case 's': printf("Result: %.2f\n", first * first); break;
                case 'r':
                    if (first >= 0)
                        printf("Result: %.2f\n", sqrt(first));
                    else
                        printf("Cannot find square root of a negative number\n");
                    break;
                default: printf("Invalid operation\n");
            }
            break;
        default: printf("Invalid mode\n");
    }

    return 0;
}