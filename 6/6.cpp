#include <iostream>
#include <string>
#include "HashTable.h"

using namespace std;

// Функция для проверки изоморфности строк
bool areIsomorphic(const string& a, const string& b) {
    if (a.length() != b.length()) {
        return false; // Если длины строк не равны, они не могут быть изоморфными
    }

    HashTable mapAB; // Отображение символов из строки a в b
    HashTable mapBA; // Обратное отображение символов из строки b в a

    for (size_t i = 0; i < a.length(); ++i) {
    string charA(1, a[i]);
    string charB(1, b[i]);

    // Проверка существующего отображения
    try {
        string mappedB = mapAB.get(charA);
        if (mappedB != charB) {
            return false; // Конфликт отображений: charA -> charB
        }
    } catch (const out_of_range&) {
        // Добавляем новое отображение
        mapAB.insert(charA, charB);
    }

    try {
        string mappedA = mapBA.get(charB);
        if (mappedA != charA) {
            return false; // Конфликт отображений: charB -> charA
        }
    } catch (const out_of_range&) {
        // Добавляем обратное отображение
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