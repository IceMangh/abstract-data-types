#pragma once
#include "DynamicArray.h"
#include "Sequence.h"
#include "SequenceEnumerator.h"
#include "Exceptions.h"

template <class T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T> items_;

public:
    ArraySequence() : items_(0) {}

    ArraySequence(const T* items, int count) : items_(items, count) {}

    ArraySequence(const DynamicArray<T>& dynamicArray) : items_(dynamicArray) {}

    ArraySequence(const ArraySequence<T>& other) : items_(other.items_) {}

    const T& GetFirst() const override {
        return items_.Get(0);
    }

    const T& GetLast() const override {
        return items_.Get(items_.GetSize() - 1);
    }

    const T& Get(int index) const override {
        return items_.Get(index);
    }

    int GetLength() const override {
        return items_.GetSize();
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || endIndex < 0 || startIndex >= GetLength() || endIndex >= GetLength() || startIndex > endIndex) {
            throw IndexOutOfRange();
        }

        int newLen = endIndex - startIndex + 1;
        DynamicArray<T> temp(newLen);
        for (int i = 0; i < newLen; ++i) {
            temp.Set(i, items_.Get(startIndex + i));
        }

        return new ArraySequence<T>(temp);
    }

    Sequence<T>& Append(const T& item) override {
        int oldSize = items_.GetSize();
        items_.Resize(oldSize + 1);
        items_.Set(oldSize, item);
        return *this;
    }

    Sequence<T>& Prepend(const T& item) override {
        int oldSize = items_.GetSize();
        items_.Resize(oldSize + 1);
        for (int i = oldSize; i > 0; --i) {
            items_.Set(i, items_.Get(i - 1));
        }
        items_.Set(0, item);
        return *this;
    }

    Sequence<T>& InsertAt(const T& item, int index) override {
        if (index < 0 || index > GetLength()) {
            throw IndexOutOfRange();
        }

        int oldSize = items_.GetSize();
        items_.Resize(oldSize + 1);
        for (int i = oldSize; i > index; --i) {
            items_.Set(i, items_.Get(i - 1));
        }
        items_.Set(index, item);
        return *this;
    }

    Sequence<T>* Concat(const Sequence<T>& other) const override {
        ArraySequence<T>* result = new ArraySequence<T>(*this);
        for (int i = 0; i < other.GetLength(); ++i) {
            result->Append(other.Get(i));
        }
        return result;
    }

    Sequence<T>* Clone() const override {
        return new ArraySequence<T>(*this);
    }

    Sequence<T>* CreateEmpty() const override {
        return new ArraySequence<T>();
    }

    static ArraySequence<T> From(const T* items, int count) {
        return ArraySequence<T>(items, count);
    }

    IEnumerator<T>* GetEnumerator() const override {
        return new SequenceEnumerator<T>(*this);
    }
};
