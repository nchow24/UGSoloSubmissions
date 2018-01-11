//Nicole Chow	nchow24	(250725575)
//Dec. 8, 2017
//TransactionArray class header
//TransactionArray structure contains a dynamic array of Transactions and info about the array's size/use of element space


struct TransactionArray {
	struct Transaction *array;
	size_t used;
	size_t size;
};

void initTArray(struct TransactionArray *a, size_t initialSize) {
	a->array = (struct Transaction *)malloc(initialSize * sizeof(struct Transaction));
	a->used = 0;
	a->size = initialSize;
}

void insertTArray(struct TransactionArray *a, struct Transaction element) {
	if (a->used == a->size) {
		a->size *= 2;
		a->array = (struct Transaction *)realloc(a->array, a->size * sizeof(struct Transaction));
	}
	a->array[a->used++] = element;
}
