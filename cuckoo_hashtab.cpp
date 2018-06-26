// A Cuckoo Table
#include<bits/stdc++.h>

//#define MAX_LOAD_FACTOR_PREDEFINED 0.9

using namespace std;

template<typename K, typename V>
class CuckooNode {
public:
    V value;
    K key;

    CuckooNode(K key, V value) {
        this->value = value;
        this->key = key;
    }

    CuckooNode() {
        this->key = (K) NULL;
        this->value = (V) NULL;
    }
};

template<typename K, typename V>
class CuckooHashTable {
//    const float MAX_LOAD_FACTOR = MAX_LOAD_FACTOR_PREDEFINED;
    CuckooNode<K, V> *table;
    int capacity;
    int size;
    int tracker;  // to keep track of the elements that have been reassigned while a single insertion process by using xor for integers

    CuckooNode<K, V> dummy;

public:
    CuckooHashTable() {
        tracker = 0;
        capacity = 16;
        size = 0;
        table = new CuckooNode<K, V>[capacity];
        dummy.key = (K) -1;
        dummy.value = (V) -1;
    }

    K hashCode1(K key);

    K hashCode2(K key);
//    K hashCode3(K key);     // using three hash functions gives us ability to use almost 90% of table before relocation

    int tableKey(K hash);

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
K CuckooHashTable<K, V>::hashCode1(K key) {
    return key;
}

template<typename K, typename V>
K CuckooHashTable<K, V>::hashCode2(K key) {
    return key * 4913757;
}

//template<typename K, typename V>
//K CuckooHashTable<K, V>::hashCode3(K key) {
//    return key * 35984654;
//}

template<typename K, typename V>
int CuckooHashTable<K, V>::tableKey(K hash) {
    return hash % capacity;
}

template<typename K, typename V>
void CuckooHashTable<K, V>::relocate() {
    // Implementing the POWER_OF_TWO sized hash table
    cout << "Relocating" << endl;
    int prev_cap = capacity;
    capacity *= 2;
    CuckooNode<K, V> *temp_table = table;
    table = new CuckooNode<K, V>[capacity];

    for (int i = 0; i < prev_cap; ++i) {
        if (temp_table[i].key != (K) NULL && temp_table[i].key != (K) -1) {
            insert(temp_table[i].key, temp_table[i].value, false);
        }
    }
    delete[] temp_table;
}

template<typename K, typename V>
bool CuckooHashTable<K, V>::insert(K key, V value, bool new_element) {
    cout << "Inserting: (" << key << "," << value << ")" << endl;
    K hash1 = hashCode1(key);
    int table_key_1 = tableKey(hash1);
    if (tracker xor key) {
        if (table[table_key_1].key == (K) NULL || table[table_key_1].key == (K) -1 || table[table_key_1].key == key) {
            table[table_key_1].key = key;
            table[table_key_1].value = value;
            if (new_element) {
                size++;
            }
            tracker = 0;
            return true;
        } else {
            K hash2 = hashCode2(key);
            int table_key_2 = tableKey(hash2);
            if (table[table_key_2].key == (K) NULL || table[table_key_2].key == (K) -1 ||
                table[table_key_2].key == key) {
                table[table_key_2].key = key;
                table[table_key_2].value = value;
                if (new_element) {
                    size++;
                }
                tracker = 0;
                return true;
            } else {
                CuckooNode<K, V> temp_node = table[table_key_1];
                table[table_key_1].key = key;
                table[table_key_1].value = value;
                if (new_element) {
                    size++;
                }
                tracker = tracker xor key;
                return insert(temp_node.key, temp_node.value, false);
            }
        }
    } else {
        relocate();
        insert(key, value, new_element);
    }
}

template<typename K, typename V>
V CuckooHashTable<K, V>::deleteNode(K key) {

    int table_key = tableKey(key);

//    for (int i = 0; i < capacity; ++i) {
//        if (table[(table_key + i) % capacity].key == key) {
//            V value = table[(table_key + i) % capacity].value;
//            size--;
//            table[(table_key + i) % capacity] = dummy;
//            return value;
//        }
//    }
//    return NULL;
    K hash1 = hashCode1(key);
    int table_key1 = tableKey(hash1);
    if (table[table_key1].key == key) {
        V value = table[table_key1].value;
        size--;
        table[table_key1] = dummy;
        return value;
    } else {
        K hash2 = hashCode2(key);
        int table_key2 = tableKey(hash2);
        if (table[table_key2].key == key) {
            V value = table[table_key2].value;
            size--;
            table[table_key2] = dummy;
            return value;
        } else
            return NULL;
    }

}

template<typename K, typename V>
V CuckooHashTable<K, V>::get(K key) {
    K hash1 = hashCode1(key);
    int table_key1 = tableKey(hash1);
    if (table[table_key1].key == key)
        return table[table_key1].value;
    else {
        K hash2 = hashCode2(key);
        int table_key2 = tableKey(hash2);
        if (table[table_key2].key == key)
            return table[table_key2].value;
        else
            return NULL;
    }

//    for (int i = 0; i < capacity; ++i) {
//        if (table[(table_key + i) % capacity].key == key) {
//            return table[(table_key + i) % capacity].value;
//        }
//    }

//    return NULL;
}

template<typename K, typename V>
int CuckooHashTable<K, V>::sizeofMap() {
    return size;
}

template<typename K, typename V>
bool CuckooHashTable<K, V>::isEmpty() {
    return size != capacity;
}

template<typename K, typename V>
void CuckooHashTable<K, V>::display() {
//    cout << "Here! Take this for a hash table!!!" << endl;
    cout << "size of table: " << sizeofMap() << endl;
    cout << "current capacity: " << capacity << endl;
    cout << "currentLoadFactor: " << currentLoadFactor() << endl;
    cout << "The Hash Table is: " << endl;
    for (int i = 0; i < capacity; ++i) {
        cout << table[i].key << ": " << table[i].value << endl;
    }
}

// ------------ class function ends --------------

int main() {
    CuckooHashTable<int, int> table;
    for (int i = 10; i <= 30; i++) {
        table.insert(i, i);
    }
    table.display();
    return 0;
};