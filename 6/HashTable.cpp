#include "HashTable.h"

HashTable::HashTable(int size) : size(size) {
    table = new HashNode*[size];
    initialize();
}

HashTable::~HashTable() {
    cleanup();
    delete[] table;
}

void HashTable::initialize() {
    for (int i = 0; i < size; ++i) {
        table[i] = nullptr;
    }
}

int HashTable::hashFunction(const string& key) {
    int hash = 0;
    for (char ch : key) {
        hash += ch;
    }
    return hash % size;
}

void HashTable::insert(const std::string& key, const std::string& value) {
    int index = hashFunction(key);
    HashNode* temp = table[index];

    while (temp != nullptr) {
        if (temp->key == key) {
            // Заменяем все значения для данного ключа на новое значение
            ValueNode* oldValues = temp->values;
            
            // Очищаем старые значения
            while (oldValues != nullptr) {
                ValueNode* toDelete = oldValues;
                oldValues = oldValues->next;
                delete toDelete;
            }

            // Устанавливаем новое значение
            temp->values = new ValueNode(value);
            return;
        }
        temp = temp->next;
    }

    // Если ключ не найден, создаем новый узел с этим ключом и значением
    HashNode* newNode = new HashNode(key, value);
    newNode->next = table[index];
    table[index] = newNode;  // Вставка в начало списка
}

std::string HashTable::get(const std::string& key) {
    int index = hashFunction(key);
    HashNode* temp = table[index];

    while (temp != nullptr) {
        if (temp->key == key) {
            // Собираем все значения в одну строку, разделяя запятыми
            std::string result;
            ValueNode* valNode = temp->values;
            while (valNode != nullptr) {
                if (!result.empty()) {
                    result += ", ";
                }
                result += valNode->value;
                valNode = valNode->next;
            }
            return result;
        }
        temp = temp->next;
    }

    throw std::out_of_range("Key not found");
}

void HashTable::remove(const std::string& key) {
    int index = hashFunction(key);
    HashNode* temp = table[index];
    HashNode* prev = nullptr;

    while (temp != nullptr && temp->key != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == nullptr) {
        std::cerr << "Key not found" << std::endl;
        return;
    }

    // Удаляем все значения, связанные с ключом
    ValueNode* valNode = temp->values;
    while (valNode != nullptr) {
        ValueNode* toDelete = valNode;
        valNode = valNode->next;
        delete toDelete;
    }

    // Удаляем узел ключа
    if (prev == nullptr) {
        table[index] = temp->next;
    } else {
        prev->next = temp->next;
    }

    delete temp;
}

void HashTable::cleanup() {
    for (int i = 0; i < size; ++i) {
        HashNode* temp = table[i];
        while (temp != nullptr) {
            HashNode* toDelete = temp;
            temp = temp->next;
            delete toDelete;
        }
        table[i] = nullptr;  // Обнуление указателя
    }
}
