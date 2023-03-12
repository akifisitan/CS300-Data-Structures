// Akif Isitan
#ifndef MPQ_H
#define MPQ_H
#include "Coordinate.h"

using namespace std;

class MPQ {
public:
    explicit MPQ(int capacity = 100);  // Constructor
    ~MPQ(); // Destructor
    void insert(const Coordinate& x, int label);  // Insert a new element into the heap with a label
    Coordinate remove(int label);  // Removes heap element with provided label
    const Coordinate& getMax() const; // Returns coordinate with max building number
    bool isEmpty() const;  // Returns true if heap is empty
    bool isFull() const;  // Returns true if heap is full

private:
    int currentSize;  // Number of current elements in heap
    int maxSize;  // Max size of heap
    vector<Coordinate> heap;  // The heap array
    vector<int> location;  // Location array for accessing labels (Building number)
    void percolateDown(int hole);  // Percolate down to maintain heap property
};


#endif //MPQ_H
