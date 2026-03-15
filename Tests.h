#pragma once
#include <cassert>
#include <iostream>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "ArraySequence.h"
#include "ListSequence.h"

inline void TestDynamicArray() {
    int data[] = {1, 2, 3};
    DynamicArray<int> arr(data, 3);
    assert(arr.GetSize() == 3);
    assert(arr.Get(0) == 1);
    arr.Set(1, 10);
    assert(arr.Get(1) == 10);
    arr.Resize(5);
    assert(arr.GetSize() == 5);
    assert(arr.Get(0) == 1);
}

inline void TestLinkedList() {
    int data[] = {1, 2, 3};
    LinkedList<int> list(data, 3);
    assert(list.GetFirst() == 1);
    assert(list.GetLast() == 3);
    list.Append(4);
    list.Prepend(0);
    list.InsertAt(99, 2);
    assert(list.GetFirst() == 0);
    assert(list.Get(2) == 99);
    assert(list.GetLast() == 4);
}

inline void TestArraySequence() {
    int data[] = {1, 2, 3};
    ArraySequence<int> seq(data, 3);
    seq.Append(4)->Prepend(0)->InsertAt(99, 2);
    assert(seq.GetFirst() == 0);
    assert(seq.Get(2) == 99);
    assert(seq.GetLast() == 4);

    Sequence<int>* sub = seq.GetSubsequence(1, 3);
    assert(sub->GetLength() == 3);
    assert(sub->Get(0) == 1);
    delete sub;
}

inline void TestListSequence() {
    int data[] = {1, 2, 3};
    ListSequence<int> seq(data, 3);
    seq.Append(4)->Prepend(0)->InsertAt(99, 2);
    assert(seq.GetFirst() == 0);
    assert(seq.Get(2) == 99);
    assert(seq.GetLast() == 4);

    Sequence<int>* sub = seq.GetSubsequence(1, 3);
    assert(sub->GetLength() == 3);
    assert(sub->Get(0) == 1);
    delete sub;
}

inline void TestConcat() {
    int a[] = {1, 2};
    int b[] = {3, 4};
    ArraySequence<int> seq1(a, 2);
    ListSequence<int> seq2(b, 2);

    Sequence<int>* joined = seq1.Concat(&seq2);
    assert(joined->GetLength() == 4);
    assert(joined->Get(0) == 1);
    assert(joined->Get(3) == 4);
    delete joined;
}

inline void RunAllTests() {
    TestDynamicArray();
    TestLinkedList();
    TestArraySequence();
    TestListSequence();
    TestConcat();
    std::cout << "All tests passed!\n";
}
