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
        capacity = 8;
        size = 0;
        table = new CuckooNode<K, V>[capacity];
        dummy.key = (K) -1;
        dummy.value = (V) -1;
    }

    K hashCode1(K key);

    K hashCode2(K key);

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
    return key * 11;
}

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
    cout << "Relocation complete" << endl;
}

template<typename K, typename V>
bool CuckooHashTable<K, V>::insert(K key, V value, bool new_element) {
    cout << "Inserting: (" << key << "," << value << "," << new_element << ") " << endl;
    K hash1 = hashCode1(key);
    int table_key_1 = tableKey(hash1);
    if (tracker xor key) {
        cout << 1 << endl;
        if (table[table_key_1].key == (K) NULL || table[table_key_1].key == (K) -1 || table[table_key_1].key == key) {
            cout << 2 << endl;
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
                cout << 3 << endl;
                table[table_key_2].key = key;
                table[table_key_2].value = value;
                if (new_element) {
                    size++;
                }
                tracker = 0;
                return true;
            } else {
                cout << 4 << endl;
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
        return insert(key, value, new_element);
    }
}

template<typename K, typename V>
V CuckooHashTable<K, V>::deleteNode(K key) {
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
//    TODO: change the xoring scheme for tracker as it takes twice many cycles to detect the loop. This can be very sloppy if whole table is traversed in replacing
//    int test_arr[] = {1, 7, 3, 12, 2, 4};
    int test_arr[] = {3658, 1829, 7236, 728, 1088, 4022, 3469, 2889, 1550, 3814, 1906, 6297, 9620, 4910, 5963, 6391,
                      8062};

    CuckooHashTable<int, int> table;
    for (int i = 0; i < sizeof(test_arr) / sizeof(test_arr[0]); i++) {
        cout << test_arr[i] << endl;
        table.insert(test_arr[i], i + 1);
    }
    table.display();
    return 0;
};