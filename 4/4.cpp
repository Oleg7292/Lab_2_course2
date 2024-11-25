#include <iostream>
#include "Array.h"

using namespace std;

// Функция для генерации и вывода всех комбинаций элементов массива
void combination(const Array& arr) {
    if (arr.length > 32) return; // Ограничение на размер

    cout << '[';

    // Цикл по всем возможным подмножествам (2^length)
    for (size_t i = 0; i < (1 << arr.length); i++) { // 1 << length = 2^length
        cout << '{';

        bool first = true; // Флаг для отслеживания первой итерации
        for (size_t l = 0; l < arr.length; l++) {
            if ((i >> l) & 1) { // Проверка, установлен ли l-й бит в числе i
                if (!first) cout << ',';
                cout << arr.get(l);
                first = false;
            }
        }

        cout << '}';
        if (i < (1 << arr.length) - 1) cout << ',';
    }

    cout << ']';
}

int main() {
    Array arr;
    size_t size_x;

    cout << "Введите количество элементов в массиве: ";
    cin >> size_x;

    if (size_x <= 0 || size_x > 32) {
        cout << "Недопустимый размер массива (от 1 до 32)." << endl;
        return 1;
    }

    arr.initialize(size_x);

    cout << "Введите элементы массива: ";
    for (size_t i = 0; i < size_x; i++) {
        string value;
        cin >> value;
        arr.add(value);
    }

    combination(arr);

    arr.cleanup(); // Освобождение памяти
    return 0;
}