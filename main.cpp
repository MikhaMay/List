#include "ListNode.h"



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

    auto it = list.begin();

    while (it != list.end()) 
        *(it++) += 1;

    std::cout << list << std::endl; // Вывод: 1 3 4

    return 0;
}