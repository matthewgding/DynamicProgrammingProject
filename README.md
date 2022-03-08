# DynamicProgrammingProject
C++ and text files used in for the final project in my Theory of Algorithms course.

### Project Description
The goal of the project was to consider a situation where a file compression failure resulted in the loss of all white spaces among the words in a text file, and to write a program that could generate all possible original documents (i.e. add white spaces) and rank them in order of likelihood, all in minimal time. The files dictionary.txt and dictionary2.txt were provided with the project instructions. The contents of dictionary.txt were an unsorted list of the top 100000 English words with rankings included. The contents of dictionary2.txt were an unsorted list of the top 20000 English words (both in lowercase and uppercase) without rankings. The contents of dictionary.txt had to be evaluated to eliminate invalid words using the contents of dictionary2.txt and the resulting dictionary was to be used to accomplish the goal of generating all possible original documents.

### File Descriptions
**trie.h** and **trie.cpp** are the header file and C++ source file for the implementation of a trie for holding all the words in dictionary2.txt
**unionDictionary.cpp** is a C++ source file that uses the contents of dictionary2.txt to create a new dictionary (unionDictionary.txt) with rankings and valid words only from the contents of dictionary.txt
