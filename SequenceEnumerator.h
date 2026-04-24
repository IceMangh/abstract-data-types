#pragma once
#include "IEnumerator.h"
#include "Sequence.h"

template <class T>
class SequenceEnumerator : public IEnumerator<T> {
private:
    const Sequence<T>& sequence;
    int index;

public:
    SequenceEnumerator(const Sequence<T>& sequence)
            : sequence(sequence), index(-1) {}

    bool MoveNext() override {
        if (index + 1 < sequence.GetLength()) {
            ++index;
            return true;
        }
        return false;
    }

    T Current() const override {
        return sequence.Get(index);
    }
};
