#pragma once

#include "ArraySequenceBase.h"

template <class T>
class ArraySequence : public ArraySequenceBase<T> {
protected:
    ArraySequenceBase<T>* Instance() override {
        return this;
    }

public:
    ArraySequence() : ArraySequenceBase<T>() {}

    ArraySequence(const T* items, int count) : ArraySequenceBase<T>(items, count) {}

    ArraySequence(const DynamicArray<T>& dynamicArray) : ArraySequenceBase<T>(dynamicArray) {}

    ArraySequence(const ArraySequence<T>& other) : ArraySequenceBase<T>(other) {}

    Sequence<T>* Clone() const override {
        return new ArraySequence<T>(*this);
    }

    Sequence<T>* CreateEmpty() const override {
        return new ArraySequence<T>();
    }

    static ArraySequence<T> From(const T* items, int count) {
        return ArraySequence<T>(items, count);
    }
};
