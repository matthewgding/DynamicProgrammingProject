/* Updated by Matthew Ding on 3/10/2022. */

#include "unionTrie.cpp"
using namespace std;

void genPossibilities(trieNode *root, string input, int start, const string& addTo);

int main() {
    // Create a trie with ranked valid entries
    auto *root = new trieNode;
    createUnionTrie(root);

    // Open the file that contains text with no white spaces
    ifstream tester;
    tester.open("input.txt");
    if (tester.is_open()) {
        string input, addTo;
        // Read the text from the file
        getline(tester, input);
        // Pass the text to the method that will parse it and add white spaces
        genPossibilities(root, input, 0, addTo);
    } else {
        // Kill the program if the input could not be read.
        cout << "The file to read from could not be opened.\n";
        return 0;
    }

    // Open the file containing all possible original texts with white spaces
    ifstream outputs;
    outputs.open("output.txt");
    string line;
    if (outputs.is_open()) {
        int mostLikelyRanking = 0;
        string mostLikelyLine;
        // Read each line to assess its rank
        while (getline(outputs, line)) {
            string word;
            int lineValue = 0;
            for (char i : line) {
                // Any white space or punctuation indicates that the string is now a word
                if (i == ' ' || i == '.' || i == ',' || i == '!' || i == '?') {
                    // Add the value of the word to the total value of the line
                    lineValue += trieNode::getValue(root, word);
                    // Reset the string to begin filling with the next word
                    word.clear();
                } else {
                    // Fill the string one character at a time
                    word += i;
                }
            }
            // Check if the line that has just been fully traversed and ranked is most
            // likely to be the original document (i.e. higher rank)
            if (lineValue > mostLikelyRanking) {
                // Record the rank of the most likely line and the line itself
                mostLikelyRanking = lineValue;
                mostLikelyLine = line;
            }
        }

        // Print out the most likely line and its rank
        cout << "\nThe most likely possible output is:\n" << mostLikelyLine
        <<"\nIt's total value is " << mostLikelyRanking << endl;
        outputs.close();
    } else {
        cout << "The file of possible outputs to rank could not be opened.\n";
    }
}

// genPossibilities(): Takes an input string without white spaces and parses it to valid words with white spaces
// Inputs: The root node of a dictionary trie, the input string, the index of where to begin parsing, the string
// of the output that has been generated thus far
void genPossibilities(trieNode *root, string input, int start, const string& addTo) {
    // Begin searching for valid words at the provided starting index
    string temp;
    temp = input[start];
    // Search through the remaining portion of the string
    while (start < input.length()) {
        // Special cases for when punctuation is encountered in the input string
        int isWord;
        char lastChar = temp[temp.length() - 1];
        // Punctuation indicates that a word ends at the previous character
        if (lastChar == '.' || lastChar == ',' || lastChar == '!' || lastChar == '?') {
            // Search for the word that ends at the previous character
            isWord = trieNode::search(root, temp.substr(0, temp.length() - 1));
        } else {
            // Normal case: search for a word with every character in temp
            isWord = trieNode::search(root, temp);
        }

        if (isWord == 1) {
            // Recursively work through the rest of the string to generate all possibilities
            genPossibilities(root, input, start + 1, addTo + temp + " ");
            // Append the next character to continue finding more possibilities
            temp += input[++start];
        } else if (isWord == 0) {
            // temp does not hold a valid word, but it may be a prefix to another word
            // Append the next character to keep searching
            temp += input[++start];
        } else {
            // temp does not hold a valid word nor a prefix to another word
            // Stop searching as this will no longer lead to valid possibilities
            return;
        }
    }

    // Conditions for the output to be written to the output file:
    // 1. The entirety of the input string must have been traversed at this point
    // 2. When the end of the input string has been reached and the parsed string
    // is valid, temp will contain no characters. Verify this.
    if (start >= input.length() && temp.length() == 1) {
        // Open the file to write to
        ofstream outFile;
        outFile.open("output.txt", ios_base::app);
        if (outFile.is_open()) {\
            // Write the valid parsed string
            outFile << addTo << endl;
            outFile.close();
        } else {
            cout << "The file to write to could not be opened.\n";
        }
    }
}
