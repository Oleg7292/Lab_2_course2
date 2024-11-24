#include <iostream>
#include <iomanip> // Для работы с отступами

struct Node {
    int value;
    Node* left;
    Node* right;
};

// Функция для создания нового узла
Node* createNode(int value) {
    Node* newNode = new Node;
    newNode->value = value;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

// Вставка элемента в бинарное дерево поиска
Node* insert(Node* root, int value) {
    if (root == nullptr) {
        return createNode(value);
    }
    if (value < root->value) {
        root->left = insert(root->left, value);
    } else if (value > root->value) {
        root->right = insert(root->right, value);
    }
    return root;
}

// Поиск минимального узла в правом поддереве
Node* findMin(Node* root) {
    while (root->left != nullptr) {
        root = root->left;
    }
    return root;
}

// Удаление узла с заданным значением
Node* deleteNode(Node* root, int value) {
    if (root == nullptr) {
        return root;
    }
    if (value < root->value) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->value) {
        root->right = deleteNode(root->right, value);
    } else {
        // Узел найден
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        // Узел с двумя дочерними элементами
        Node* temp = findMin(root->right);
        root->value = temp->value;
        root->right = deleteNode(root->right, temp->value);
    }
    return root;
}

// Обход дерева (симметричный, для проверки)
void inOrderTraversal(Node* root) {
    if (root != nullptr) {
        inOrderTraversal(root->left);
        std::cout << root->value << " ";
        inOrderTraversal(root->right);
    }
}

// Функция для отображения структуры дерева
void printTree(Node* root, int space = 0, int indent = 4) {
    if (root == nullptr) {
        return;
    }

    // Увеличиваем отступ
    space += indent;

    // Сначала печатаем правое поддерево
    printTree(root->right, space);

    // Печатаем текущий узел с отступами
    std::cout << std::endl;
    std::cout << std::setw(space) << root->value << std::endl;

    // Затем печатаем левое поддерево
    printTree(root->left, space);
}

// Основная функция
int main() {
    Node* root = nullptr;

    // Пример вставки элементов
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 70);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 60);
    root = insert(root, 80);

    std::cout << "Дерево до удаления:";
    printTree(root);

    // Удаление узла
    int valueToDelete = 70;
    root = deleteNode(root, valueToDelete);

    std::cout << "\nДерево после удаления:";
    printTree(root);

    return 0;
}