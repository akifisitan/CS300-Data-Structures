// akifisitan
#include <iostream>
#include <fstream>
#include "HashTable.h"
#include "HashTable.cpp"

using namespace std;

string readFromFile(const string& fileName) {
    // Open the file
    ifstream inFile(fileName);
    char ch;
    string inputString;
    // Read file character by character to the string
    while (true) {
        inFile.get(ch);
        if (inFile.eof())
            break;
        inputString += ch;
    }
    inFile.close();
    return inputString;
}

void writeToFile(const string& fileName, const vector<int>& vec) {
    // Open the file
    ofstream outFile(fileName);
    // Write every code in the array to the file separated by a single space
    for (int i : vec)
        outFile << i << " ";
    outFile.close();
}

vector<int> compress(string initString) {
    // Initialize the dictionary & array
    HashTable<string, int> dictionary("STRING_NOT_FOUND", 4096);
    vector<int> codes;
    // Insert 256 characters into the dictionary
    for (int i = 0; i < 256; i++) {
        string c = string(1, (unsigned char) i);
        dictionary.insert(c, i);
    }
    // Initialize prefix with the first character of the input
    string prefix;
    prefix = initString[0];
    // Store previous prefix for output
    string prevPrefix = prefix;
    // Iterate until the remaining string is empty
    while (!initString.empty()) {
        int index = 1;
        // Find the longest prefix that is in the dictionary
        // Iterate through the string
        while (index <= initString.size()) {
            if (!dictionary.contains(prefix))
                break;
            // Remember previous prefix before updating the prefix
            prevPrefix = prefix;
            prefix += initString[index];
            // Move to the next character
            index++;
        }
        // Insert the previous prefix to the array
        codes.push_back(dictionary[prevPrefix]);
        // Insert the previous prefix + the next character to the dictionary
        dictionary.insert(prevPrefix + initString[index - 1], dictionary.size());
        // Update the encoded part of the string
        initString = initString.substr(index - 1);
        // Update the prefix
        prefix = initString[0];
    }
    // Print & return array of codes
    for (int i : codes) cout << i << " ";
    return codes;
}

int main() {

    // Read string from file
    string decompressed = readFromFile("compin.txt");
    // Compress the file contents
    vector<int> compressed = compress(decompressed);
    // Write the compressed code sequence into a file
    writeToFile("compout.txt", compressed);

    return 0;
}
