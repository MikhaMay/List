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

    while (it != list.end()) 
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

void second_test(){
    ListNode<double> list;
    
    list.push_back(2.2);
    list.push_back(1.1);
    list.push_back(2.2);
    list.push_back(3.3);
    list.push_back(2.2);
    list.push_back(4.4);
    
    std::cout << list.size() << " " << list.empty() << std::endl;

    std::cout << list << std::endl;

    list.remove(2.2);   // удаление всех 2.2

    std::cout << list.size() << " " << list.empty() << std::endl;

    std::cout << list << std::endl;

    list.clear();       // очистка

    std::cout << list.size() << " " << list.empty() << std::endl;

    std::cout << list << std::endl;
}

void third_test() {
    ListNode<int> list;
    for (int i = 1; i < 6; ++i) list.push_back(i);

    std::cout << list << std::endl; // Вывод: 1 2 3 4 5

    auto it = list.begin();
    ++(++it);

    list.insert(it, -1);

    std::cout << list << std::endl; // Вывод: 1 2 -1 3 4 5

    list.insert(list.end(), -2);
    list.insert(list.begin(), -3);

    std::cout << list << std::endl; // Вывод: -3 1 2 -1 3 4 5 -2

    list.clear();
    list.insert(list.end(), 10);

    std::cout << list << std::endl; // Вывод: 10

    it = list.begin();
    for (int i = 1; i < 6; ++i) list.insert(it, i);

    std::cout << list << std::endl; // Вывод: 1 2 3 4 5 6 10

    it = list.rbegin();
    while ( !list.empty() ) {
        list.erase(it--);
        std::cout << list << std::endl;}
}

void fourth_test() {
    
}

int main() {
    // first_test();

    //second_test();

    third_test();

    return 0;
}