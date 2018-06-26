// A simple Hash table with linear probing and open addressing
#include<bits/stdc++.h>

#define MAX_LOAD_FACTOR_PREDEFINED 0.9

using namespace std;

template<typename K, typename V>
class HashNode {
public:
    V value;
    K key;

    HashNode(K key, V value) {
        this->value = value;
        this->key = key;
    }

    HashNode() {
        this->key = (K) NULL;
        this->value = (V) NULL;
    }
};

template<typename K, typename V>
class SimpleHashTable {
    const float MAX_LOAD_FACTOR = MAX_LOAD_FACTOR_PREDEFINED;
    HashNode<K, V> *table;
    int capacity;
    int size;

    HashNode<K, V> dummy;

public:
    SimpleHashTable() {
        capacity = 16;
        size = 0;
        table = new HashNode<K, V>[capacity];
        dummy.key = (K) -1;
        dummy.value = (V) -1;
    }

    K hashCode(K key);

    int tableKey(K key);

    void relocate();

    bool insert(K key, V value, bool new_element = true);

    V deleteNode(K key);

    V get(K key);

    int sizeofMap();

    bool isEmpty();

    void display();

    float currentLoadFactor() {
        return (float) size / capacity;
    }
};

// --------------- class methods ---------------------
template<typename K, typename V>
K SimpleHashTable<K, V>::hashCode(K key) {
    return key;
}

template<typename K, typename V>
int SimpleHashTable<K, V>::tableKey(K key) {
    K hash = hashCode(key);
    return hash % capacity;
}

template<typename K, typename V>
void SimpleHashTable<K, V>::relocate() {
    // Implementing the POWER_OF_TWO sized hash table
    cout << "Relocating" << endl;
    int prev_cap = capacity;
    capacity *= 2;
    HashNode<K, V> *temp_table = table;
    table = new HashNode<K, V>[capacity];

    for (int i = 0; i < prev_cap; ++i) {
        if (temp_table[i].key != (K) NULL && temp_table[i].key != (K) -1) {
            insert(temp_table[i].key, temp_table[i].value, false);
        }
    }
    delete[] temp_table;
}

template<typename K, typename V>
bool SimpleHashTable<K, V>::insert(K key, V value, bool new_element = true) {
//    cout << "Inserting: (" << key << "," << value << ")" << endl;
    int table_key = tableKey(key);
    for (int i = 0; i < capacity; ++i) {
        if (table[(table_key + i) % capacity].key == (K) NULL || table[(table_key + i) % capacity].key == (K) -1 ||
            table[(table_key + i) % capacity].key == key) {
            table[(table_key + i) % capacity].key = key;
            table[(table_key + i) % capacity].value = value;
            size++;
            if ((float) size / capacity > MAX_LOAD_FACTOR) {
                relocate();
            }
            return true;
        }
    }
    // the execution will never reach here as there MAX_LOAD_FACTOR is 0.5 and half the table will always be empty so
    // the element will find empty spaces to rest;
}

template<typename K, typename V>
V SimpleHashTable<K, V>::deleteNode(K key) {

    int table_key = tableKey(key);

    for (int i = 0; i < capacity; ++i) {
        if (table[(table_key + i) % capacity].key == key) {
            V value = table[(table_key + i) % capacity].value;
            size--;
            table[(table_key + i) % capacity] = dummy;
            return value;
        }
    }
    return NULL;
}

template<typename K, typename V>
V SimpleHashTable<K, V>::get(K key) {
    int table_key = tableKey(key);

    for (int i = 0; i < capacity; ++i) {
        if (table[(table_key + i) % capacity].key == key) {
            return table[(table_key + i) % capacity].value;
        }
    }
    return NULL;
}

template<typename K, typename V>
int SimpleHashTable<K, V>::sizeofMap() {
    return size;
}

template<typename K, typename V>
bool SimpleHashTable<K, V>::isEmpty() {
    return size != capacity;
}

template<typename K, typename V>
void SimpleHashTable<K, V>::display() {
//    cout << "Here! Take this for a hash table!!!" << endl;
    cout << "size of table: " << sizeofMap() << endl;
    cout << "current capacity: " << capacity << endl;
    cout << "currentLoadFactor: " << currentLoadFactor() << endl;
    cout << "The Hash Table is: " << endl;
    for (int i = 0; i << capacity; ++i) {
        cout << table[i].key << ": " << table[i].value << endl;
    }
}

// ------------ class function ends --------------

int main() {
    SimpleHashTable<int, int> table;
    for (int i = 1; i <= 5000; i++) {
        table.insert(i, i);
    }
    table.display();
    return 0;
};