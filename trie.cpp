/* Created by Matthew Ding on 3/7/2022.
 * This implementation has been adapted from the implementation found from Techie Delight.
 * https://www.techiedelight.com/memory-efficient-trie-implementation-using-map-insert-search-delete/ */

#include "trie.h"
using namespace std;

// newTrieNode(): Generates a new trie node
// Output: An empty trie node
trieNode *trieNode::newTrieNode() {
    auto *node = new trieNode;
    node->isEndOfWord = false;
    return node;
}

// insert(): Iterative function to insert a string into a trie
// Inputs: The root node of the trie to insert into, string to insert
void trieNode::insert(trieNode *&root, const string &str) {
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
