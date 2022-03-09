/* Updated by Matthew Ding on 3/8/2022.
 * This file provides the methods that are needed to create a trie of valid words with ranks.
 * This file replaces the functionality of unionDictionary.cpp */

#include <iostream>
#include <fstream>
#include "trie.cpp"
using namespace std;

void createUnionTrie(trieNode *root);
void fillBigTrie(trieNode *root);

// Program to create a copy of the ranked dictionary without invalid values using the unranked but valid dictionary
void createUnionTrie(trieNode *root) {
    // Declare the root node of the trie and add the words from the ranked dictionary
    auto *bigTrie = new trieNode;
    fillBigTrie(bigTrie);

    // Open the valid dictionary to read words from
    ifstream smallDict;
    smallDict.open("dictionary3.txt");

    cout << "Creating a dictionary trie of valid words with rankings..." << endl;
    // Traverse through each line (starting at 0) of the unranked dictionary
    // Even numbered lines are lowercase, and odd numbered lines are uppercase
    string line;
    int lineCount = 0, value;
    if (smallDict.is_open()) {
        while (getline(smallDict, line)) {
            if (lineCount % 2 == 0) {
                // Get the ranking when a lowercase word is being evaluated
                value = trieNode::getValue(bigTrie, line);
                trieNode::insert(root, line, value);
                lineCount++;
            } else {
                // Add uppercase words with the same ranking as their lowercase variants
                trieNode::insert(root, line, value);
                lineCount++;
            }
        }
    } else {
        cout << "The valid dictionary file could not be opened." << endl;
    }
    cout << "Successfully created a dictionary trie of valid words with rankings!";
}

// fillBigTrie(): Opens the ranked dictionary and creates a trie with all its words
// Input: The root node of the trie to add the words to
void fillBigTrie(trieNode *root) {
    // Open the ranked dictionary to read from
    ifstream bigDict;
    bigDict.open("dictionary.txt");

    // Initialize an arbitrary value >= 1002 to rank words
    int value = 1002;
    // Read each line from the valid dictionary and add words to the trie
    string line;
    if (bigDict.is_open()) {
        while (getline(bigDict, line)) {
            // Conditions for insertion:
            // Do not insert commented lines (which indicate ranking) to the trie
            // Decrement each time a comment line is encountered to change the ranking for that block of words
            // Insert each word with the current rank value
            if (line[0] == '#') {
                value--;
                continue;
            } else {
                trieNode::insert(root, line, value);
            }
        }
    } else {
        cout << "The ranked dictionary file could not be opened." << endl;
    }
}