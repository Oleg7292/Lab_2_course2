#ifndef ARRAY_H
#define ARRAY_H

#include <string>
#include <cstddef>  // Для size_t

using namespace std;

struct Array {
    string* data;
    size_t capacity;
    size_t length;

    void initialize(size_t initialCapacity = 2);
    void resize();
    void add(const string& value);
    string get(size_t index) const;
    void removeAt(size_t index);
    void insertAt(size_t index, const string& value);
    void setAt(size_t index, const string& value);
    void cleanup();
};

#endif
