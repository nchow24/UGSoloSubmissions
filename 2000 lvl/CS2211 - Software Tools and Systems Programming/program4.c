#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//compile using gcc -lm Q1.c 

int main(void){ 
	srand((unsigned) time(NULL));
	double x, y, ratio, approxPi, sumPi = 0, mean, sumSD = 0, sd, count = 0;
	int N, validN = 0, i = 0, j = 0, k = 0;
	double ratios[10];
	
	printf("Enter integer: ");
		scanf("%d", &N);

	//loop for positive integer
	while (N<=0){
		printf("Error, re-enter integer: ");
		scanf("%d", &N);
	}
	
	printf("N = %d:\n", N);
	printf("Approx pi values:\n");

	//calculate pi 10 times
	for (j; j<10; j++){
		count = 0;
		i = 0;
		
		//count number of coordinates inside quadrant
		for (i; i<N; i++){
			x = (float)rand()/RAND_MAX;
			y = (float)rand()/RAND_MAX;
			if ( (x*x + y*y) <= 1 ){
				count += 1;
			}
		
		}
		
		ratio = count/N;
		approxPi = ratio*4;

		//store approximate pi values in array for standard deviation calculation
		ratios[j] = approxPi;

		sumPi += approxPi;

		printf("%f\n", approxPi);
	}
	mean = sumPi/10;

	//calculate the numerator value of the standard deviation 
	for (k; k<10; k++){
		sumSD += (ratios[k]-mean)*(ratios[k]-mean);
	}
	
	sd = sqrt(sumSD/10);
	printf("Mean: %f\n", mean);
	printf("Standard Deviation: %f\n", sd);
	
} 