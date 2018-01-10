#include <stdio.h>


int main(void){

	int months;
	double loan, monthlyPayment, interest, monthlyInterest;
	int validLoan = 0, validInterest = 0, validPayment = 0, validMonths = 0;
	
	while (validLoan == 0){
		printf("Enter amount of loan: ");
		scanf("%lf", &loan);
	
		//
		//check if amount of loan is valid
		//
		if (loan <= 0){
			printf("Invalid amount of loan.\n");
		} else {
			validLoan = 1;
		}
	}
	
	while (validInterest == 0){
		printf("Enter yearly interest rate: ");
		scanf("%lf", &interest);

		//
		//check if interest rate is valid (valid if between 0% and 100%)
		//
		if ( (interest <= 0) || ( 100 <= interest) ){
			printf("Invalid interest rate.\n");
		} else {
			validInterest = 1;
			monthlyInterest = interest/12;
		}
	}

	while (validPayment == 0){
		printf("Enter monthly payment: ");
		scanf("%lf", &monthlyPayment);
		
		//
		//check if monthly payment is valid
		//
		if (monthlyPayment <= 0){
			printf("Invalid monthly payment.\n");
		} else {
			validPayment = 1;
		}
	}
	
	while (validMonths == 0){
		printf("Enter number of monthly payments: ");
		scanf("%d", &months);
		
		//
		//check if number of months is valid
		//
		if (months <= 0){
			printf("Invalid number of monthly payments\n");
		} else {
			validMonths = 1;
		}
	}
	
	//
	//Calculate loan left at the end of each month
	//
	printf("REMAINING BALANCE ON LOAN\n");
	int i = 1;
	for (i; i<=months; i++){
		loan = loan + (loan * (monthlyInterest/100) ) - monthlyPayment;

		//
		//stop next payments if remaining balance reached 0
		//
		if (loan <= 0){
			printf("Month %d: $0.00\n", i);
			printf("Balance reached 0 at month %d.\n", i);
			printf("Amount of last payment: $%.2f\n", loan + monthlyPayment);
			break;
		//
		//continue payments if remaining balance still exists
		//
		} else {
			printf("Month %d: $%.2f\n", i, loan);
		}
	}	
}
