/*******************************************************************************
 * Updated by Matthew Ding on 3/10/2022.
 * Important note: output.txt MUST be emptied before every run of this program.
 *******************************************************************************/

#include "unionTrie.cpp"
#include "mergeSort.cpp"
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
    fstream outputs;
    outputs.open("output.txt");
    string line;

    // Count the number of lines in the file to be sorted later
    int count = 0;
    if (outputs.is_open()) {
        while (getline(outputs, line)) {
            count++;
        }
        outputs.close();
    } else {
        // Kill the program if the file of possible original documents could not be opened
        cout << "The file of possible outputs to rank could not be opened.\n";
        return 0;
    }

    // Insert all the lines from the file into an array
    outputs.open("output.txt");
    string lines[count];
    int i = 0;
    while (getline(outputs, line)) {
        lines[i] = line;
        i++;
    }
    outputs.close();

    // Read each line to assess its rank and insert rank to an int array
    int values[count];
    for (int j = 0; j < count; j++) {
        string current = lines[j];
        string word;
        int lineValue = 0;
        for (char k : current) {
            // Any white space or punctuation indicates that the string is now a word
            if (k == ' ' || k == '.' || k == ',' || k == '!' || k == '?') {
                // Add the value of the word to the total value of the line
                lineValue += trieNode::getValue(root, word);
                // Reset the string to begin filling with the next word
                word.clear();
            } else {
                // Fill the string one character at a time
                word += k;
            }
        }
        // After the line has been fully read and ranked, insert the rank to the value array
        values[j] = lineValue;
    }

    // Use mergesort to sort the arrays from least likely to most likely
    mergeSort(values, lines, 0, count - 1);

    // Save the original documents to the output file from most likely to least likely
    outputs.open("output.txt");
    for (int l = count - 1; l >= 0; l--) {
        outputs << "\nRank: " << values[l];
        outputs << "\n\t" << lines[l] << "\n";
    }

    /*******************************************************************
    // This can be uncommented to print the rankings to the command line
    // Print out the original documents from most likely to least likely
    for (int l = count - 1; l >= 0; l--) {
        cout << "\nRank: " << values[l];
        cout << "\n\t" << lines[l] << "\n";
    }
    *******************************************************************/
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
