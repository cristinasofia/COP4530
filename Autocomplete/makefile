CC = clang++
CFLAGS = -std=c++11 -pedantic -Wall

all: autocomplete-my-unordered-map

autocomplete-my-unordered-map.o: autocomplete-my-unordered-map.cc
	$(CC) $(CFLAGS) -c autocomplete-my-unordered-map.cc

clean:
	rm -f *.o autocomplete-my-unordered-map
