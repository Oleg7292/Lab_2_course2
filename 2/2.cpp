#include <iostream>
#include <string>
#include <cstring> // Для memset
#include <cstdlib> // Для malloc, free
#include <fstream> // Для работы с файлами

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

    // Конструктор
    HashSet(size_t initialCapacity = 1024)
        : capacity(initialCapacity), size(0) {
        table = (Node**)malloc(sizeof(Node*) * capacity);
        memset(table, 0, sizeof(Node*) * capacity);
    }

    // Деструктор
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

    // Хеш-функция
    size_t hash(const string& key) const {
        size_t hashValue = 0;
        for (char ch : key) {
            hashValue = (hashValue * 31 + ch) % capacity;
        }
        return hashValue;
    }

    // Добавление элемента
    void Add(const string& value) {
        size_t index = hash(value);

        Node* current = table[index];
        while (current) {
            if (current->value == value) {
                // Элемент уже существует
                return;
            }
            current = current->next;
        }

        // Добавляем новый элемент
        Node* newNode = new Node(value);
        newNode->next = table[index];
        table[index] = newNode;
        ++size;

        cout << "Added: " << value << endl;
    }

    // Удаление элемента
    bool Remove(const string& value) {
        size_t index = hash(value);
        Node* current = table[index];
        Node* prev = nullptr;

        while (current) {
            if (current->value == value) {
                // Удаляем элемент
                if (prev) {
                    prev->next = current->next;
                } else {
                    table[index] = current->next;
                }
                delete current;
                --size;

                cout << "Removed: " << value << endl;
                return true;
            }
            prev = current;
            current = current->next;
        }
        cout << "Element not found: " << value << endl;
        return false;
    }

    // Проверка наличия элемента
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

    // Вывод всех элементов множества
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

    // Запись множества в файл
    void WriteToFile(const string& filePath) const {
        ofstream file(filePath);
        if (!file) {
            cerr << "Error: Unable to open file for writing: " << filePath << endl;
            return;
        }

        for (size_t i = 0; i < capacity; ++i) {
            Node* current = table[i];
            while (current) {
                file << current->value << endl;
                current = current->next;
            }
        }
        file.close();
    }
};

void showUsage() {
    cout << "Usage: ./program --file <file_path> --query <command> [<parameter>]\n";
    cout << "Commands:\n";
    cout << "  ADD <element>    - Add element to the set\n";
    cout << "  DELETE <element> - Remove element from the set\n";
    cout << "  EXISTS <element> - Check if element exists in the set\n";
    cout << "  PRINT            - Print all elements in the set\n";
}

int main(int argc, char* argv[]) {
    if (argc < 5) {
        cerr << "Invalid arguments.\n";
        showUsage();
        return 1;
    }

    string fileFlag = argv[1];
    string filePath = argv[2];
    string queryFlag = argv[3];
    string command = argv[4];

    if (fileFlag != "--file" || queryFlag != "--query") {
        cerr << "Invalid flags.\n";
        showUsage();
        return 1;
    }

    HashSet mySet;

    // Чтение данных из файла
    ifstream file(filePath);
    if (!file) {
        cerr << "Error: Unable to open file " << filePath << ".\n";
        return 1;
    }

    string element;
    while (file >> element) {
        mySet.Add(element);
    }
    file.close();

    // Обработка команды
    if (command == "ADD") {
        if (argc != 6) {
            cerr << "ADD command requires an element parameter.\n";
            return 1;
        }
        string newElement = argv[5];
        mySet.Add(newElement);
        mySet.WriteToFile(filePath); // Записываем изменения в файл
    } else if (command == "DELETE") {
        if (argc != 6) {
            cerr << "DELETE command requires an element parameter.\n";
            return 1;
        }
        string deleteElement = argv[5];
        if (mySet.Remove(deleteElement)) {
            mySet.WriteToFile(filePath); // Записываем изменения в файл
        }
    } else if (command == "EXISTS") {
        if (argc != 6) {
            cerr << "EXISTS command requires an element parameter.\n";
            return 1;
        }
        string checkElement = argv[5];
        if (mySet.Contains(checkElement)) {
            cout << "Element '" << checkElement << "' exists in the set.\n";
        } else {
            cout << "Element '" << checkElement << "' does not exist in the set.\n";
        }
    } else if (command == "PRINT") {
        cout << "Set elements:\n";
        mySet.Print();
    } else {
        cerr << "Unknown command.\n";
        showUsage();
        return 1;
    }

    return 0;
}