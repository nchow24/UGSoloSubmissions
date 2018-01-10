#include <stdio.h>
#include <stdlib.h>

int main(void){
	int size, mid, number = 2, i = 1;
	
	printf("Enter size: ");
	scanf("%d", &size);


	//loop for positive odd integer
	while ( (size%2 == 0) || (size <1) || (size> 13) ){
		printf("Error, re-enter size: ");
		scanf("%d", &size);
	}
	
	int magic[size][size], *limit = magic, *p = magic, *m = magic, *a;

	limit = limit + (size*size);
	mid = size/2;

	for(m = magic; m<limit; m++){
		*m = 0;
	}	
	p = p + mid;
	*p = 1;

	//insert numbers into the array
	for (number; number <= (size*size); number++){

		//pointer moving up 1 row right 1 column (assuming no wrapping occurs)
		a = p - size + 1;

		//check if wrapping occured from changing pointer by checking if
		// a and p are in the same row
		int d = 1, sameRow = 0;
		for (d; d<size; d++){
			m = a - d*size;
			if (m == magic){
				sameRow = 1;
			}
		}
		//fill directly below p if p is the top right corner
		m = magic;
		m = m + size -1;
		if (p == m){
			p = p + size;
			*p = number;
		} else {
			//fill *a if moving up 1 row right 1 column doesn't move out of bounds, wrap around
			//and a is not already filled
			if ((a < limit) && (magic <= a) && (*a == 0) && (sameRow ==0)){
				p = a;
				*p = number;
			} else {
				//fill directly below a if moving up 1 row right 1 column stays in bounds, doesn't wrap around
				//but *a is filled
				if ((a < limit) && (magic <= a) && (*a != 0) && (sameRow ==0)){
					a = p + size;
					//make sure moving down is in bounds and not filled
					if ((a < limit) && (magic <= a) && (*a == 0) && (sameRow ==0)){
						p = a;
						*p = number;
					}
				} else {
					//fill on first column up one row if wrapping to the same row occurred
					if (sameRow==1){
						a = a - size;
						p = a;
						*p = number;
					//fill on same column bottom row if a went out of bounds of the array
					} else {
						a = p + (size-1)*size + 1;
						p = a;
						*p = number;
					}
				}
			}
		}
	}
	
	//print array
	m = magic;
	for (m; m<limit; m++){
		printf("%-6d", *m);
		if (i%size == 0){
			printf("\n");
		}
		i++;
	}	
}





