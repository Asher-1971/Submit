#include <stdio.h>

int main(void)
{
	int choice;
    printf("Enter Choice 1 = Burger, 2 = Pizza, 3 = Biryani, and 4 = Sandwich :");
	scanf("%d", &choice);

	switch (choice) {
		case 1:
			printf("Burger\n");
		case 2:
			printf("Pizza\n");
		case 3:
			printf("Biryani\n");
		case 4:
			printf("Sandwich\n");
		default:
			printf("Invalid Choice\n");
	}

	return 0;
}
