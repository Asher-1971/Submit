#include <stdio.h>

int main(void)
{
	int rating, years;

	printf("Enter performance rating: ");
	scanf("%d", &rating);
	printf("Enter years of service: ");
	scanf("%d", &years);

	if (rating == 5 && years >= 3)
		printf("Excellent Bonus\n");
	else if (rating >= 4 && years >= 2)
		printf("Good Bonus\n");
	else if (rating >= 3 && years >= 1)
		printf("Basic Bonus\n");
	else
		printf("No Bonus\n");

	return 0;
}
