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

    Node* head_;
    Node* tail_;
    int length_;

    Node* GetNode(int index) const {
        if (index < 0 || index >= length_) {
            throw IndexOutOfRange();
        }
        Node* cur = head_;
        for (int i = 0; i < index; ++i) {
            cur = cur->next;
        }
        return cur;
    }

public:
    LinkedList() : head_(nullptr), tail_(nullptr), length_(0) {}

    LinkedList(const T* items, int count) : head_(nullptr), tail_(nullptr), length_(0) {
        if (count < 0) {
            throw std::invalid_argument("Negative count");
        }
        for (int i = 0; i < count; ++i) {
            Append(items[i]);
        }
    }

    LinkedList(const LinkedList<T>& other) : head_(nullptr), tail_(nullptr), length_(0) {
        Node* cur = other.head_;
        while (cur != nullptr) {
            Append(cur->data);
            cur = cur->next;
        }
    }

    LinkedList<T>& operator=(const LinkedList<T>& other) {
        if (this != &other) {
            Clear();
            Node* cur = other.head_;
            while (cur != nullptr) {
                Append(cur->data);
                cur = cur->next;
            }
        }
        return *this;
    }

    ~LinkedList() {
        Clear();
    }

    void Clear() {
        Node* cur = head_;
        while (cur != nullptr) {
            Node* next = cur->next;
            delete cur;
            cur = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        length_ = 0;
    }

    const T& GetFirst() const {
        if (length_ == 0) {
            throw IndexOutOfRange();
        }
        return head_->data;
    }

    const T& GetLast() const {
        if (length_ == 0) {
            throw IndexOutOfRange();
        }
        return tail_->data;
    }

    const T& Get(int index) const {
        return GetNode(index)->data;
    }


    int GetLength() const {
        return length_;
    }

    LinkedList<T>* GetSubList(int startIndex, int endIndex) const {
        if (startIndex < 0 || endIndex < 0 || startIndex >= length_ || endIndex >= length_ || startIndex > endIndex) {
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
        if (length_ == 0) {
            head_ = tail_ = node;
        } else {
            tail_->next = node;
            tail_ = node;
        }
        ++length_;
    }

    void Prepend(const T& item) {
        Node* node = new Node(item, head_);
        head_ = node;
        if (length_ == 0) {
            tail_ = node;
        }
        ++length_;
    }

    void InsertAt(const T& item, int index) {
        if (index < 0 || index > length_) {
            throw IndexOutOfRange();
        }
        if (index == 0) {
            Prepend(item);
            return;
        }
        if (index == length_) {
            Append(item);
            return;
        }
        Node* prev = GetNode(index - 1);
        prev->next = new Node(item, prev->next);
        ++length_;
    }

    LinkedList<T>* Concat(const LinkedList<T>* other) const {
        LinkedList<T>* result = new LinkedList<T>(*this);
        for (int i = 0; i < other->GetLength(); ++i) {
            result->Append(other->Get(i));
        }
        return result;
    }

    T& operator[](int index){
        if (index < 0 || index >= length_) {
            throw IndexOutOfRange();
        }
        Node* cur = head_;
        for (int i = 0; i < index; ++i) {
            cur = cur->next;
        }
        return cur->data;
    }

};
