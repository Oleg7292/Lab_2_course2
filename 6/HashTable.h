#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;

struct ValueNode {
    string value;
    ValueNode* next;

    ValueNode(const string& val) : value(val), next(nullptr) {}
};

struct HashNode {
    string key;
    ValueNode* values;  // Указатель на начало списка значений для ключа
    HashNode* next;

    HashNode(const string& k, const string& val)
        : key(k), next(nullptr) {
        values = new ValueNode(val);  // Инициализируем список значений первым элементом
    }
};

struct HashTable {
    HashNode** table;  // Указатель на массив указателей
    int size;          // Размер таблицы

    HashTable(int size = 10);
    ~HashTable();

    void initialize();
    int hashFunction(const string& key);
    void insert(const string& key, const string& value);
    string get(const string& key);
    void remove(const string& key);
    void cleanup();
};

#endif
