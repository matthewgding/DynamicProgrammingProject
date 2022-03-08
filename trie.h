/* Created by Matthew Ding on 3/7/2022. */

#include <unordered_map>
#include <string>
using namespace std;

// Data structure to store trie nodes
class trieNode {
public:
    // trieNode variables
    bool isEndOfWord;
    unordered_map<char, trieNode *> map;

    //trieNode functions
    static trieNode *newTrieNode();
    static void insert(trieNode *&root, const string &str);
    static bool search(trieNode *root, const string &str);
};
