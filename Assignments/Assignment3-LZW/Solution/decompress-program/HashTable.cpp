// akifisitan
#include "HashTable.h"

using namespace std;

// Constructor
template <class Key, class Value>
HashTable<Key, Value>::HashTable(const Key& notFound, int size)
        : ITEM_NOT_FOUND(notFound), maxSize(nextPrime(size)),  table(maxSize), currentSize(0) {}

// Hashing function, mainly for strings
template<class Key, class Value>
int HashTable<Key, Value>::hash(const Key &key, int tableSize) const {
    int sum = 0;
    for (unsigned char c : key)
        sum += (int) c;
    return sum % tableSize;
}

// Find position of the key in the table
template<class Key, class Value>
int HashTable<Key, Value>::findPos(const Key &key) const {
    int p = hash(key, table.size());
    while(table[p].info != EMPTY && table[p].key != key) {
        p = (p + 1) % table.size();
    }
    return p;
}

// Return true if item is marked as active
template<class Key, class Value>
bool HashTable<Key, Value>::isActive(int currentPos) const {
    return table[currentPos].info == ACTIVE;
}

// Remove key value pair from the dictionary
template<class Key, class Value>
void HashTable<Key, Value>::remove(const Key& key) {
    int currentPos = findPos(key);
    if (isActive(currentPos)) {
        table[currentPos].info = DELETED;
        currentSize--;
    }
}

// Return the key if the dictionary contains a given key
template<class Key, class Value>
const Key& HashTable<Key, Value>::find(const Key &key) const {
    int currentPos = findPos(key);
    if (isActive(currentPos))
        return table[currentPos].key;
    return ITEM_NOT_FOUND;
}

// Insert key value pair into the dictionary
template <class Key, class Value>
void HashTable<Key, Value>::insert(const Key& key, const Value& value) {
    // Insert x as active
    int currentPos = findPos(key);
    if(isActive(currentPos))
        return;
    table[currentPos] = Item(ACTIVE, key, value);
    // enlarge the hash table if necessary
    if(++currentSize >= table.size() / 2)
        rehash();
}

// Rehash the table to lower load factor
template<class Key, class Value>
void HashTable<Key, Value>::rehash() {
    vector<Item> oldArray = table;
    // Create new double-sized, empty table
    table.resize(nextPrime(2 * oldArray.size()));
    for(unsigned int j = 0; j < table.size(); j++)
        table[j].info = EMPTY;
    // Copy table over
    currentSize = 0;
    for(int i = 0; i < oldArray.size(); i++)
        if (oldArray[ i ].info == ACTIVE)
            insert(oldArray[i].key, oldArray[i].value);
}

// Check if a number is prime
template<class Key, class Value>
bool HashTable<Key, Value>::isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// Compute next closest prime of given integer
template<class Key, class Value>
int HashTable<Key, Value>::nextPrime(int n) {
    // Check if the given number is already prime
    if (isPrime(n)) return n;
    // Start checking from the next odd number
    int i = n + (n % 2 == 0 ? 1 : 2);
    while (!isPrime(i))
        i += 2;
    return i;
}

// Print dictionary
template<class Key, class Value>
void HashTable<Key, Value>::print() {
    cout << "{";
    for (Item i : table) {
        if (i.info == ACTIVE)
            cout << i.key << ": " << i.value << ", ";
    }
    cout << "}";
}

// Return true if dictionary is empty
template<class Key, class Value>
bool HashTable<Key, Value>::isEmpty() const {
    return currentSize == 0;
}

// Overload operator [] to access value of given key
template<class Key, class Value>
const Value &HashTable<Key, Value>::operator[](const Key &key) {
    int currentPos = findPos(key);
    if (isActive(currentPos))
        return table[currentPos].value;
    throw out_of_range("Key error");
}

// Return true if dictionary contains given key
template<class Key, class Value>
bool HashTable<Key, Value>::contains(const Key &key) const {
    if (isActive(findPos(key)))
        return true;
    return false;
}

// Return the number of elements in the dictionary
template<class Key, class Value>
int HashTable<Key, Value>::size() {
    return currentSize;
}
