/* Created by Matthew Ding on 3/7/2022. */

#include <iostream>
#include <fstream>
#include "trie.cpp"
using namespace std;

void fillTrie(trieNode *root);

// Program to create a copy of the ranked dictionary without invalid values using the unranked but valid dictionary
int main() {
    // Declare the root node of the trie and add the words from the valid dictionary
    auto *root = new trieNode;
    fillTrie(root);

    // Open the file to write the union dictionary to
    ofstream unionDict;
    unionDict.open("unionDictionary.txt");
    if (!unionDict.is_open()) {
        cout << "The union dictionary file could not be opened.";
    }

    // Open the ranked dictionary with invalid values to read from
    ifstream bigDict;
    bigDict.open("dictionary.txt");
    if (!bigDict.is_open()) {
        cout << "The ranked dictionary file could not be opened.";
    }

    cout << "Creating a dictionary with rankings and valid words..." << endl;
    // Traverse through each line of the ranked dictionary
    // Add ranking comments and any valid words to the union dictionary
    string line;
    while (getline(bigDict, line)) {
        if (line[0] == '#') {
            // Commented lines beginning with '#' in the ranked dictionary should always be added
            unionDict << line << endl;
        } else if (trieNode::search(root, line)) {
            // Append each line containing a word that is valid (i.e. found in the trie)
            unionDict << line << endl;
        }
    }
    cout << "Successfully created a dictionary with rankings and valid words!";
}

// fillTrie(): Opens the valid dictionary and creates a trie with all its words
// Input: The root node of the trie to add the words to
void fillTrie(trieNode *root) {
    // Open the valid dictionary to read from
    ifstream smallDict;
    smallDict.open("dictionary2.txt");

    // Read each word from the valid dictionary and add it to the trie
    string line;
    if (smallDict.is_open()) {
        while (getline(smallDict, line)) {
            trieNode::insert(root, line);
        }
        smallDict.close();
    } else {
        cout << "The file could not be opened.";
    }
}