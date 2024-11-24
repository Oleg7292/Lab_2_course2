#include <iostream>
#include <string>
#include <limits> // Для numeric_limits

using namespace std;

template <typename T>
struct Deque
{
    struct Node
    {
        T data;
        Node* prev = nullptr;
        Node* next = nullptr;

        // Конструктор узла
        Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head = nullptr;
    Node* tail = nullptr;

    // Конструктор дека
    Deque(const T& value)
        : head(new Node(value)),
          tail(head)
    {}

    // Метод добавления элемента
    void Add(const T& value)
    {
        Node* newQueueNode = new Node(value);
        newQueueNode->prev = tail;

        if (tail)
        {
            tail->next = newQueueNode;
        }
        else
        {
            head = newQueueNode;
        }

        tail = newQueueNode;
    }

    // Метод удаления элемента
    void Delete()
    {
        if (!head)
        {
            cerr << "Queue underflow\n";
            return;
        }

        Node* toDelete = head;
        head = head->next;

        if (head)
        {
            head->prev = nullptr;
        }
        else
        {
            tail = nullptr;
        }

        delete toDelete;
    }

    // Метод вывода элементов
    void Out()
    {
        if (!head)
        {
            cout << "Deque is empty.\n";
            return;
        }

        Node* i = head;

        while (i)
        {
            cout << i->data << ' ';
            i = i->next;
        }

        cout << endl;
    }

    // Метод поиска элемента
    Node* Find(const T& value)
    {
        Node* i = head;

        while (i)
        {
            if (i->data == value)
                return i;
            i = i->next;
        }

        return nullptr;
    }
};

int main()
{
    string command;
    string param;

    Deque<string> s("");

    while (true)
    {
        cout << "Write one of these commands (SETADD, SETDEL, SET_AT, PRINT) and param (if needed), or type EXIT to quit:\n";
        cin >> command;

        // Проверяем корректность команды
        if (command == "SETADD")
        {
            if (!(cin >> param))  // Проверяем ввод параметра
            {
                cerr << "Invalid input. Please enter a valid number.\n";
                cin.clear(); // Сбрасываем флаг ошибки
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Пропускаем остаток строки
                continue;
            }
            s.Add(param);
        }
        else if (command == "SETDEL")
        {
            s.Delete();
        }
        else if (command == "SET_AT")
        {
            if (!(cin >> param))  // Проверяем ввод параметра
            {
                cerr << "Invalid input. Please enter a valid number.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cout << (s.Find(param) ? "Found" : "Not Found") << endl;
        }
        else if (command == "PRINT")
        {
            s.Out();
        }
        else if (command == "EXIT")
        {
            cout << "Exiting program.\n";
            break;
        }
        else
        {
            cout << "Unknown command. Try again.\n";
            cin.clear(); // Сбрасываем флаг ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Пропускаем остаток строки
        }
    }

    return 0;
}