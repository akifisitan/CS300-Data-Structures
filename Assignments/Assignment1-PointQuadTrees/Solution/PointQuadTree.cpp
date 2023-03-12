// Akif Isitan
#include <iostream>
#include <string>
#include <vector>
#include "PointQuadTree.h"

using namespace std;

// Constructor
PointQuadTree::PointQuadTree(const string &notFound): ITEM_NOT_FOUND(notFound), root(nullptr) {}

// Return the quadrant of the point quadtree rooted at node r in which node p belongs
string PointQuadTree::compare(const int &x, const int &y, PQTNode *r) {
    if (r->xCoordinate > x) {
        if (r->yCoordinate > y) 
			return "SW";
        else return "NW";
    }
    else if (r->yCoordinate > y) 
		return "SE";
    else return "NE";
}

// Call insert for the user as the user does not know the root
void PointQuadTree::insert(const string &s, const int &x, const int &y) {
    insert(s, x, y, root);
}

// Insert a value to the tree
void PointQuadTree::insert(const string &s, const int&x, const int&y, PQTNode* &r) {
    if (r == nullptr) { // Create node at the right place
        r = new PQTNode(s, x, y);
		//cout << s << " created with coordinates: "<< x << ", " << y << endl;
	}
    else if (compare(x, y, r) == "NW") {// Insert to NW
        insert(s, x, y, r->NW);
		//cout << s << " inserted to NW" << endl;
	}
    else if (compare(x, y, r) == "NE") { // Insert to NE
        insert(s, x, y, r->NE);
		//cout << s << " inserted to NE" << endl;
	}
    else if (compare(x, y, r) == "SW") { // Insert to SW
        insert(s, x, y, r->SW);
		//cout << s << " inserted to SW" << endl;
	}
    else if (compare(x, y, r) == "SE") {// Insert to SE
        insert(s, x, y, r->SE);
		//cout << s << " inserted to SE" << endl;
	}
    else throw "invalid_quadrant"; // Should not happen
}

// Call prettyPrint for the user as the user does not know the root
void PointQuadTree::prettyPrint() const {
    prettyPrint(root);
}

// Pretty print the tree
void PointQuadTree::prettyPrint(PQTNode *p) const {
    if (p != nullptr) {
        cout << p->cityName << endl;
        prettyPrint(p->SE); // recursively print the south-east subtree
        prettyPrint(p->SW); // recursively print the south-west subtree
        prettyPrint(p->NE); // recursively print the north-east subtree
        prettyPrint(p->NW); // recursively print the north-west subtree
    }
}

// Return true if point is inside or on top of the circle
bool PointQuadTree::inCircle(int circle_x, int circle_y, int radius, int x, int y) {
    int distance = ((x - circle_x) * (x - circle_x)) + ((y - circle_y) * (y - circle_y));
    if (distance <= radius * radius)
        return true;
    else
        return false;
}

// Returns the case to be searched according to given coordinates
int PointQuadTree::nodeToSearch(const int &x, const int &y, const int &radius, PQTNode *t) {
    const int root_x = t->xCoordinate;
    const int root_y = t->yCoordinate;

	// Left side of left vertical tangent line 
    if (root_x < x-radius) {
        if (root_y > y+radius)
            return 1;
		else if (root_y == y+radius)
			return 'M';
		else if ((y+radius > root_y) && (root_y > y-radius))
            return 4;
		else if (root_y == y-radius)
			return 'L';
        else if (root_y < y-radius)
            return 6;
		else 
			throw "error";
    }
	// Between left and right vertical tangent lines
	else if ((x-radius < root_x) && (root_x < x+radius)) {
        if (root_y > y+radius)
            return 2;
        else if (root_y < y-radius)
            return 7;
		else if (root_y==y+radius) {
			if (root_x < x)
				return 'A';
			else if (x < root_x)
				return 'B';
			else 
				throw "error";
		}
		else if (root_y==y-radius) {
			if (root_x < x)
				return 'F';
			else if (x < root_x) 
				return 'E';
			else 
				return 13;
		}
		else if (!inCircle(x, y, radius, root_x, root_y)) {
			if (root_x < x) {
				if (root_y < y)
					return 11;
				else if (root_y > y)
					return 9;
				else return 13;
			}
			else if (root_x > x) {
				if (root_y > y) 
					return 10;
				else if (root_y < y) 
					return 12;
				else return 13;
			}
			else return 13;
		}
		else return 13;
    }
	// Right side of the right vertical tangent line
    else if (x+radius < root_x) {
        if (root_y > y+radius)
            return 3;
		else if (root_y == y+radius)
			return 'P';
		else if ((y+radius > root_y) && (root_y > y-radius))
            return 5;
		else if (root_y == y-radius)
			return 'R';
        else if (root_y < y-radius)
            return 8;
		else throw "error";
    }
	// On top of the left vertical tangent line to circle
	else if (x-radius==root_x) {
        if ((y+radius > root_x) && (root_x > y))
            return 'I';
        else if ((root_y > y) && (root_y > y-radius))
            return 'G';
        else if (y + radius < root_y)
            return 'N';
        else if (root_y < y - radius)
            return 'K';
		else if (root_y == y - radius)
			return 'W';
		else if (root_y == y + radius)
			return 'X';
		else throw "error";
    }
	// On top of the right vertical tangent line to circle 
	else if (root_x==x+radius) {
        if ((y+radius > root_x) && (root_x > y))
            return 'C';
        else if ((root_y > y) && (root_y > y-radius))
            return 'D';
        else if (y + radius < root_y)
            return 'O';
        else if (root_y < y - radius)
            return 'J';
		else if (root_y == y - radius)
			return 'Z';
		else if (root_y == y + radius)
			return 'Y';
		else throw "error";
    }
	// Should not happen
	else
		throw "error";
    
}

void PointQuadTree::printWithinRadius(const int &x, const int &y, const int &radius) const {
    vector <vector<string>> cityVector; // Contains found cities vector at index 0, visited cities vector at index 1
	vector<string> foundCityVector, visitedCityVector;
	cityVector.push_back(foundCityVector);
	cityVector.push_back(visitedCityVector);
	printWithinRadius(x, y, radius, root, cityVector);
	// No cities found
	if (cityVector.at(0).size() == 0) 
		cout << "<None>" << endl;
	// Print found cities
	else { 
		for (unsigned int i=0; i < cityVector.at(0).size(); i++) {
			if (i != cityVector.at(0).size() - 1) 
				cout << cityVector.at(0).at(i) << ", ";
			else
				cout << cityVector.at(0).at(i) << endl;
		}
	}
	// Print visited cities
	for (unsigned int i=0; i < cityVector.at(1).size(); i++) {
		if (i != cityVector.at(1).size() - 1) 
			cout << cityVector.at(1).at(i) << ", ";
		else
			cout << cityVector.at(1).at(i) << endl;
	}
	cout << endl;
}

void PointQuadTree::printWithinRadius(const int &x, const int &y, const int &radius, PQTNode *t, vector<vector<string>> &v) const {
	if (t != nullptr) {

        // Add each visited city to the vector
		v.at(1).push_back(t->cityName);

		// Add city to found cities if city coordinates within the circle
        if (inCircle(x, y, radius, t->xCoordinate, t->yCoordinate)) {
			
			v.at(0).push_back(t->cityName);
        }

		// Check which quadrants to keep searching
        const int r = nodeToSearch(x, y, radius, t);
		
        if (r == 1 || r == 'N')
            printWithinRadius(x, y, radius, t->SE, v);
        else if (r == 2 || r == 'O') {
            printWithinRadius(x, y, radius, t->SE, v);
            printWithinRadius(x, y, radius, t->SW, v);
        }
        else if (r == 3)
            printWithinRadius(x, y, radius, t->SW, v);
        else if (r == 4 || r == 'G' || r == 'I' || r == 'M' || r == 'X') {
            printWithinRadius(x, y, radius, t->SE, v);
            printWithinRadius(x, y, radius, t->NE, v);
        }
        else if (r == 5 || r == 'P') {
            printWithinRadius(x, y, radius, t->SW, v);
            printWithinRadius(x, y, radius, t->NW, v);
        }
        else if (r == 6 || r == 'K' || r == 'L' || r == 'W') {
            printWithinRadius(x, y, radius, t->NE, v);
        }
        else if (r == 7 || r == 'E' || r == 'F' || r == 'J' || r == 'Z') {
            printWithinRadius(x, y, radius, t->NE, v);
            printWithinRadius(x, y, radius, t->NW, v);
        }
        else if (r == 8 || r == 'R') {
            printWithinRadius(x, y, radius, t->NW, v);
        }
        else if (r == 9 || r == 'A') {
            printWithinRadius(x, y, radius, t->SE, v);
            printWithinRadius(x, y, radius, t->SW, v);
            printWithinRadius(x, y, radius, t->NE, v);
        }
        else if (r == 10 || r == 'B' || r == 'C' || r == 'Y') {
            printWithinRadius(x, y, radius, t->SE, v);
            printWithinRadius(x, y, radius, t->SW, v);
            printWithinRadius(x, y, radius, t->NW, v);
        }
        else if (r == 11) {
            printWithinRadius(x, y, radius, t->SE, v);
            printWithinRadius(x, y, radius, t->NE, v);
            printWithinRadius(x, y, radius, t->NW, v);
        }
        else if (r == 12 || r == 'D') {
            printWithinRadius(x, y, radius, t->SW, v);
            printWithinRadius(x, y, radius, t->NE, v);
            printWithinRadius(x, y, radius, t->NW, v);
        }
        else if (r == 13) {
            printWithinRadius(x, y, radius, t->SE, v);
            printWithinRadius(x, y, radius, t->SW, v);
            printWithinRadius(x, y, radius, t->NE, v);
            printWithinRadius(x, y, radius, t->NW, v);
        }
		else 
			throw "unknown_r_value"; // should not happen
    }
}













