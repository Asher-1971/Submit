#include <stdio.h>

int main(void){
    float withdraw =0 , balance = 0 ;
    printf("input available balance: ");
    scanf("%.2f", &balance);
    printf("%.2f", balance);

    if (balance > 500){
        printf("High Usage");
    }
    else {
        printf("Normal Usage");
    }
}