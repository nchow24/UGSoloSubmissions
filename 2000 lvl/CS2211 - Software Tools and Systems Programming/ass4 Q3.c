#include <stdio.h>

void pay_amount(int dollars, int *twenties, int *tens, int *fives, int *toonies, int *lonnie);

int main(void){
	int amount, quantityStart = 0, *_20, *_10, *_5, *_2, *_1;
	
	//quantityStart represents all bill/coins needed, adjusted accordingly to first be the # of 20s needed, then 10s,
	//then 5s then 2s then 1s as seen in function pay_amount()
	_1 = _2 = _5 = _10 = _20 = &quantityStart;

	printf("Enter amount: ");
	scanf("%d", &amount);

	//loop for positive integer
	while (amount<=0){
		printf("Error, re-enter amount: ");
		scanf("%d", &amount);
	}

	//calculate minimum #coins/bills needed
	pay_amount(amount, _20, _10, _5, _2, _1);
	
}


void pay_amount(int amount, int *_20, int *_10, int *_5, int *_2, int *_1){
	
	//find # of 20s needed, subtract the amount paid with 20s from amount
	*_20 = amount/20;
	printf("# of 20's: %d\n", *_20);
	amount = amount - (*_20)*20;

	//find # of 10s needed, subtract the amount paid with 10s from amount
	*_10 = amount/10;
	printf("# of 10's: %d\n", *_10);
	amount = amount - (*_10)*10;

	//find # of 5s needed, subtract the amount paid with 5s from amount
	*_5 = amount/5;
	printf("# of 5's: %d\n", *_5);
	amount = amount - (*_5)*5;

	//find # of 2s needed, subtract the amount paid with 2s from amount
	*_2 = amount/2;
	printf("# of 2's: %d\n", *_2);
	amount = amount - (*_2)*2;
	
	//the rest of the amount must be paid with in 1s
	*_1 = amount;
	printf("# of 1's: %d\n", *_1);
}