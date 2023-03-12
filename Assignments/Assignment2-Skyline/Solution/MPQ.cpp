// Akif Isitan
#include "MPQ.h"

// Constructor
MPQ::MPQ(int capacity) {
    currentSize = 0;
    maxSize = capacity;
    heap = vector<Coordinate>(capacity);
    location = vector<int>(capacity, -1);
}

// Destructor
MPQ::~MPQ() {
    heap.clear();
    location.clear();
}

// Insert a new element into the heap with a label
void MPQ::insert(const Coordinate &x, int label) {
    if (isFull())
        throw overflow_error("Heap is full!");
    int hole = ++currentSize;
	// Move hole upward to insert the element, make sure to keep locations updated
    for ( ; hole > 1 && x.buildingHeight > heap[hole / 2].buildingHeight; hole /= 2) {
        heap[hole] = heap[hole / 2];
        location[heap[hole].buildingNo] = hole;
    }
	// Insert element into the hole & its label location accordingly
    heap[hole] = x;
    location[label] = hole;
}

// Removes heap element with provided label
Coordinate MPQ::remove(int label) {
    if (isEmpty())
        throw underflow_error("Empty heap!");
    Coordinate removedLabel = heap[location[label]];
	// Logically remove the element from the heap
    heap[location[label]] = heap[currentSize--];
	// Percolate down the newly open hole to keep heap property
    percolateDown(location[label]);
	// Remove label
    location[label] = -1;
    return removedLabel;
}

// Returns coordinate with max building number
const Coordinate& MPQ::getMax() const {
    if (isEmpty()) throw out_of_range("Empty heap! Cannot get max element!");
    return heap[1];
}

// Percolate down hole to maintain heap property
void MPQ::percolateDown(int hole) {
    int child;
    Coordinate temp = heap[hole];
    for ( ; hole * 2 <= currentSize; hole = child) {
        child = hole * 2;
        if (child != currentSize && heap[child + 1].buildingHeight > heap[child].buildingHeight)
            child++;
		// Make sure to keep track of label location when percolating down
        if (heap[child].buildingHeight > temp.buildingHeight) {
            heap[hole] = heap[child];
            location[heap[hole].buildingNo] = hole;
        }
        else break;
    }
    heap[hole] = temp;
    location[temp.buildingNo] = hole;
}

// Check if heap is empty
bool MPQ::isEmpty() const {
    return currentSize == 0;
}

// Check if heap is full
bool MPQ::isFull() const {
    return currentSize == maxSize;
}
