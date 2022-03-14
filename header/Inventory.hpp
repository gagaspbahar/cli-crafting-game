#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <iostream>
#include "Item.hpp"
#include <map>
using namespace std;

#define MAX_CAP 64

template <class T>
class Inventory {
protected :
    map<T, int> inv;
    int size;
public :
    Inventory();
    int getCapacity() const;
    bool isFull() const;
    void giveItem(T item);
    void moveItem(T item);
    void discardItem(int idx);
    void showInventory();
};

#endif