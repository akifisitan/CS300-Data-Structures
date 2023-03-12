// Akif Isitan
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include "PointQuadTree.h"
using namespace std;

PointQuadTree processCities() {
	// Create tree
    PointQuadTree myTree("NOT_FOUND");
    fstream inFile("cities.txt");
    string line, citiesFile = "";
    bool isFirstLine = true;
    int gridX, gridY;
	// Add all lines except first to a string
    while (getline(inFile, line)) {
        if (isFirstLine) {
		    int comma_index = line.find(' ');
            gridX = stoi(line.substr(0, comma_index));
            gridY = stoi(line.substr(comma_index, line.length()));
            isFirstLine = false;
        }
		else
			citiesFile += line + "\n";
    }
    inFile.close();
	// Read the string and parse the variables
    stringstream citiesStream(citiesFile);
    string cityName;
	int cityXCoordinate, cityYCoordinate;
    // Add variables to the tree
    while (citiesStream >> cityName >> cityXCoordinate >> cityYCoordinate) {
        myTree.insert(cityName, cityXCoordinate, cityYCoordinate);
    }
	// Print the tree
    myTree.prettyPrint();
	cout << endl;
    return myTree;
}

void processQueries(PointQuadTree &tree, string fileName) {
    fstream inFile;
    string line;
    inFile.open(fileName);
    int x, y, radius;
	// Read queries line by line, parse input
    while (getline(inFile, line)) { 
        int first_comma_index = line.find(' ');
        int second_comma_index = line.find(' ', first_comma_index + 1);
        x = stoi(line.substr(0, first_comma_index));
        y = stoi(line.substr(first_comma_index, second_comma_index));
        radius = stoi(line.substr(second_comma_index, line.length()));
		// Calculate query
        tree.printWithinRadius(x, y, radius);
    }
    inFile.close();
}

int main() {
	
	PointQuadTree myTree = processCities();
    processQueries(myTree, "queries.txt");

    return 0;
}
