// Akif Isitan
#ifndef POINTQUADTREE_H
#define POINTQUADTREE_H

#include <string>
#include <vector>
using namespace std;

class PointQuadTree {
    public:
        explicit PointQuadTree(const string &notFound);
        void insert(const string &s, const int &x, const int &y);
        void prettyPrint() const;
        void printWithinRadius(const int &x, const int &y, const int &radius) const;
    private:
		class PQTNode {
			string cityName;
			int xCoordinate;
			int yCoordinate;
			PQTNode* NW;
			PQTNode* NE;
			PQTNode* SW;
			PQTNode* SE;
		PQTNode(const string &theCityName, const int &theXCoordinate, const int &theYCoordinate)
		  : cityName(theCityName), xCoordinate(theXCoordinate), yCoordinate(theYCoordinate),
		    NW(nullptr), NE(nullptr), SW(nullptr), SE(nullptr)  {}
		friend class PointQuadTree;
		};
        PQTNode* root;
        const string ITEM_NOT_FOUND;
        static string compare(const int &x, const int&y, PQTNode*r);
        void insert(const string &s, const int &x, const int&y, PQTNode *&radius);
        void prettyPrint(PQTNode *p) const;
        void printWithinRadius(const int &x, const int &y, const int &radius, PQTNode* t, vector<vector<string>> &v) const;
        static int nodeToSearch(const int &x, const int &y, const int &radius, PQTNode *t);
		// Return true if (x, y) is inside or on the circle with center coordinates circle_x, circle_y and radius radius
        static bool inCircle(int circle_x, int circle_y, int radius, int x, int y); 
};

#endif