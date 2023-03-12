// Akif Isitan
#include "Coordinate.h"

using namespace std;

// Default constructor
Coordinate::Coordinate()
        : value(0), side('N'), buildingNo(0), buildingHeight(0) {}

// Non-default constructor
Coordinate::Coordinate(int aValue, char aSide, int aBuildNo, int aBuildHeight)
        : value(aValue), side(aSide), buildingNo(aBuildNo), buildingHeight(aBuildHeight) {}

// Overload < operator for handling equal value cases
bool Coordinate::operator<(const Coordinate& rhs) const {
	// Check values first, whichever value is bigger the bigger coordinate
	if (value < rhs.value)
		return true;
	else if (value > rhs.value)
		return false;
	// If values are equal
	else { // if (value == rhs.value)
		// If sides are both R values, buildingHeight bigger is the bigger (Sort R values by ascending height)
		if (side == 'R' && rhs.side == 'R') {
			if (buildingHeight < rhs.buildingHeight)
				return true;
			else 
				return false;
		}
		// If sides are both L values, buildingHeight smaller is the bigger (Sort L values by descending height)
		else if (side == 'L' && rhs.side == 'L') {
			if (buildingHeight < rhs.buildingHeight)
				return false;
			else 
				return true;
		}
		// If sides are different, L values are bigger than R values (Does not really matter)
		else if (side == 'L' && rhs.side == 'R') // different sides
			return true;
		else // if (side == 'R' && rhs.side == 'L')
			return false;
	}		
}

// Comparison function for sorting coordinates
bool Coordinate::compareCoordinates(const Coordinate& a, const Coordinate& b) {
    return a < b;
}

// Uses standard library's quicksort algorithm to sort coordinates by value
// Sort L sides in descending & R sides in ascending order of building height if values are equal
// Otherwise sort by values ascending
void Coordinate::sortCoordinates(vector<Coordinate> &coordinates) {
    sort(coordinates.begin(), coordinates.end(), compareCoordinates);
}
