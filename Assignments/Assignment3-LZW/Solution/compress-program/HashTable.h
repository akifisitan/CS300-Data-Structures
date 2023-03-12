// akifisitan
#ifndef CS300HW3_BETA_HASHTABLE_H
#define CS300HW3_BETA_HASHTABLE_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Hash table class
template <class Key, class Value>
class HashTable {
public:
    // Maximum size of the dictionary
    int maxSize;
    // Constructor
    explicit HashTable(const Key& notFound, int size);
    // Hashing Function (For strings)
    int hash(const Key& key, int tableSize) const;
    // Enum for Items in the dictionary
    enum EntryType {ACTIVE, EMPTY, DELETED};
    // Remove key value pair from the dictionary
    void remove(const Key& key);
    // Return true if the dictionary contains a given key
    bool contains(const Key& key) const;
    // Return the key if the dictionary contains a given key
    const Key& find(const Key& key) const;
    // Insert key value pair into the dictionary
    void insert(const Key& key, const Value& value);
    // Similar to find, but instead of returning NOT_FOUND, throws an exception if key is not in the dictionary
    const Value& operator[](const Key& key);
    // Return true if dictionary stores no elements
    bool isEmpty() const;
    // Print the dictionary
    void print();
    // Returns the number of elements stored in the dictionary
    int size();

private:
    // Hash table item
    struct Item {
        EntryType info;
        Key key;
        Value value;
        explicit Item(EntryType i = EMPTY, const Key& aKey = Key(), const Value& aValue = Value())
                : info(i), key(aKey), value(aValue) {};
    };
    // Number of elements stored in the dictionary
    int currentSize;
    // Return value for find
    const Key ITEM_NOT_FOUND;
    // Hash Table
    vector<Item> table;
    // Return true if item is marked as active
    bool isActive(int currentPos) const;
    // Find position of the key in the table
    int findPos(const Key& key) const;
    // Rehash the table to lower load factor
    void rehash();
    // Helper functions to make table size prime
    static bool isPrime(int n);
    static int nextPrime(int n);
};

// #include "HashTable.cpp" need to exclude .cpp from project, instead just included both .h and .cpp in main
#endif //CS300HW3_BETA_HASHTABLE_H
