#include "Stack.h" 
#include <iostream> 
#include <stdexcept>
#include <cctype> 

using namespace std;

// Функция для применения математической операции между двумя числами.
int applyOperation(int a, int b, char op) {
    switch(op) {
        case '+': return a + b; 
        case '-': return a - b; 
        case '*': return a * b; 
        case '/': 
            if (b == 0) throw invalid_argument("Division by zero"); 
            return a / b; 
        default: throw invalid_argument("Unknown operator"); // Если оператор неизвестен, выбрасываем исключение
    }
}

// Функция для определения приоритета операций.
// Чем выше возвращаемое значение, тем выше приоритет.
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2; 
    return 0; 
}

// Функция для вычисления математического выражения.
int evaluateExpression(const string& expression) {
    IntStack values; 
    CharStack operators; 
    values.initialize(); 
    operators.initialize(); 
    
    int i = 0;
    while (i < expression.size()) {
        // Пропускаем пробелы
        if (isspace(expression[i])) {
            i++;
            continue;
        }

        // Если текущий символ - число или унарный минус перед числом
        if (isdigit(expression[i]) || (expression[i] == '-' && (i == 0 || expression[i - 1] == '('))) {
            int value = 0, sign = 1; // Переменная для числа и его знака
            if (expression[i] == '-') {
                sign = -1; // Устанавливаем отрицательный знак
                i++;
            }
            // Чтение числа из строки
            while (i < expression.size() && isdigit(expression[i])) {
                value = value * 10 + (expression[i] - '0');
                i++;
            }
            values.push(sign * value); // Добавляем число в стек
            continue;
        }
        
        // Если текущий символ - открывающая скобка
        if (expression[i] == '(') {
            operators.push(expression[i]); // Добавляем её в стек операторов
        }
        // Если текущий символ - закрывающая скобка
        else if (expression[i] == ')') {
            // Выполняем операции до тех пор, пока не найдём открывающую скобку
            while (!operators.isEmpty() && operators.top_elem() != '(') {
                int b = values.top_elem(); values.pop(); 
                int a = values.top_elem(); values.pop(); 
                char op = operators.top_elem(); operators.pop(); // Получаем оператор
                values.push(applyOperation(a, b, op)); // Выполняем операцию и сохраняем результат
            }
            operators.pop(); // Удаляем открывающую скобку из стека операторов
        }
        // Если текущий символ - оператор (+, -, *, /)
        else {
            // Выполняем операции с более высоким или равным приоритетом
            while (!operators.isEmpty() && precedence(operators.top_elem()) >= precedence(expression[i])) {
                int b = values.top_elem(); values.pop(); 
                int a = values.top_elem(); values.pop(); 
                char op = operators.top_elem(); operators.pop();
                values.push(applyOperation(a, b, op)); 
            }
            operators.push(expression[i]); // Добавляем текущий оператор в стек
        }
        i++;
    }
    // Выполняем оставшиеся операции в стеке
    while (!operators.isEmpty()) {
        int b = values.top_elem(); values.pop(); 
        int a = values.top_elem(); values.pop(); 
        char op = operators.top_elem(); operators.pop(); 
        values.push(applyOperation(a, b, op)); 
    }

    // Результат находится на вершине стека значений
    int result = values.top_elem();
    values.cleanup(); 
    operators.cleanup(); 
    return result;
}

int main() {
    string expression; // Строка для ввода выражения
    cout << "Введите выражение: ";
    getline(cin, expression); // Читаем выражение с пробелами
    
    try {
        // Вычисляем результат выражения
        int result = evaluateExpression(expression);
        cout << "Результат: " << result << endl; // Вывод результата
    } catch (const exception& e) {
        // Обрабатываем ошибки (например, деление на ноль или некорректный ввод)
        cout << "Ошибка: " << e.what() << endl;
    }
    
    return 0;
}