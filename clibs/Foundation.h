#ifndef FOUNDATION_H
#define FOUNDATION_H

#include "fromia.h"
#include <stdarg.h>
#include <stdint.h>

namespace Fromia {

    // Dynamic Array
    template <typename T>
    struct Array {
        T* data;
        size_t size;
        size_t capacity;

        Array() : data(NULL), size(0), capacity(0) {}
        void add(T element) {
            if (size >= capacity) {
                capacity = (capacity == 0) ? 1 : capacity * 2;
                data = (T*)realloc(data, capacity * sizeof(T));
            }
            data[size++] = element;
        }
        T get(size_t index) {
            if (index >= size) {
                error("Index out of bounds");
                return T();
            }
            return data[index];
        }
    };

    // String Utilities
    void concat(char* dest, const char* src1, const char* src2) {
        sprintf(dest, "%s%s", src1, src2);
    }
}

#endif // FOUNDATION_H
