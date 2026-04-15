#pragma once
#include <cassert>
#include <iostream>
#include "DynamicArray.h"
#include "LinkedList.h"
#include "MutableArraySequence.h"
#include "ImmutableArraySequence.h"
#include "MutableListSequence.h"
#include "ImmutableListSequence.h"

int Double(int x) {
    return x * 2;
}

int Sum(int a, int b) {
    return a + b;
}

int Multiply(int a, int b) {
    return a * b;
}

inline void TestDynamicArray() {
    int data[] = {1, 2, 3};
    DynamicArray<DynamicArray<int>> arr(3);
    DynamicArray<int> arr1(data, 3);
    DynamicArray<int> arr2(data, 3);
    DynamicArray<int> arr3(data, 3);
    arr.Set(0, arr1);
    arr.Set(1, arr2);
    arr.Set(1, arr3);
    assert(arr.Get(0).Get(0) == 1);
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
    MutableArraySequence<int> seq(data, 3);
    seq.Append(4)->Prepend(0)->InsertAt(99, 2);
    assert(seq.GetFirst() == 0);
    assert(seq.Get(2) == 99);
    assert(seq.GetLast() == 4);

    Sequence<int>* sub = seq.GetSubsequence(1, 3);
    assert(sub->GetLength() == 3);
    assert(sub->Get(0) == 1);
    delete sub;
}

inline void TestArraySequenceMap() {
    int data[] = {1, 2, 32};
    MutableArraySequence<int> seq(data, 3);
    Sequence<int>* mapped = seq.Map(Double);

    assert(mapped->GetLength() == 3);
    assert(mapped->Get(0) == 2);
    assert(mapped->Get(1) == 4);
    assert(mapped->Get(2) == 64);
    delete mapped;
}

inline void TestArraySequenceFrom() {
    int data[] = {1, 2, 3};

    MutableArraySequence<int> seq = MutableArraySequence<int>::From(data, 3);

    assert(seq.GetLength() == 3);
    assert(seq.Get(0) == 1);
    assert(seq.Get(1) == 2);
    assert(seq.Get(2) == 3);
}

void TestArraySequenceReduce() {
    int data[] = {1, 2, 3, 4};
    MutableArraySequence<int> seq(data, 4);

    int sumResult = seq.Reduce(Sum, 0);
    int mulResult = seq.Reduce(Multiply, 1);

    assert(sumResult == 10);
    assert(mulResult == 24);
}

inline void TestListSequence() {
    int data[] = {1, 2, 3};
    MutableListSequence<int> seq(data, 3);
    seq.Append(4)->Prepend(0)->InsertAt(99, 2);
    assert(seq.GetFirst() == 0);
    assert(seq.Get(2) == 99);
    assert(seq.GetLast() == 4);

    Sequence<int>* sub = seq.GetSubsequence(1, 3);
    assert(sub->GetLength() == 3);
    assert(sub->Get(0) == 1);
    delete sub;
}

inline void TestListSequenceMap() {
    int data[] = {1, 2, 3};

    MutableListSequence<int> seq(data, 3);
    Sequence<int>* mapped = seq.Map(Double);

    assert(mapped->GetLength() == 3);
    assert(mapped->Get(0) == 2);
    assert(mapped->Get(1) == 4);
    assert(mapped->Get(2) == 6);

    delete mapped;
}

inline void TestListSequenceFrom() {
    int data[] = {1, 2, 3};

    MutableListSequence<int> seq = MutableListSequence<int>::From(data, 3);

    assert(seq.GetLength() == 3);
    assert(seq.Get(0) == 1);
    assert(seq.Get(1) == 2);
    assert(seq.Get(2) == 3);
}

void TestListSequenceReduce() {
    int data[] = {1, 2, 3, 4};
    MutableListSequence<int> seq(data, 4);

    int sumResult = seq.Reduce(Sum, 0);
    int mulResult = seq.Reduce(Multiply, 1);

    assert(sumResult == 10);
    assert(mulResult == 24);
}

inline void TestConcat() {
    int a[] = {1, 2};
    int b[] = {3, 4};

    MutableArraySequence<int> seq1(a, 2);
    ImmutableListSequence<int> seq2(b, 2);

    Sequence<int>* joined = seq1 + seq2;
    assert(joined->GetLength() == 4);
    assert(joined->Get(0) == 1);
    assert(joined->Get(1) == 2);
    assert(joined->Get(2) == 3);
    assert(joined->Get(3) == 4);

    delete joined;
}

inline void TestClone() {
    int data[] = {1, 2, 3};
    MutableArraySequence<int> seq(data, 3);

    Sequence<int>* copy = seq.Clone();

    assert(copy->GetCount() == 3);
    assert(copy->Get(0) == 1);
    assert(copy->Get(1) == 2);
    assert(copy->Get(2) == 3);

    delete copy;
}

inline void TestImmutableArraySequence() {
    int data[] = {1, 2, 3};
    ImmutableArraySequence<int> original(data, 3);

    Sequence<int>* appended = original.Append(4);
    Sequence<int>* prepended = original.Prepend(0);
    Sequence<int>* inserted = original.InsertAt(99, 1);

    assert(original.GetLength() == 3);
    assert(original.Get(0) == 1);
    assert(original.Get(1) == 2);
    assert(original.Get(2) == 3);

    assert(appended->GetLength() == 4);
    assert(appended->GetLast() == 4);

    assert(prepended->GetLength() == 4);
    assert(prepended->GetFirst() == 0);

    assert(inserted->GetLength() == 4);
    assert(inserted->Get(1) == 99);
    assert(inserted->Get(2) == 2);

    delete appended;
    delete prepended;
    delete inserted;
}

inline void TestImmutableArraySequenceMapReduce() {
    int data[] = {1, 2, 3, 4};
    ImmutableArraySequence<int> seq(data, 4);

    Sequence<int>* mapped = seq.Map(Double);
    Sequence<int>* sub = seq.GetSubsequence(1, 2);
    Sequence<int>* joined = seq + *sub;

    assert(mapped->GetLength() == 4);
    assert(mapped->Get(0) == 2);
    assert(mapped->Get(3) == 8);

    assert(sub->GetLength() == 2);
    assert(sub->Get(0) == 2);
    assert(sub->Get(1) == 3);

    assert(joined->GetLength() == 6);
    assert(joined->Get(4) == 2);
    assert(joined->Get(5) == 3);

    assert(seq.Reduce(Sum, 0) == 10);
    assert(seq.Reduce(Multiply, 1) == 24);

    delete mapped;
    delete sub;
    delete joined;
}

inline void TestImmutableListSequence() {
    int data[] = {1, 2, 3};
    ImmutableListSequence<int> original(data, 3);

    Sequence<int>* appended = original.Append(4);
    Sequence<int>* prepended = original.Prepend(0);
    Sequence<int>* inserted = original.InsertAt(99, 1);

    assert(original.GetLength() == 3);
    assert(original.Get(0) == 1);
    assert(original.Get(1) == 2);
    assert(original.Get(2) == 3);

    assert(appended->GetLength() == 4);
    assert(appended->GetLast() == 4);

    assert(prepended->GetLength() == 4);
    assert(prepended->GetFirst() == 0);

    assert(inserted->GetLength() == 4);
    assert(inserted->Get(1) == 99);
    assert(inserted->Get(2) == 2);

    delete appended;
    delete prepended;
    delete inserted;
}

inline void TestImmutableListSequenceMapReduce() {
    int data[] = {1, 2, 3, 4};
    ImmutableListSequence<int> seq(data, 4);

    Sequence<int>* mapped = seq.Map(Double);
    Sequence<int>* sub = seq.GetSubsequence(1, 2);
    Sequence<int>* joined = seq + *sub;

    assert(mapped->GetLength() == 4);
    assert(mapped->Get(0) == 2);
    assert(mapped->Get(3) == 8);

    assert(sub->GetLength() == 2);
    assert(sub->Get(0) == 2);
    assert(sub->Get(1) == 3);

    assert(joined->GetLength() == 6);
    assert(joined->Get(4) == 2);
    assert(joined->Get(5) == 3);

    assert(seq.Reduce(Sum, 0) == 10);
    assert(seq.Reduce(Multiply, 1) == 24);

    delete mapped;
    delete sub;
    delete joined;
}

inline void TestMutableVsImmutableListDifference() {
    int data[] = {1, 2, 3};
    MutableListSequence<int> mutableSeq(data, 3);
    ImmutableListSequence<int> immutableSeq(data, 3);

    mutableSeq.Append(10);
    Sequence<int>* immutableResult = immutableSeq.Append(10);

    assert(mutableSeq.GetLength() == 4);
    assert(mutableSeq.GetLast() == 10);

    assert(immutableSeq.GetLength() == 3);
    assert(immutableSeq.GetLast() == 3);
    assert(immutableResult->GetLength() == 4);
    assert(immutableResult->GetLast() == 10);

    delete immutableResult;
}

inline void TestMutableVsImmutableDifference() {
    int data[] = {1, 2, 3};
    MutableArraySequence<int> mutableSeq(data, 3);
    ImmutableArraySequence<int> immutableSeq(data, 3);

    mutableSeq.Append(10);
    Sequence<int>* immutableResult = immutableSeq.Append(10);

    assert(mutableSeq.GetLength() == 4);
    assert(mutableSeq.GetLast() == 10);

    assert(immutableSeq.GetLength() == 3);
    assert(immutableSeq.GetLast() == 3);
    assert(immutableResult->GetLength() == 4);
    assert(immutableResult->GetLast() == 10);

    delete immutableResult;
}

inline void RunAllTests() {
    TestDynamicArray();
    TestLinkedList();
    TestArraySequence();
    TestListSequence();
    TestArraySequenceFrom();
    TestArraySequenceMap();
    TestListSequenceFrom();
    TestArraySequenceReduce();
    TestListSequenceMap();
    TestListSequenceReduce();
    TestConcat();
    TestClone();
    TestImmutableArraySequence();
    TestImmutableArraySequenceMapReduce();
    TestImmutableListSequence();
    TestImmutableListSequenceMapReduce();
    TestMutableVsImmutableDifference();
    TestMutableVsImmutableListDifference();
    std::cout << "All tests passed!\n";
}
