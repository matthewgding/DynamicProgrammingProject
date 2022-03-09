/* Updated by Matthew Ding on 3/8/2022.
 * This implementation has been adapted from the implementation found from Techie Delight.
 * https://www.techiedelight.com/memory-efficient-trie-implementation-using-map-insert-search-delete/ */

#include "trie.h"
using namespace std;

// newTrieNode(): Generates a new trie node
// Output: An empty trie node
trieNode *trieNode::newTrieNode() {
    auto *node = new trieNode;
    node->isEndOfWord = false;
    node->valueOfWord = 0;
    return node;
}

// insert(): Iterative function to insert a string into a trie
// Inputs: The root node of the trie to insert into, string to insert, value to assign
void trieNode::insert(trieNode *&root, const string &str, const int &value = 0) {
    // Check to see if a valid root node has been provided
    if (root == nullptr) {
        root = newTrieNode();
    }

    // Start inserting from the root node
    trieNode *current = root;
    for (char i : str) {
        // Create a new trie node if the desired path doesn't already exist
        if (current->map.find(i) == current->map.end()) {
            current->map[i] = newTrieNode();
        }

        // Traverse to the next node
        current = current->map[i];
    }

    // Mark the last node as the end of the word being inserted
    current->isEndOfWord = true;
    current->valueOfWord = value;
}

// search(): Iterative function to search for a string in a trie
// Inputs: The root node of the trie to search in, char pointer to string to find
// Output: A boolean value (true if successful, false if unsuccessful)
bool trieNode::search(trieNode *root, const string &str) {
    // Base case: An empty trie has been provided
    if (root == nullptr) {
        return false;
    }

    // Begin searching at the root
    trieNode *current = root;
    for (char i : str) {
        // Go to the next node in the trie
        current = current->map[i];

        // The string is not in the trie if it hasn't been found and the path ends
        if (current == nullptr) {
            return false;
        }
    }

    // The string has been found in the trie if it reached its end and the current node was the end of a word
    // If the string was not a valid word, then the function will return false even if the string was found
    return current->isEndOfWord;
}

// getValue(): Returns the assigned value of the provided word
// Inputs: The root node of the trie to search in, the word to get a value for
static int getValue(trieNode *root, const string &str) {
    // Base case: No word has been provided
    if (root == nullptr) {
        return 0;
    }

    // Search for the word and retrieve its value
    // Begin searching at the root
    trieNode *current = root;
    for (char i : str) {
        // Go to the next node in the trie
        current = current->map[i];

        // There is no value if the string hasn't been found and the path ends
        if (current == nullptr) {
            return 0;
        }
    }

    // If the word is valid then it has a value to return
    if (current->isEndOfWord) {
        return current->valueOfWord;
    }
    // Return 0 if the word is invalid
    return 0;
}
