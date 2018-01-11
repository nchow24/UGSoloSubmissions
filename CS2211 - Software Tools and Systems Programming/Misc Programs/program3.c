#include <stdio.h>


int main(void){
	double userNumber, e = 0, currentTerm;
	int valid = 0, factorialResult = 1;

	while (valid == 0){
		printf("Enter floating-point number: ");
		scanf("%lf", &userNumber);

		//
		//check for valid user number
		//
		if (userNumber <= 0){
			printf("Invalid floating-point number.\n");
		} else {
			valid = 1;
		}
	}
	
	int i = 1;
	int start = 1;
	
	while (valid == 1){
		//
		//calculate the factorial portion of the current value
		//
		for (start; start<=i; start++){
			factorialResult = factorialResult * start;
		}
		
		currentTerm = (float)1 / (float)factorialResult;
	
		//
		//check if current term should be added to e
		//
		if (currentTerm >= userNumber){
			e = e + currentTerm;
			start = 1;
			i = i + 1;
			factorialResult = 1;
		} else {
			valid = 0;
		}
	}
	
	printf("Approximated value of e: %.15f\n", e);
	printf("%d term(s) needed to generate this value.\n", i-1);
}