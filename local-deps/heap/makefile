CC		= gcc
OPTFLAGS	= -O3 -march=native -mtune=native -flto -ffast-math
DEBUGFLAGS	= -O0 -g3 -Warray-bounds -Wformat-overflow -Wstringop-overflow -Wstringop-overread
PROFFLAGS	= -pg
CCFLAGS		= $(DEBUGFLAGS)

.PHONY: run clean

run: test_heap clean
	./test_heap

clean:
	rm *.o

test_heap: test.c heap.o
	$(CC) $(CCFLAGS) *.o test.c -o test_heap

heap.o: heap.c
	$(CC) $(CCFLAGS) -c heap.c -o heap.o
