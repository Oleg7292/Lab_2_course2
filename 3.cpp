#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>

using namespace std;

struct HashSet {
    struct Node {
        string value;
        Node* next;

        Node(const string& val) : value(val), next(nullptr) {}
    };

    Node** table;
    size_t capacity;
    size_t size;

    HashSet(size_t initialCapacity = 1024)
        : capacity(initialCapacity), size(0) {
        table = (Node**)malloc(sizeof(Node*) * capacity);
        memset(table, 0, sizeof(Node*) * capacity);
    }

    ~HashSet() {
        for (size_t i = 0; i < capacity; ++i) {
            Node* current = table[i];
            while (current) {
                Node* toDelete = current;
                current = current->next;
                delete toDelete;
            }
        }
        free(table);
    }

    size_t hash(const string& key) const {
        size_t hashValue = 0;
        for (char ch : key) {
            hashValue = (hashValue * 31 + ch) % capacity;
        }
        return hashValue;
    }

    void Add(const string& value) {
        size_t index = hash(value);
        Node* current = table[index];
        while (current) {
            if (current->value == value) {
                return;
            }
            current = current->next;
        }
        Node* newNode = new Node(value);
        newNode->next = table[index];
        table[index] = newNode;
        ++size;
    }

    bool Remove(const string& value) {
        size_t index = hash(value);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current) {
            if (current->value == value) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    table[index] = current->next;
                }
                delete current;
                --size;
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    bool Contains(const string& value) const {
        size_t index = hash(value);
        Node* current = table[index];
        while (current) {
            if (current->value == value) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    void Print() const {
        for (size_t i = 0; i < capacity; ++i) {
            Node* current = table[i];
            while (current) {
                cout << current->value << " ";
                current = current->next;
            }
        }
        cout << endl;
    }

    int Sum() const {
        int total = 0;
        for (size_t i = 0; i < capacity; ++i) {
            Node* current = table[i];
            while (current) {
                total += stoi(current->value);
                current = current->next;
            }
        }
        return total;
    }

    // Копирует все элементы множества в массив
    int ExtractElements(int* arr) const {
        int index = 0;
        for (size_t i = 0; i < capacity; ++i) {
            Node* current = table[i];
            while (current) {
                arr[index++] = stoi(current->value);
                current = current->next;
            }
        }
        return index;
    }
};

// Рекурсивная функция для поиска подмножества
bool findSubset(int* arr, int n, bool* used, int targetSum, int currentSum, HashSet& subset) {
    if (currentSum == targetSum) {
        return true;
    }

    for (int i = 0; i < n; ++i) {
        if (!used[i] && currentSum + arr[i] <= targetSum) {
            used[i] = true;
            subset.Add(to_string(arr[i]));

            if (findSubset(arr, n, used, targetSum, currentSum + arr[i], subset)) {
                return true;
            }

            // Backtrack
            used[i] = false;
            subset.Remove(to_string(arr[i]));
        }
    }

    return false;
}
void divideSet(HashSet& set, int k) {
    int totalSum = set.Sum();
    if (totalSum % k != 0) {
        cout << "Cannot divide the set into " << k << " subsets with equal sum." << endl;
        return;
    }

    int targetSum = totalSum / k;
    int* arr = new int[set.size];
    bool* used = new bool[set.size];
    memset(used, 0, sizeof(bool) * set.size);

    set.ExtractElements(arr);

    for (int i = 0; i < k; ++i) {
        HashSet subset;
        if (!findSubset(arr, set.size, used, targetSum, 0, subset)) {
            cout << "Cannot divide the set into " << k << " subsets with equal sum." << endl;
            delete[] arr;
            delete[] used;

            // Прерываем проверку для большего k
            throw false; // Исключение для быстрого выхода
        }

        cout << "Subset " << i + 1 << ": ";
        subset.Print();
    }

    delete[] arr;
    delete[] used;
}

int main() {
    HashSet set;

    cout << "Enter the number of elements in the set: ";
    int n;
    cin >> n;

    cout << "Enter the elements of the set (space-separated): ";
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        set.Add(to_string(num));
    }

    cout << "Input set: ";
    set.Print();

    try {
        for (int k = 2; k <= n; ++k) {
            cout << "\nTrying to divide into " << k << " subsets...\n";
            divideSet(set, k);
        }
    } catch (bool) {
        cout << "Stopped further checks since dividing into more subsets is impossible." << endl;
    }

    return 0;
}