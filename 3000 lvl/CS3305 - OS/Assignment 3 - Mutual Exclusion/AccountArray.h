//Nicole Chow	nchow24	(250725575)
//Dec. 8, 2017
//AccountArray class header
//AccountArray structure contains a dynamic array of Accounts and info about the array's size/use of element space


struct AccountArray {
	struct Account *array;
	size_t used;
	size_t size;
};

void initAArray(struct AccountArray *a, size_t initialSize) {
	a->array = (struct Account *)malloc(initialSize * sizeof(struct Account));
	a->used = 0;
	a->size = initialSize;
}

void insertAArray(struct AccountArray *a, struct Account element) {
	if (a->used == a->size) {
		a->size *= 2;
		a->array = (struct Account *)realloc(a->array, a->size * sizeof(struct Account));
	}
	a->array[a->used++] = element;
}
