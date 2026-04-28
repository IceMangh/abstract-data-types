#pragma once

#include <memory>
#include "DynamicArray.h"
#include "Exceptions.h"
#include "Sequence.h"

template <class T>
class ArraySequenceBase : public Sequence<T> {
protected:
    DynamicArray<T> data;

    virtual ArraySequenceBase<T>* Instance() = 0;

    void AppendInPlace(const T& item) override {
        AppendInternal(item);
    }

    Sequence<T>* AppendInternal(const T& item) {
        const int OldLength = data.GetLength();
        int NewLength = OldLength;
        ++NewLength;

        data.Resize(NewLength);
        data.Set(OldLength, item);
        return this;
    }

    Sequence<T>* PrependInternal(const T& item) {
        const int OldLength = data.GetLength();
        int NewLength = OldLength;
        ++NewLength;

        data.Resize(NewLength);

        for (int i = OldLength; i > 0; --i) {
            data.Set(i, data.Get(i - 1));
        }
        data.Set(0, item);
        return this;
    }

    Sequence<T>* InsertAtInternal(const T& item, int index) {
        const int OldLength = data.GetLength();
        if (index < 0 || index > OldLength) {
            throw IndexOutOfRange();
        }

        if (index == OldLength) {
            return AppendInternal(item);
        }

        int NewLength = OldLength;
        ++NewLength;

        data.Resize(NewLength);
        for (int i = OldLength; i > index; --i) {
            data.Set(i, data.Get(i - 1));
        }
        data.Set(index, item);
        return this;
    }

public:
    ArraySequenceBase() : data(0) {}

    ArraySequenceBase(const T* items, int count) : data(items, count) {}

    ArraySequenceBase(const DynamicArray<T>& dynamicArray) : data(dynamicArray) {}

    ArraySequenceBase(const ArraySequenceBase<T>& other) : data(other.data) {}

    const T& GetFirst() const override {
        if (data.GetLength() == 0) {
            throw IndexOutOfRange();
        }
        return data.Get(0);
    }

    const T& GetLast() const override {
        if (data.GetLength() == 0) {
            throw IndexOutOfRange();
        }
        return data.Get(data.GetLength() - 1);
    }

    const T& Get(int index) const override {
        return data.Get(index);
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || endIndex < 0 || startIndex > endIndex || endIndex >= data.GetLength()) {
            throw IndexOutOfRange();
        }

        std::unique_ptr<Sequence<T>> result(this->CreateEmpty());
        for (int i = startIndex; i <= endIndex; ++i) {
            this->AppendToResult(result, data.Get(i));
        }

        return result.release();
    }

    int GetLength() const override {
        return data.GetLength();
    }

    IEnumerator<T>* GetEnumerator() const override {
        return data.GetEnumerator();
    }

    Sequence<T>* Append(const T& item) override {
        ArraySequenceBase<T>* target = Instance();
        std::unique_ptr<ArraySequenceBase<T>> targetGuard((target == this) ? nullptr : target);

        Sequence<T>* result = target->AppendInternal(item);
        if (result == target) {
            targetGuard.release();
        }
        return result;
    }

    Sequence<T>* Prepend(const T& item) override {
        ArraySequenceBase<T>* target = Instance();
        std::unique_ptr<ArraySequenceBase<T>> targetGuard((target == this) ? nullptr : target);

        Sequence<T>* result = target->PrependInternal(item);
        if (result == target) {
            targetGuard.release();
        }
        return result;
    }

    Sequence<T>* InsertAt(const T& item, int index) override {
        ArraySequenceBase<T>* target = Instance();
        std::unique_ptr<ArraySequenceBase<T>> targetGuard((target == this) ? nullptr : target);

        Sequence<T>* result = target->InsertAtInternal(item, index);
        if (result == target) {
            targetGuard.release();
        }
        return result;
    }

    Sequence<T>* Concat(const Sequence<T>& list) const override {
        std::unique_ptr<Sequence<T>> result(this->Clone());
        std::unique_ptr<IEnumerator<T>> enumerator(list.GetEnumerator());

        while (enumerator->MoveNext()) {
            this->AppendToResult(result, enumerator->Current());
        }

        return result.release();
    }
};
