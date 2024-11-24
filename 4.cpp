#include <iostream>
using namespace std; 

// Функция для генерации и вывода всех комбинаций элементов массива
void combination(int* arr, int size)
{
    if (size > 32) return;

    cout << '[';

    // Цикл по всем возможным подмножествам (2^size)
    for (int i = 0; i < (1 << size); i++) { // 1 << size = 2^size, перебираем все подмножества
        cout << '{';

        bool first = true; // Флаг для отслеживания первой итерации
        for (int l = 0; l < size; l++) {
            if ((i >> l) & 1) { // Проверка, установлен ли l-й бит в числе i
                if (!first) cout << ',';
                cout << arr[l]; 
                first = false;
            }
        }

        cout << '}';
        if (i < (1 << size) - 1) cout << ','; 
    }

    cout << ']'; 
}

int main()
{
    int size_x; // Размер массива
    cout << "Введите количество элементов в массиве: ";
    cin >> size_x;

    if (size_x <= 0 || size_x > 32) {
        cout << "Недопустимый размер массива (от 1 до 32)." << endl;
        return 1;
    }

    int* x = new int[size_x]; // Динамическое выделение памяти для массива
    cout << "Введите элементы массива: ";
    for (int i = 0; i < size_x; i++) {
        cin >> x[i];
    }

    combination(x, size_x);

    delete[] x; 
    return 0;
}