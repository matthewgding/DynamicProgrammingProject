/* Updated by Matthew Ding on 3/8/2022. */

#include <unordered_map>
#include <string>
using namespace std;

// Data structure to store trie nodes
class trieNode {
public:
    // trieNode variables
    bool isEndOfWord;
    int valueOfWord;
    unordered_map<char, trieNode *> map;

    //trieNode functions
    static trieNode *newTrieNode();
    static void insert(trieNode *&root, const string &str, const int &value);
    static bool search(trieNode *root, const string &str);
    static int getValue(trieNode *root, const string &str);
};
