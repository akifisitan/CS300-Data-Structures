// akifisitan
#include <iostream>
#include <fstream>
#include <sstream>
#include "HashTable.h"
#include "HashTable.cpp"

using namespace std;

vector<int> readFromFile(const string& fileName) {
    // Open the file
    ifstream inFile(fileName);
    string line;
    // Read the single line into a string
    getline(inFile, line);
    inFile.close();
    istringstream iss(line);
    vector<int> codes;
    int n;
    // Process the codes into an array & return it
    while (iss >> n)
        codes.push_back(n);
    return codes;
}

void writeToFile(const string& fileName, const string &s) {
    // Open the file
    ofstream outFile(fileName);
    // Write the decoded string to the file
    outFile << s;
    outFile.close();
}

string decompress(const vector<int>& codes) {
    // Initialize the dictionary & output string
    vector<string> dictionary(4096, "STRING_NOT_FOUND");
    string decompressed;
    // Keep track of the number of elements in the dictionary
    int dictElements = 0;
    // Insert 256 chars into the dictionary
    for (int i = 0; i < 256; i++) {
        string c = string(1, (unsigned char) i);
        dictionary[i] = c;
        dictElements++;
    }
    // Output first code
    decompressed = dictionary[codes[0]];
    // Iterate over remaining codes
    for (int i = 1; i < codes.size(); i++) {
        int currentCode = codes[i];
        int prevCode = codes[i - 1];
        // Code is in the dictionary
        if (dictionary[currentCode] != "STRING_NOT_FOUND") {
            // text(x), is extracted from the dictionary and output.
            decompressed += dictionary[currentCode];
            // Enter the pair (next code, text(q)fc(x)) into the dictionary.
            dictionary[dictElements] = dictionary[prevCode] + dictionary[currentCode][0];
        }
        // Code is not in the dictionary
        else {
            // The code-to-text mapping for x is text(q)fc(q)
            // where x is currentCode, q is prevCode
            string textQ_fcQ = dictionary[prevCode] + dictionary[prevCode][0];
            decompressed += textQ_fcQ;
            dictionary[currentCode] = textQ_fcQ;
        }
        // Increment element size
        dictElements++;
    }
    // Print & return decompressed string
    cout << decompressed;
    return decompressed;
}

int main() {

    // Read code sequence from the file
    vector<int> compressed = readFromFile("compout.txt");
    // Decompress the code sequence
    string decompressed = decompress(compressed);
    // Write the decompressed string into a file
    writeToFile("decompout.txt", decompressed);

    return 0;
}
