#include <iostream>
#include <cstring>

using namespace std;

// Функция для печати всех подмножеств
void printSubsets(int** subsets, int* subsetSizes, int k) {
    for (int i = 0; i < k; ++i) {
        cout << "{ ";
        for (int j = 0; j < subsetSizes[i]; ++j) {
            cout << subsets[i][j] << " ";
        }
        cout << "}\n";
    }
}

// Рекурсивная функция для разбиения множества на подмножества
bool canPartition(int* arr, int n, int k, int** subsets, int* subsetSizes, bool* used, int subsetSum, int targetSum, int index) {
    // Если осталось одно подмножество, заполняем его оставшимися элементами
    if (k == 1) {
        int subsetIndex = 0;
        for (int i = 0; i < n; ++i) {
            if (!used[i]) {
                subsets[0][subsetIndex++] = arr[i];
            }
        }
        subsetSizes[0] = subsetIndex;
        return true;
    }

    // Если текущее подмножество достигло целевой суммы, начинаем формировать следующее
    if (subsetSum == targetSum) {
        return canPartition(arr, n, k - 1, subsets + 1, subsetSizes + 1, used, 0, targetSum, 0);
    }

    // Перебираем элементы множества, чтобы сформировать текущее подмножество
    for (int i = index; i < n; ++i) {
        if (!used[i] && subsetSum + arr[i] <= targetSum) {
            // Отмечаем текущий элемент как использованный
            used[i] = true;
            subsets[0][subsetSizes[0]++] = arr[i];

            // Рекурсивно продолжаем формировать подмножество
            if (canPartition(arr, n, k, subsets, subsetSizes, used, subsetSum + arr[i], targetSum, i + 1)) {
                return true;
            }

            // Откатываем изменения, если текущий путь не привел к решению
            used[i] = false;
            --subsetSizes[0];
        }
    }

    // Если не удалось сформировать подмножество, возвращаем false
    return false;
}

// Функция для поиска всех возможных разбиений множества
void findAllPartitions(int* arr, int n) {
    int totalSum = 0;

    // Считаем общую сумму элементов множества
    for (int i = 0; i < n; ++i) {
        totalSum += arr[i];
    }

    bool found = false;

    // Перебираем все возможные количества подмножеств (от 1 до n)
    for (int k = 1; k <= n; ++k) {
        // Если сумма множества не делится на k, пропускаем
        if (totalSum % k != 0) continue;

        int targetSum = totalSum / k; // Целевая сумма для каждого подмножества

        // Динамическое выделение памяти для подмножеств и вспомогательных данных
        int** subsets = new int*[k];
        int* subsetSizes = new int[k];
        bool* used = new bool[n];

        for (int i = 0; i < k; ++i) {
            subsets[i] = new int[n];
            subsetSizes[i] = 0;
        }
        memset(used, false, n * sizeof(bool));

        // Проверяем, можно ли разбить множество на k подмножеств
        if (canPartition(arr, n, k, subsets, subsetSizes, used, 0, targetSum, 0)) {
            cout << "Разбиение множества на " << k << " подмножества с суммой " << targetSum << ":\n";
            printSubsets(subsets, subsetSizes, k);
            found = true;
        }

        // Освобождаем выделенную память
        for (int i = 0; i < k; ++i) {
            delete[] subsets[i];
        }
        delete[] subsets;
        delete[] subsetSizes;
        delete[] used;
    }

    // Если разбиение не найдено, выводим сообщение
    if (!found) {
        cout << "Множество нельзя разбить на подмножества с равной суммой.\n";
    }
}

int main() {
    int n;

    // Ввод количества элементов множества
    cout << "Введите количество элементов множества: ";
    cin >> n;

    // Динамическое выделение памяти для множества
    int* arr = new int[n];

    // Ввод элементов множества
    cout << "Введите элементы множества:\n";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    // Вывод введенного множества
    cout << "Множество: { ";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << "}\n";
    // Поиск всех возможных разбиений множества
    findAllPartitions(arr, n);

    // Освобождение памяти
    delete[] arr;
    return 0;
}