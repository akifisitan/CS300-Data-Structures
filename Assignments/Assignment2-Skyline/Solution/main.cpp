// Akif Isitan
#include "MPQ.h"
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

// Get coordinates from input
vector<Coordinate> getCoordinates(const string& fileName) {
    // Open file as input
    ifstream file(fileName);
    stringstream buffer;
    buffer << file.rdbuf();
    string tempStr;
    vector<int> input;
    // Read coordinates to array
    while(buffer >> tempStr)
        input.push_back(stoi(tempStr));
    file.close();
    // Process read coordinates & create Coordinates from input
    vector<Coordinate> coordinates;
    for (unsigned int i=1; i < input.size(); i++) {
        // L coordinate indices: 1, 4, 7, ..., 3k+1
        if (i % 3 == 1) {
            // Create Coordinate with value, side, buildingNumber (Label) & buildingHeight
            Coordinate tempCoordinate(input[i], 'L', ((i + 1) / 3) + 1, input[i + 1]);
            coordinates.push_back(tempCoordinate);
        }
        // R coordinate indices: 3, 6, 9, ..., 3k
        else if (i % 3 == 0) {
            Coordinate tempCoordinate(input[i], 'R', ((i - 1) / 3) + 1, input[i - 1]);
            coordinates.push_back(tempCoordinate);
        }
    }
    // Sort coordinates & return the sorted array
    Coordinate::sortCoordinates(coordinates);
    return coordinates;
}

void printSkyline(vector<Coordinate>& coordinates) {
    // Create modified priority queue
    MPQ mpq(coordinates.size());
    // Output 0, 0 if first building does not start at 0
    if (coordinates[0].value != 0)
        cout << 0 << " " << 0 << "\n";
    // Iterate through coordinates
    for (Coordinate c : coordinates) {
        // Remember previous max if mpq was not empty
        int prevMax = 0;
        if (!mpq.isEmpty())
            prevMax = mpq.getMax().buildingHeight; // previous max building height
        // Insert coordinate to MPQ if side is L
        if (c.side == 'L')
            mpq.insert(c, c.buildingNo);
        // Remove coordinate from MPQ if side is R
        else
            mpq.remove(c.buildingNo); // Remove label from MPQ side is R
        // If mpq is empty, no coordinates remain therefore height is 0
        if (mpq.isEmpty())
            cout << c.value << " " << 0 << "\n";
        // If max building height changed, print the coordinate value & height
        else if (prevMax != mpq.getMax().buildingHeight) // Check if max changed
            cout << c.value << " " << mpq.getMax().buildingHeight << "\n";
    }
}

int main() {
    // Get coordinates from input file
    vector<Coordinate> coordinates = getCoordinates("input.txt");

    // Print the skyline
    printSkyline(coordinates);

    return 0;
}