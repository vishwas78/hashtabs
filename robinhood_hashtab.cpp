// A Hash table with Robin hood Hashing
#include<bits/stdc++.h>
#include <cstdlib>
#include <ctime>
//#include <time.h>
#include <zconf.h>
#include <sys/time.h>

#define MAX_LOAD_FACTOR_PREDEFINED 0.8

using namespace std;

template<typename K, typename V>
class RobinHoodNode {
public:
    V value;
    K key;
    int dist;   // stores the distance from its ideal position

    RobinHoodNode(K key, V value, int dist) {
        this->value = value;
        this->key = key;
        this->dist = dist;
    }

    RobinHoodNode() {
        this->key = (K) NULL;
        this->value = (V) NULL;
        this->dist = 0;
    }
};

template<typename K, typename V>
class RobinHoodHashTable {
    const float MAX_LOAD_FACTOR = MAX_LOAD_FACTOR_PREDEFINED;
    int PROBE_LIMIT;
    RobinHoodNode<K, V> *table;
    int capacity;
    int size;

    RobinHoodNode<K, V> dummy;

public:
    RobinHoodHashTable() {
        capacity = 16;
        PROBE_LIMIT = static_cast<int>(log(capacity));
        size = 0;
        table = new RobinHoodNode<K, V>[capacity + PROBE_LIMIT];
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
K RobinHoodHashTable<K, V>::hashCode(K key) {
    // TODO: implement a high entropy hash function that can `truly` distribute data
    return key;
}

template<typename K, typename V>
int RobinHoodHashTable<K, V>::tableKey(K key) {
    K hash = hashCode(key);
    return hash % capacity;
}

template<typename K, typename V>
void RobinHoodHashTable<K, V>::relocate() {
    // Implementing the POWER_OF_TWO sized hash table
    cout << "Relocating" << endl;
    int prev_cap = capacity;
    capacity *= 2;
    PROBE_LIMIT = static_cast<int>(log(capacity));
    RobinHoodNode<K, V> *temp_table = table;
    table = new RobinHoodNode<K, V>[capacity + PROBE_LIMIT];

    for (int i = 0; i < prev_cap; ++i) {
        if (temp_table[i].key != (K) NULL && temp_table[i].key != (K) -1) {
            insert(temp_table[i].key, temp_table[i].value, false);
        }
    }
    delete[] temp_table;
}

template<typename K, typename V>
bool RobinHoodHashTable<K, V>::insert(K key, V value, bool new_element) {
//    cout << "Inserting: (" << key << "," << value << ")" << endl;
    int table_key = tableKey(key);
    for (int i = 0; i < PROBE_LIMIT; ++i) {
        if (table[table_key + i].key == (K) NULL || table[table_key + i].key == (K) -1 ||
            table[table_key + i].key == key) {
            table[table_key + i].dist = i;
            table[table_key + i].key = key;
            table[table_key + i].value = value;
            if (new_element) {
                size++;
            }
            if ((float) size / capacity > MAX_LOAD_FACTOR) {
                relocate();
            }
            return true;
        } else if (table[table_key + i].dist < i) {
            RobinHoodNode<K, V> tempNode = table[table_key + i];
            table[table_key + i].dist = i;
            table[table_key + i].key = key;
            table[table_key + i].value = value;
            if (new_element) {
                size++;
            }
            if ((float) size / capacity > MAX_LOAD_FACTOR) {
                relocate();
            }
            insert(tempNode.key, tempNode.value, false);
            return true;
        }
    }

    // If no place is found for the element in the region of interest
    relocate();
    return insert(key, value, new_element);
}

template<typename K, typename V>
V RobinHoodHashTable<K, V>::deleteNode(K key) {

    int table_key = tableKey(key);

    for (int i = 0; i < PROBE_LIMIT; ++i) {
        if (table[table_key + i].key == key) {
            V value = table[table_key + i].value;
            size--;
            table[table_key + i] = dummy;
            return value;
        }
    }
    return (V) NULL;
}

template<typename K, typename V>
V RobinHoodHashTable<K, V>::get(K key) {
    int table_key = tableKey(key);

    for (int i = 0; i < PROBE_LIMIT; ++i) {
        if (table[table_key + i].key == key) {
            return table[table_key + i].value;
        }
    }
    return (V) NULL;
}

template<typename K, typename V>
int RobinHoodHashTable<K, V>::sizeofMap() {
    return size;
}

template<typename K, typename V>
bool RobinHoodHashTable<K, V>::isEmpty() {
    return size != capacity;
}

template<typename K, typename V>
void RobinHoodHashTable<K, V>::display() {
//    cout << "Here! Take this for a hash table!!!" << endl;
    cout << "size of table: " << sizeofMap() << endl;
    cout << "current capacity: " << capacity << endl;
    cout << "currentLoadFactor: " << currentLoadFactor() << endl;
    cout << "The Hash Table is: " << endl;
//    for (int i = 0; i < capacity; ++i) {
//        cout << table[i].key << " : " << table[i].value << " : " << table[i].dist << endl;
//    }
}

// ------------ class function ends --------------

unsigned int hash3(unsigned int h1, unsigned int h2, unsigned int h3) {
    return (((h1 * 2654435789U) + h2) * 2654435789U) + h3;
}

int main() {
    struct timeval time_t;
    gettimeofday(&time_t, NULL);
    srand(hash3(time_t.tv_sec, time_t.tv_usec, getpid()));

    RobinHoodHashTable<int, int> table;
    for (int i = 1; i <= 500; i++) {
        table.insert(rand(), rand());
    }
    table.display();
    return 0;
};