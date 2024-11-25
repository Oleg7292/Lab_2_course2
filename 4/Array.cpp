#include "Array.h"
#include <iostream>
#include <stdexcept>

using namespace std;

void Array::initialize(size_t initialCapacity) {
    capacity = initialCapacity;
    length = 0;
    data = new string[capacity];  // Выделяем память под строки
}

void Array::resize() {
    capacity *= 2;
    string* newData = new string[capacity];
    for (size_t i = 0; i < length; ++i) {
        newData[i] = data[i];
    }
    delete[] data;
    data = newData;
}

void Array::add(const string& value) {
    if (length >= capacity) {
        resize();
    }
    data[length++] = value;
}

string Array::get(size_t index) const {
    if (index >= length) {
        throw out_of_range("Index out of range");
    }
    return data[index];
}

void Array::removeAt(size_t index) {
    if (index >= length) {
        throw out_of_range("Index out of range");
    }
    for (size_t i = index; i < length - 1; ++i) {
        data[i] = data[i + 1];
    }
    length--;
}

void Array::insertAt(size_t index, const string& value) {
    if (index > length) {
        throw out_of_range("Index out of range");
    }
    if (length >= capacity) {
        resize();
    }
    for (size_t i = length; i > index; --i) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    length++;
}

void Array::setAt(size_t index, const string& value) {
    if (index >= length) {
        throw out_of_range("Index out of range");
    }
    data[index] = value;
}

void Array::cleanup() {
    delete[] data;
}