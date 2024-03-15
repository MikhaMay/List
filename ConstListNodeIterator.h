#pragma once
#include "ListNodeIterator.h"

template<typename T>
class ConstListNodeIterator : public ListNodeIterator<T> {
public:
    explicit ConstListNodeIterator(Node<T>* p) : ListNodeIterator<T>(p) {}

    const T& operator*() const {
        return this->ptr->data;
    }
};