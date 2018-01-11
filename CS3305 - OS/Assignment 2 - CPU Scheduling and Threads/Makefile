GCC = gcc

default: clean part1 part2

part1: part1.c
	$(GCC) $^ -pthread -std=c99 -o part1.out

part2: part2.c 
	$(GCC) $^ -std=c99 -o part2.out

clean:
	rm -rf *.out