GCC = gcc

default: clean asn3

asn3: asn3.c
	$(GCC) $^ -pthread -std=c99 -o asn3.out

clean:
	rm -rf *.out