# DynamicProgrammingProject
C++ and text files used in for the final project in my Theory of Algorithms course.

### Project Description
The goal of the project was to consider a situation where a file compression failure resulted in the loss of all white spaces among the words in a text file, and to write a program that could generate all possible original documents (i.e. add white spaces) and rank them in order of likelihood, all in minimal time. The files dictionary.txt and dictionary3.txt were provided with the project instructions. The contents of the two dictionaries were to be used to accomplish the goal of generating all possible original documents and rank them appropriately.

### File Descriptions
**Please read .gitignore for obsolete files**  
**dictionary.txt** contains an unsorted list of the top 100000 English words with rankings included  
**dictionary3.txt** contains an unsorted list of the top 20000 English words (both in lowercase and uppercase) without rankings  
**trie.h** and **trie.cpp** are the header file and C++ source file that provide the implementation of a trie class for holding words and their rankings
**unionTrie.cpp** is the C++ source file that provides the methods used to to create a trie of valid words and their associated values based on the contents of dictionary.txt and dictionary3.txt
**mergeSort.cpp** is the C++ source file that provides the methods used to sort the generated possible original documents by their likelihoods  
**main.cpp** is the C++ source file that provides the method to generate all possible original documents and runs the program that performs the generation, ranking, and sorting of all possible original documents  
