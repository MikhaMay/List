#pragma once
#include "Node.h"
#include <cstddef> // Для std::nullptr_t

template<typename T>
class ListNodeIterator {
public:
    Node<T>* ptr;

    explicit ListNodeIterator(Node<T>* p) : ptr(p) {}

    ListNodeIterator<T>& operator++() {
        ptr = ptr->next;
        return *this;
    }

    ListNodeIterator<T> operator++(int) {
        ListNodeIterator<T> tmp(ptr);
        this->operator++();
        return tmp;
    }

    ListNodeIterator<T>& operator--() {
        ptr = ptr->prev;
        return *this;
    }

    ListNodeIterator<T> operator--(int) {
        ListNodeIterator<T> tmp(ptr);
        this->operator--();
        return tmp;
    }

    T& operator*() {
        return ptr->data;
    }

    bool operator!=(const ListNodeIterator<T>& other) const {
        return ptr != other.ptr;
    }

    bool operator!=(std::nullptr_t) const {
        return ptr != nullptr;
    }
};