# DynamicProgrammingProject
C++ and text files used in for the final project in my Theory of Algorithms course.

### Project Description
The goal of the project was to consider a situation where a file compression failure resulted in the loss of all white spaces among the words in a text file, and to write a program that could generate all possible original documents (i.e. add white spaces) and rank them in order of likelihood, all in minimal time. The files dictionary.txt and dictionary3.txt were provided with the project instructions. The contents of the two dictionaries were to be used to accomplish the goal of generating all possible original documents.

### File Descriptions
**dictionary.txt** contains an unsorted list of the top 100000 English words with rankings included.  
**dictionary3.txt** contains an unsorted list of the top 20000 English words (both in lowercase and uppercase) without rankings.  
**trie.h** and **trie.cpp** are the header file and C++ source file for the implementation of a trie for holding all the words in dictionary3.txt  
**unionTrie.cpp** is a C++ source file that uses the contents of dictionary.txt and dictionary3.txt to create a trie of valid words and their associated values  
