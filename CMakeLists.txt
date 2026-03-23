cmake_minimum_required(VERSION 4.0)
project(atd)

set(CMAKE_CXX_STANDARD 20)

add_executable(atd main.cpp
        ArraySequence.h
        DynamicArray.h
        Exceptions.h
        ImmutableArraySequence.h
        LinkedList.h
        ListSequence.h
        Sequence.h
        Tests.h
        IEnumerator.h
        IEnumerable.h
        SequenceEnumerator.h
        ICollection.h
)
