//Nicole Chow	nchow24	(250725575)
//Dec. 8, 2017
//ClientArray class header
//ClientArray structure contains a dynamic array of Clients and info about the array's size/use of element space

struct ClientArray {
	struct Client *array;
	size_t used;
	size_t size;
};

void initCArray(struct ClientArray *a, size_t initialSize) {
	a->array = (struct Client *)malloc(initialSize * sizeof(struct Client));
	a->used = 0;
	a->size = initialSize;
}

void insertCArray(struct ClientArray *a, struct Client element) {
	if (a->used == a->size) {
		a->size *= 2;
		a->array = (struct Client *)realloc(a->array, a->size * sizeof(struct Client));
	}
	a->array[a->used++] = element;
}
