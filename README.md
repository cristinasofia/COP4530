# COP4530
Data Structures and Algorithms

## Description of Autocomplete
This program uses a three level list (or 3-dimensional list.)

The first level list is an explicit vector; this vector will be indexed by the number of characters that are in "search terms". (Search terms are created by taking all of the possible relevant substrings up to the value in argument three of the program.) The values of the vector are lists of "search terms" objects.

Each "search term" object will have (of course) its "search term", and it will have a list of (occurence,word) pairs, just as in the the first program. Of course, these pairs are only related to the parent "search term" object. The second level and third level lists are based on the STL list. It first locates the correct element in the vector of search term lists; then it walks the list of search terms of that length, looking for the input string; if it finds it, it then reports from the associated word pair list matches up to the maximum specified in argument two.

## Description of Doublets
This program creates a "word ladder" by selecting one word and transforming it, one letter at a time, into another word. Transformations are only valid iff the each word appears in a given word list.

## Description of Cocktail Shaker Sort
This program splits the search into a "forward" search and a "backward" search, doing each in "cocktail shaker" fashion. That is, it first finds all of the words one letter different from the "source" word, and all of the words one letter different from "target" word. Then finds all of the words two letters different from the "source" word, and then the words that are two letters different than the "target". At each word, it finishes when the other side has found the same word.

## Description of Sorting Algorithms
A driver file is given, main.cc which expects to be linked against another file implementing a class called Sort, which implements an "out-of-place" sort using a "non-in-place" sort in an online fashion.

The first subdirectory, Tests, contains five test files; the largest test file has one million records and occupies almost 100 megabytes of space. The second subdirectory, driver, contains the files main.cc.

The other files in the directory are the Makefile, the test script "test.bash", templates HeapSort.cc and TrieSort.cc, and the implementation header, Sort.h.

There is also a compiled version of valsort from the gensort package found in the tar file which is used for testing.

HeapSort and TrieSort are implemented recursively as a linked version.
