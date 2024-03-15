#include <iostream>
#include <stdexcept>

template <typename T>
struct Node {
    T data;
    Node* prev = nullptr;
    Node* next = nullptr;

    Node(const T& d) : data(d), prev(nullptr), next(nullptr) {}
};

template<typename T>
class ListNodeIterator {
public:
    Node<T>* ptr;

    explicit ListNodeIterator(Node<T>* p) : ptr(p) {}

    ListNodeIterator<T>& operator++() {
        ptr = ptr->next;
        return *this;
    }

    ListNodeIterator<T>& operator--() {
        ptr = ptr->prev;
        return *this;
    }

    T& operator*() {
        return ptr->data;
    }

    bool operator!=(const ListNodeIterator<T>& other) const {
        return ptr != other.ptr;
    }

    bool operator==(const ListNodeIterator<T>& other) const {
        return ptr == other.ptr;
    }
};

template<typename T>
class ConstListNodeIterator : public ListNodeIterator<T> {
public:
    explicit ConstListNodeIterator(Node<T>* p) : ListNodeIterator<T>(p) {}

    const T& operator*() const {
        return this->ptr->data;
    }
};


template <typename T>
class ListNode {
private:
    Node<T>* head;
    Node<T>* tail;
public:
    ListNode() : head(nullptr), tail(nullptr) {}

    ~ListNode() {
        while (head != nullptr) {
            Node<T>* next = head->next;
            delete head;
            head = next;
        }
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
    }

    void pop_back() {
        if(head == nullptr) return;

        Node<T>* toDelete = tail;
        if(head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete toDelete;
    }

    void pop_front() {
        if(head == nullptr) return;

        Node<T>* toDelete = head;
        if(head == tail) {
            head = nullptr;
            tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete toDelete;
    }

    const T& back() const {
        if(tail == nullptr) throw std::runtime_error("ListNode is empty;\n");
        return tail->data;
    }

    T& back() {
        if(tail == nullptr) throw std::runtime_error("ListNode is empty;\n");
        return tail->data;
    }

    const T& front() const {
        if(head == nullptr) throw std::runtime_error("ListNode is empty;\n");
        return head->data;
    }

    T& front() {
        if(head == nullptr) throw std::runtime_error("ListNode is empty;\n");
        return head->data;
    }

    ListNodeIterator<T> begin() { return ListNodeIterator<T>(head); }

    ListNodeIterator<T> end() { return ListNodeIterator<T>(nullptr); }

    ConstListNodeIterator<T> begin() const { return ConstListNodeIterator<T>(head); }

    ConstListNodeIterator<T> end() const { return ConstListNodeIterator<T>(nullptr); }

    friend std::ostream& operator<< (std::ostream& os, const ListNode<T>& list) {
        for (auto it = list.begin(); it != list.end(); ++it) {
            os << *it << " ";
        }
        return os;
    }
};

int main() {
    ListNode<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    std::cout << list << std::endl; // Вывод: 1 2 3

    list.pop_front();
    std::cout << list << std::endl; // Вывод: 2 3

    list.push_front(0);
    std::cout << list << std::endl; // Вывод: 0 2 3

    return 0;
}