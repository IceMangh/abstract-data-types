#pragma once
#include <stdexcept>
#include "Exceptions.h"

template <class T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& data, Node* next = nullptr) : data(data), next(next) {}
    };

    Node* head;
    Node* tail;
    int length;

    Node* GetNode(int index) const {
        if (index < 0 || index >= length) {
            throw IndexOutOfRange();
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current;
    }

public:
    LinkedList() : head(nullptr), tail(nullptr), length(0) {}

    LinkedList(const T* items, int count) : head(nullptr), tail(nullptr), length(0) {
        if (count < 0) {
            throw std::invalid_argument("Negative count");
        }
        for (int i = 0; i < count; ++i) {
            Append(items[i]);
        }
    }

    LinkedList(const LinkedList<T>& other) : head(nullptr), tail(nullptr), length(0) {
        Node* current = other.head;
        while (current != nullptr) {
            Append(current->data);
            current = current->next;
        }
    }

    LinkedList<T>& operator=(const LinkedList<T>& other) {
        if (this != &other) {
            Clear();
            Node* current = other.head;
            while (current != nullptr) {
                Append(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    ~LinkedList() {
        Clear();
    }

    void Clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    const T& GetFirst() const {
        if (length == 0) {
            throw IndexOutOfRange();
        }
        return head->data;
    }

    const T& GetLast() const {
        if (length == 0) {
            throw IndexOutOfRange();
        }
        return tail->data;
    }

    const T& Get(int index) const {
        return GetNode(index)->data;
    }


    int GetLength() const {
        return length;
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex) const {
        if (startIndex < 0 || endIndex < 0 || startIndex >= length || endIndex >= length || startIndex > endIndex) {
            throw IndexOutOfRange();
        }
        LinkedList<T>* result = new LinkedList<T>();
        for (int i = startIndex; i <= endIndex; ++i) {
            result->Append(Get(i));
        }
        return result;
    }

    void Append(const T& item) {
        Node* node = new Node(item);
        if (length == 0) {
            head = tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
        ++length;
    }

    void Prepend(const T& item) {
        Node* node = new Node(item, head);
        head = node;
        if (length == 0) {
            tail = node;
        }
        ++length;
    }

    void InsertAt(const T& item, int index) {
        if (index < 0 || index > length) {
            throw IndexOutOfRange();
        }
        if (index == 0) {
            Prepend(item);
            return;
        }
        if (index == length) {
            Append(item);
            return;
        }
        Node* prev = GetNode(index - 1);
        prev->next = new Node(item, prev->next);
        ++length;
    }

    LinkedList<T>* Concat(const LinkedList<T>* other) const {
        LinkedList<T>* result = new LinkedList<T>(*this);
        for (int i = 0; i < other->GetLength(); ++i) {
            result->Append(other->Get(i));
        }
        return result;
    }

    T& operator[](int index) {
        if (index < 0 || index >= length) {
            throw IndexOutOfRange();
        }
        Node* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

};
