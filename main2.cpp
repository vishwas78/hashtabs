#include<bits/stdc++.h>

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
        this->key = (K) NULL;       // TODO: this gives warning about NULL converting to int
        this->value = (V) NULL;
    }
};

template<typename K, typename V>
class HashTableBase {
    const float LOAD_FACTOR = 0.5;
    HashNode<K, V> *table;
    int capacity;
    int size;

    HashNode<K, V> dummy;

public:
    HashTableBase() {
        capacity = 16;
        size = 0;
        table = new HashNode<K, V>[capacity];
        dummy.key = (K) -1;
        dummy.value = (V) -1;
    }

    K hashCode(K key);

    int tableKey(K key);

    void relocate();

    bool insert(K key, V value);

    V deleteNode(K key);

    V get(K key);

    int sizeofMap();

    bool isEmpty();

    void display();
};

// --------------- class methods ---------------------
template<typename K, typename V>
K HashTableBase<K, V>::hashCode(K key) {
    return key;
}

template<typename K, typename V>
int HashTableBase<K, V>::tableKey(K key) {
    K hash = hashCode(key);
    return hash % capacity;
}

template<typename K, typename V>
void HashTableBase<K, V>::relocate() {
    // Implementing the POWER_OF_TWO sized hash table
    cout << "Relocating" << endl;
    int prev_cap = capacity;
    capacity *= 2;
    HashNode<K, V> *temp_table = table;
    table = new HashNode<K, V>[capacity];

    for (int i = 0; i < prev_cap; ++i) {
        if (temp_table[i].key != (K) NULL && temp_table[i].key != (K) -1) {
            insert(temp_table[i].key, temp_table[i].value);
        }
    }
    delete[] temp_table;
}

template<typename K, typename V>
bool HashTableBase<K, V>::insert(K key, V value) {
    cout << "Inserting: (" << key << "," << value << ")" << endl;
    int table_key = tableKey(key);

    for (int i = 0; i < capacity; ++i) {
        if (table[table_key + i].key == (K) NULL && table[table_key + i].key == (K) -1 && table[table_key + i].key == key) {
            table[table_key + i].key = key;
            table[table_key + i].value = value;
            size++;
            if (size / capacity > LOAD_FACTOR) {
                relocate();
            }
            return true;
        }
    }
    // the execution will never reach here as there LOAD_FACTOR is 0.5 and half the table will always be empty so
    // the element will find empty spaces to rest;
//    relocate();
//    return insert(key, value);
}

template<typename K, typename V>
V HashTableBase<K, V>::deleteNode(K key) {

    int hashcode = tableKey(key);

    for (int i = 0; i < capacity; ++i) {
        if (table[hashcode + i].key == key) {
            V value = table[hashcode + i].value;
            size--;
//            table[hashcode + i].key = (K) -1;
//            table[hashcode + i].value = (V) -1;
            table[hashcode + i] = dummy;
            return value;
        }
    }
    return NULL;
}

template<typename K, typename V>
V HashTableBase<K, V>::get(K key) {
    int hashcode = tableKey(key);

    for (int i = 0; i < capacity; ++i) {
        if (table[hashcode + i].key == key) {
            return table[hashcode + i].value;
        }
    }
    return NULL;
}

template<typename K, typename V>
int HashTableBase<K, V>::sizeofMap() {
    return size;
}

template<typename K, typename V>
bool HashTableBase<K, V>::isEmpty() {
    return size != capacity;
}

template<typename K, typename V>
void HashTableBase<K, V>::display() {
    cout << "Here! Take this for a hash table!!!" << endl;
}

// ------------ class function ends --------------

int main() {
    HashTableBase<int, int> table;
//    cout << table.tableKey(175) << endl
    for (int i = 1; i <= 50; i++) {
        cout << i << endl;
        table.insert(i, i);
    }


    return 0;
};