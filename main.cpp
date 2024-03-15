#include "ListNode.h"
// > push_back(const T& value): Добавляет элемент в конец списка.
// > push_front(const T& value): Добавляет элемент в начало списка.
// > pop_back(): Удаляет последний элемент из списка.
// > pop_front(): Удаляет первый элемент из списка.
// > insert(iterator position, const T& value): Вставляет элемент на указанную позицию.
// > erase(iterator position): Удаляет элемент на указанной позиции.
// > remove(const T& value): Удаляет все элементы, равные указанному значению.
// > clear(): Удаляет все элементы из списка.
// > size(): Возвращает количество элементов в списке.
// > empty(): Проверяет, пуст ли список.

void first_test(){
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

    while (it != nullptr) 
        *(it++) += 1;

    std::cout << list << std::endl; // Вывод: 1 3 4

    try {
    while(1) {
        list.pop_front();
        std::cout << list << std::endl;
    }} catch (std::runtime_error e)  {
        std::cout << e.what() << std::endl;
    } 

    for(int i = 0; i < 20; ++i) 
        list.push_front(i);

    std::cout << list << std::endl;
}

int main() {
    first_test();

    
    return 0;
}