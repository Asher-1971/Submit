#include <stdio.h>

int main(void){
    float withdraw =0 , balance = 0 ;
    printf("input available balance: ");
    scanf("%f", &balance);
    printf("input withdraw amount: ");
    scanf("%f", &withdraw);


    if (balance > 0 && withdraw <= balance){
        printf("Withdraw Approved");
    }
    else {
        printf("withdraw denied");
    }
}