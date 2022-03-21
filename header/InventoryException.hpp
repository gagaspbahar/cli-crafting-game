#ifndef _INVENTORYEXCEPTION_HPP_
#define _INVENTORYEXCEPTION_HPP_

#include <iostream>
using namespace std;

class InventoryException {
public:
    virtual void print() = 0;
};

class FullException : public InventoryException {
public:
    void print() {
        cout << "Sorry, the item quantity is over the maximum capacity." ;
    }
};

class EmptyException : public InventoryException {
public:
    void print() {
        cout << "Insufficient number of items, discarding process failed.";
    }
};

class DifferentItemException : public InventoryException {
public:
    void print() {
        cout << "You can't stack two different items, moving process failed.";
    }
};

#endif