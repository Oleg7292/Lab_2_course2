#include <iostream>
#include <string>

using namespace std;

// Структура для хранения пары ключ-значение
struct Pair {
    char key;
    char value;
    Pair* next;
};

// Ассоциативный массив (хэш-таблица с цепочками)
struct HashMap {
    static const int SIZE = 128; // Максимальное количество символов (ASCII)
    Pair* table[SIZE];          // Таблица связных списков

    // Инициализация хэш-таблицы
    HashMap() {
        for (int i = 0; i < SIZE; ++i) {
            table[i] = nullptr;
        }
    }

    // Хэш-функция (ASCII код символа)
    int hash(char key) {
        return key % SIZE;
    }

    // Вставка пары ключ-значение
    void insert(char key, char value) {
        int index = hash(key);
        Pair* newPair = new Pair{key, value, table[index]};
        table[index] = newPair;
    }

    // Поиск значения по ключу
    char get(char key) {
        int index = hash(key);
        Pair* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return '\0'; // Если ключ не найден
    }

    // Проверка наличия ключа
    bool contains(char key) {
        int index = hash(key);
        Pair* current = table[index];
        while (current != nullptr) {
            if (current->key == key) {
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

// Функция для проверки изоморфности строк
bool areIsomorphic(const string& a, const string& b) {
    if (a.length() != b.length()) {
        return false; // Если длины строк не равны, они не могут быть изоморфными
    }

    HashMap mapAB; // Отображение символов из строки a в b
    HashMap mapBA; // Обратное отображение символов из строки b в a

    for (size_t i = 0; i < a.length(); ++i) {
        char charA = a[i];
        char charB = b[i];

        // Проверка существующего отображения
        if ((mapAB.contains(charA) && mapAB.get(charA) != charB) ||
            (mapBA.contains(charB) && mapBA.get(charB) != charA)) {
            return false; // Конфликт отображений
        }

        // Установка отображения
        if (!mapAB.contains(charA)) {
            mapAB.insert(charA, charB);
        }
        if (!mapBA.contains(charB)) {
            mapBA.insert(charB, charA);
        }
    }

    return true;
}

// Основная функция
int main() {
    string a, b;

    // Примеры использования
    cout << "Введите первую строку: ";
    cin >> a;
    cout << "Введите вторую строку: ";
    cin >> b;

    if (areIsomorphic(a, b)) {
        cout << "Строки \"" << a << "\" и \"" << b << "\" изоморфны." << endl;
    } else {
        cout << "Строки \"" << a << "\" и \"" << b << "\" не изоморфны." << endl;
    }

    return 0;
}