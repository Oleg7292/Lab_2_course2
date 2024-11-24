#ifndef STACK_H
#define STACK_H

struct IntStackNode {
    int data;
    IntStackNode* next;
};

struct CharStackNode {
    char data;
    CharStackNode* next;
};

struct IntStack {
    IntStackNode* top;
    void initialize();
    void push(int value);
    void pop();
    int top_elem() const;
    bool isEmpty() const;
    void cleanup();
};

struct CharStack {
    CharStackNode* top;
    void initialize();
    void push(char value);
    void pop();
    char top_elem() const;
    bool isEmpty() const;
    void cleanup();
};

#endif