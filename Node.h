#pragma once

template <typename T>
struct Node {
    T data;
    Node* prev = nullptr;
    Node* next = nullptr;

    Node(const T& d) : data(d), prev(nullptr), next(nullptr) {}
};