#ifndef ITEM_H
#define ITEM_H
#include <iostream>

using namespace std;

template <class T>
class Item
{
private:
    T m_information;
    Item* m_nextElement;   //If there is no next element = nullptr
public:
    Item(){ };
    Item(T value) : m_information(value) { };
    void print() const{
        cout << "Value of item: " << m_information << '\n'
             << "Next element: " << m_nextElement->m_information << '\n';
    };



    template<class listeT>
    friend class Liste;
};

#endif // ITEM_H
