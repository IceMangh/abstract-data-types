#pragma once
#include <stdexcept>
#include "Exceptions.h"

template <class T>
class DynamicArray {
private:
    T* data;
    int size;
    int capacity;

    void Reserve(int newCapacity) {
        if (newCapacity <= capacity) {
            return;
        }

        T* newData = new T[newCapacity]{};
        for (int i = 0; i < size; ++i) {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    void CheckIndex(int index) const {
        if (index < 0 || index >= size) {
            throw IndexOutOfRange();
        }
    }

public:
    DynamicArray() : data(nullptr), size(0), capacity(0) {}

    explicit DynamicArray(int size) : data(nullptr), size(size), capacity(size) {
        if (size < 0) {
            throw std::invalid_argument("Negative size");
        }
        if (this->size > 0) {
            data = new T[this->size]{};
        }
    }

    DynamicArray(const T* items, int count) : data(nullptr), size(count), capacity(count) {
        if (count < 0) {
            throw std::invalid_argument("Negative size");
        }
        if (size > 0) {
            data = new T[size];
            for (int i = 0; i < size; ++i) {
                data[i] = items[i];
            }
        }
    }

    DynamicArray(const DynamicArray<T>& other) : data(nullptr), size(other.size), capacity(other.capacity) {
        if (size > 0) {
            data = new T[capacity]{};
            for (int i = 0; i < size; ++i) {
                data[i] = other.data[i];
            }
        }
    }

    DynamicArray<T>& operator=(const DynamicArray<T>& other) {
        if (this != &other) {
            T* newData = nullptr;
            if (other.capacity > 0) {
                newData = new T[other.capacity]{};
                for (int i = 0; i < other.size; ++i) {
                    newData[i] = other.data[i];
                }
            }
            delete[] data;
            data = newData;
            size = other.size;
            capacity = other.capacity;
        }
        return *this;
    }

    ~DynamicArray() {
        delete[] data;
    }

    const T& Get(int index) const {
        CheckIndex(index);
        return data[index];
    }


    int GetSize() const {
        return size;
    }

    void Set(int index, const T& value) {
        CheckIndex(index);
        data[index] = value;
    }

    void Resize(int newSize) {
        if (newSize < 0) {
            throw std::invalid_argument("Negative size");
        }

        if (newSize == size) {
            return;
        }

        if (newSize > size) {
            if (newSize > capacity) {
                int newCapacity = (capacity == 0) ? 1 : capacity;
                while (newCapacity < newSize) {
                    newCapacity *= 2;
                }
                Reserve(newCapacity);
            }

            for (int i = size; i < newSize; ++i) {
                data[i] = T{};
            }
            size = newSize;
            return;
        }

        T* newData = nullptr;
        if (newSize > 0) {
            newData = new T[newSize]{};
            for (int i = 0; i < newSize; ++i) {
                newData[i] = data[i];
            }
        }

        delete[] data;
        data = newData;
        size = newSize;
        capacity = newSize;
    }

    T& operator[](int index) {
        CheckIndex(index);
        return data[index];
    }

};
