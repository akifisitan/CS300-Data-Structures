// Akif Isitan
#ifndef COORDINATE_H
#define COORDINATE_H
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Coordinate {
public:
    int value;  // Coordinate's value
    char side;  // Coordinate's side (L or R)
    int buildingNo;  // Coordinate's Building Number (Label)
    int buildingHeight;  // Coordinate's Building's height
    Coordinate();  // Default constructor
    Coordinate(int aValue, char aSide, int aBuildNo, int aBuildHeight); // Non-default constructor
	bool operator<(const Coordinate& c) const;  // Overload < operator for handling equal value cases
    static bool compareCoordinates(const Coordinate& a, const Coordinate& b);  // Comparison function for sorting algorithm
    static void sortCoordinates(vector<Coordinate> &coordinates);  // Sort array of coordinates by value
};


#endif //COORDINATE_H
