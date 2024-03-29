#pragma once
#include "Node.h"
#include "ListNodeIterator.h"
#include "ConstListNodeIterator.h"
#include <iostream>
#include <stdexcept>
#include <initializer_list>

template <typename T>
class ListNode {
private:
    Node<T>* head = nullptr;
    Node<T>* tail = nullptr;
    size_t size_ = 0;
public:
    ListNode() {}

    ListNode(const ListNode<T> & ln) {
        for (auto it = ln.begin(); it != ln.end(); ++it) 
            push_back(*it);
    }

    ListNode<T>& operator= (const ListNode<T> & ln) {
        if (this != &ln) {
            clear();
            for (auto it = ln.begin(); it != ln.end(); ++it) 
                push_back(*it);
        }
        return *this;
    }

    ListNode(ListNode<T> && ln) noexcept : head(ln.head), tail(ln.tail), size_(ln.size_) {
        ln.head = nullptr;
        ln.tail = nullptr;
        ln.size_ = 0;
    }

    ListNode(std::initializer_list<T> ilist) {
        for (auto &item : ilist)
            push_back(item);
    }
    
    ListNode<T>&& operator=(ListNode<T> && ln) noexcept {
        if (this != &ln) {
            clear();
            size_ = ln.size_;
            head = ln.head;
            tail = ln.tail;
            ln.head = nullptr;
            ln.tail = nullptr;
        }
        return std::move(*this);
    }

    ~ListNode() {
        clear();
    }

    void push_back(const T& d) {
        Node<T>* tmp_node = new Node<T>(d);
        if(head == nullptr) {
            head = tmp_node;
            tail = tmp_node;
        } else {
            tail->next = tmp_node;
            tmp_node->prev = tail;
            tail = tmp_node;
        }
        ++size_;
    }

    void push_front(const T& d) {
        Node<T>* tmp_node = new Node<T>(d);
        if(head == nullptr) {
            head = tmp_node;
            tail = tmp_node;
        } else {
            tmp_node->next = head;
            head->prev = tmp_node;
            head = tmp_node;
        }
        ++size_;
    }

    void pop_back() {
        if(head == nullptr) throw std::runtime_error("ListNode is empty;");
        Node<T>* toDelete = tail;
        if(head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete toDelete;
        --size_;
    }

    void pop_front() {
        if(head == nullptr) throw std::runtime_error("ListNode is empty;");
        Node<T>* toDelete = head;
        if(head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete toDelete;
        --size_;
    }

    const T& back() const {
        if(tail == nullptr) throw std::runtime_error("ListNode is empty;");
        return tail->data;
    }

    T& back() {
        if(tail == nullptr) throw std::runtime_error("ListNode is empty;");
        return tail->data;
    }

    const T& front() const {
        if(head == nullptr) throw std::runtime_error("ListNode is empty;");
        return head->data;
    }

    T& front() {
        if(head == nullptr) throw std::runtime_error("ListNode is empty;");
        return head->data;
    }

    ListNodeIterator<T> begin() { return ListNodeIterator<T>(head); }

    ConstListNodeIterator<T> begin() const { return ConstListNodeIterator<T>(head); }

    ListNodeIterator<T> end() { return ListNodeIterator<T>(nullptr); }

    ConstListNodeIterator<T> end() const { return ConstListNodeIterator<T>(nullptr); }

    ListNodeIterator<T> rbegin() { return ListNodeIterator<T>(tail); }

    ConstListNodeIterator<T> rbegin() const { return ConstListNodeIterator<T>(tail); }

    ListNodeIterator<T> rend() { return ListNodeIterator<T>(nullptr); }

    ConstListNodeIterator<T> rend() const { return ConstListNodeIterator<T>(nullptr); }

    friend std::ostream& operator<< (std::ostream& os, const ListNode<T>& list) {
        if (list.head == nullptr) 
            os << "[]";
        else {
            os << "[";
            for (auto cur = list.head; cur != list.tail; cur = cur->next) {
                os << cur->data << ", ";
            }
            os << list.tail->data << "]";
        }
        return os;
    }

    void clear() {
        while (head != nullptr) {
            Node<T>* toDelete = head;
            head = head->next;
            delete toDelete;
            size_ -= 1;
        }
        tail = nullptr;
    }

    void remove(const T& val) {
        Node<T>* current = head;
        while (current != nullptr) {
            if (current->data == val) {
                Node<T>* toDelete = current;
                if (current->next != nullptr) current->next->prev = current->prev;
                if (current->prev != nullptr) current->prev->next = current->next;

                if (current == head) head = current->next;
                if (current == tail) tail = current->prev;

                current = current->next;
                delete toDelete;
                --size_;
            } else {
                current = current->next;
            }
        }
    }

    size_t size() const {
        return size_;
    }

    bool empty() const {
        return size_ == 0;
    }

    void insert(ListNodeIterator<T> position, const T& value) {
        ++size_;
        Node<T>* newNode = new Node<T>(value);
        Node<T>* current = position.ptr;    // Узел, на который указывает position

        if (current == nullptr) {           // Если вставляем в конец списка, или он пустой
            if (head == nullptr) {
                head = newNode;
                tail = newNode;
            }
            else {
                tail->next = newNode;
                tail = newNode;
            }
        }
        else if (current == head) {         // Если вставляем в начало списка, и он не пустой
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        else {                              // Вставляем в середину списка
            newNode->next = current;
            newNode->prev = current->prev;
            current->prev->next = newNode;
            current->prev = newNode;
        }
    }

    void erase(ListNodeIterator<T> position) {
        Node<T>* toDelete = position.ptr;
        
        if (head == tail) {                 // Голова совпадает с хвостом
            head = nullptr;
            tail = nullptr;
        }
        else if (toDelete == head) {        // Удаление головы (элементов больше одного по п. 1)
            head = head->next;
            head->prev = nullptr;
        }
        else if (toDelete == tail) {        // Удаление хвоста (элементов больше одного по п. 1)
            tail = tail->prev;
            tail->next = nullptr;
        }
        else {                              // Удаление середины (элементов больше одного по п. 1)
            toDelete->prev->next = toDelete->next;
            toDelete->next->prev = toDelete->prev;
        }

        delete toDelete;
        --size_;
    }

    bool operator==(const ListNode<T> & l) const {
        if (size_ != l.size_) 
            return false;

        for (auto it1 = begin(), it2 = l.begin(); it1 != end(); ++it1, ++it2) 
            if (*it1 != *it2)
                return false;

        return true;
    }

};