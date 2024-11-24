#include "Stack.h"
#include <iostream>
#include <stdexcept>

void IntStack::initialize() {
    top = nullptr;
}

void IntStack::push(int value) {
    IntStackNode* newNode = new IntStackNode;
    newNode->data = value;
    newNode->next = top;
    top = newNode;
}

void IntStack::pop() {
    if (!top) {
        std::cerr << "Stack underflow\n";
        return;
    }
    IntStackNode* toDelete = top;
    top = top->next;
    delete toDelete;
}

int IntStack::top_elem() const {
    if (!top) throw std::out_of_range("Stack is empty");
    return top->data;
}

bool IntStack::isEmpty() const {
    return top == nullptr;
}

void IntStack::cleanup() {
    while (top) {
        IntStackNode* toDelete = top;
        top = top->next;
        delete toDelete;
    }
}

void CharStack::initialize() {
    top = nullptr;
}

void CharStack::push(char value) {
    CharStackNode* newNode = new CharStackNode;
    newNode->data = value;
    newNode->next = top;
    top = newNode;
}

void CharStack::pop() {
    if (!top) {
        std::cerr << "Stack underflow\n";
        return;
    }
    CharStackNode* toDelete = top;
    top = top->next;
    delete toDelete;
}

char CharStack::top_elem() const {
    if (!top) throw std::out_of_range("Stack is empty");
    return top->data;
}

bool CharStack::isEmpty() const {
    return top == nullptr;
}

void CharStack::cleanup() {
    while (top) {
        CharStackNode* toDelete = top;
        top = top->next;
        delete toDelete;
    }
}