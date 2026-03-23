#pragma once

#include "DynamicArray.h"
#include "Exceptions.h"

template <class T>
class ImmutableArraySequence {
private:
    DynamicArray<T> items_;

public:
    ImmutableArraySequence() : items_(0) {}

    ImmutableArraySequence(const T* items, int count) : items_(items, count) {}

    ImmutableArraySequence(const DynamicArray<T>& dynamicArray) : items_(dynamicArray) {}

    ImmutableArraySequence(const ImmutableArraySequence<T>& other) = default;

    ImmutableArraySequence<T>& operator=(const ImmutableArraySequence<T>& other) = default;

    const T& GetFirst() const {
        return items_.Get(0);
    }

    const T& GetLast() const {
        return items_.Get(items_.GetSize() - 1);
    }

    const T& Get(int index) const {
        return items_.Get(index);
    }

    int GetLength() const {
        return items_.GetSize();
    }

    ImmutableArraySequence<T> GetSubsequence(int startIndex, int endIndex) const {
        if (startIndex < 0 || endIndex < 0 || startIndex >= GetLength() || endIndex >= GetLength() || startIndex > endIndex) {
            throw IndexOutOfRange();
        }

        const int newLength = endIndex - startIndex + 1;
        DynamicArray<T> temp(newLength);
        for (int i = 0; i < newLength; ++i) {
            temp.Set(i, items_.Get(startIndex + i));
        }
        return ImmutableArraySequence<T>(temp);
    }

    ImmutableArraySequence<T> Append(const T& item) const {
        DynamicArray<T> temp(items_);
        const int oldSize = temp.GetSize();
        temp.Resize(oldSize + 1);
        temp.Set(oldSize, item);
        return ImmutableArraySequence<T>(temp);
    }

    ImmutableArraySequence<T> Prepend(const T& item) const {
        DynamicArray<T> temp(items_);
        const int oldSize = temp.GetSize();
        temp.Resize(oldSize + 1);
        for (int i = oldSize; i > 0; --i) {
            temp.Set(i, temp.Get(i - 1));
        }
        temp.Set(0, item);
        return ImmutableArraySequence<T>(temp);
    }

    ImmutableArraySequence<T> InsertAt(const T& item, int index) const {
        if (index < 0 || index > GetLength()) {
            throw IndexOutOfRange();
        }

        DynamicArray<T> temp(items_);
        const int oldSize = temp.GetSize();
        temp.Resize(oldSize + 1);
        for (int i = oldSize; i > index; --i) {
            temp.Set(i, temp.Get(i - 1));
        }
        temp.Set(index, item);
        return ImmutableArraySequence<T>(temp);
    }

    template <class TOtherSequence>
    ImmutableArraySequence<T> Concat(const TOtherSequence& other) const {
        DynamicArray<T> temp(GetLength() + other.GetLength());
        for (int i = 0; i < GetLength(); ++i) {
            temp.Set(i, Get(i));
        }
        for (int i = 0; i < other.GetLength(); ++i) {
            temp.Set(GetLength() + i, other.Get(i));
        }
        return ImmutableArraySequence<T>(temp);
    }

    template <class Mapper>
    ImmutableArraySequence<T> Map(Mapper mapper) const {
        DynamicArray<T> temp(GetLength());
        for (int i = 0; i < GetLength(); ++i) {
            temp.Set(i, mapper(Get(i)));
        }
        return ImmutableArraySequence<T>(temp);
    }

    template <class Reducer>
    T Reduce(Reducer reducer, T start) const {
        T result = start;
        for (int i = 0; i < GetLength(); ++i) {
            result = reducer(result, Get(i));
        }
        return result;
    }

    bool operator==(const ImmutableArraySequence<T>& other) const {
        if (GetLength() != other.GetLength()) {
            return false;
        }

        for (int i = 0; i < GetLength(); ++i) {
            if (Get(i) != other.Get(i)) {
                return false;
            }
        }

        return true;
    }

    bool operator!=(const ImmutableArraySequence<T>& other) const {
        return !(*this == other);
    }

    ImmutableArraySequence<T> operator+(const ImmutableArraySequence<T>& other) const {
        return Concat(other);
    }

    static ImmutableArraySequence<T> From(const T* items, int count) {
        return ImmutableArraySequence<T>(items, count);
    }
};
