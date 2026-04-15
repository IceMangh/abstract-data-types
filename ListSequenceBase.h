#pragma once

#include <memory>
#include "LinkedList.h"
#include "Sequence.h"
#include "SequenceEnumerator.h"

template <class T>
class ListSequenceBase : public Sequence<T> {
protected:
    LinkedList<T> items;

    virtual ListSequenceBase<T>* Instance() = 0;

    void AppendInPlace(const T& item) override {
        AppendInternal(item);
    }

    Sequence<T>* AppendInternal(const T& item) {
        items.Append(item);
        return this;
    }

    Sequence<T>* PrependInternal(const T& item) {
        items.Prepend(item);
        return this;
    }

    Sequence<T>* InsertAtInternal(const T& item, int index) {
        items.InsertAt(item, index);
        return this;
    }

public:
    ListSequenceBase() : items() {}

    ListSequenceBase(const T* items, int count) : items(items, count) {}

    ListSequenceBase(const LinkedList<T>& list) : items(list) {}

    ListSequenceBase(const ListSequenceBase<T>& other) : items(other.items) {}

    const T& GetFirst() const override {
        return items.GetFirst();
    }

    const T& GetLast() const override {
        return items.GetLast();
    }

    const T& Get(int index) const override {
        return items.Get(index);
    }

    int GetLength() const override {
        return items.GetLength();
    }

    Sequence<T>* GetSubsequence(int startIndex, int endIndex) const override {
        if (startIndex < 0 || endIndex < 0 || startIndex > endIndex || endIndex >= items.GetLength()) {
            throw IndexOutOfRange();
        }

        std::unique_ptr<Sequence<T>> result(this->CreateEmpty());
        for (int i = startIndex; i <= endIndex; ++i) {
            this->AppendToResult(result, items.Get(i));
        }

        return result.release();
    }

    IEnumerator<T>* GetEnumerator() const override {
        return new SequenceEnumerator<T>(*this);
    }

    Sequence<T>* Append(const T& item) override {
        ListSequenceBase<T>* target = Instance();
        std::unique_ptr<ListSequenceBase<T>> targetGuard((target == this) ? nullptr : target);

        Sequence<T>* result = target->AppendInternal(item);
        if (result == target) {
            targetGuard.release();
        }
        return result;
    }

    Sequence<T>* Prepend(const T& item) override {
        ListSequenceBase<T>* target = Instance();
        std::unique_ptr<ListSequenceBase<T>> targetGuard((target == this) ? nullptr : target);

        Sequence<T>* result = target->PrependInternal(item);
        if (result == target) {
            targetGuard.release();
        }
        return result;
    }

    Sequence<T>* InsertAt(const T& item, int index) override {
        ListSequenceBase<T>* target = Instance();
        std::unique_ptr<ListSequenceBase<T>> targetGuard((target == this) ? nullptr : target);

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
