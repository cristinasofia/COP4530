

CC=clang++
CFLAGS=-g

targets : bstsort heapsort triesort 

bstsort : BSTSort.o main.o
	$(CC) $(CFLAGS) -o bstsort $^

heapsort : HeapSort.o main.o
	$(CC) $(CFLAGS) -o heapsort $^

triesort : TrieSort.o main.o
	$(CC) $(CFLAGS) -o triesort $^


%.o : %.cc
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f BSTSort.o HeapSort.o TrieSort.o main.o BSTSort HeapSort TrieSort

