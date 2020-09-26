# COP4530
Data Structures and Algorithms

# Description of Doublets
This program creates a "word ladder" by selecting one word and transforming it, one letter at a time, into another word. Transformations are only valid iff the each word appears in a given word list.

# Description of Cocktail Shaker Sort
This program splits the search into a "forward" search and a "backward" search, doing each in "cocktail shaker" fashion. That is, it first finds all of the words one letter different from the "source" word, and all of the words one letter different from "target" word. Then finds all of the words two letters different from the "source" word, and then the words that are two letters different than the "target". At each word, it finishes when the other side has found the same word.

## Description of Sorting Algorithms
A driver file is given, main.cc which expects to be linked against another file implementing a class called Sort, which implements an "out-of-place" sort using a "non-in-place" sort in an online fashion.

The first subdirectory, Tests, contains five test files; the largest test file has one million records and occupies almost 100 megabytes of space. The second subdirectory, driver, contains the files main.cc.

The other files in the directory are the Makefile, the test script "test.bash", templates HeapSort.cc and TrieSort.cc, and the implementation header, Sort.h.

There is also a compiled version of valsort from the gensort package found in the tar file which is used for testing.

HeapSort and TrieSort are implemented recursively as a linked version.
