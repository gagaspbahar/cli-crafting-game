#ifndef ITEM_HPP
#define ITEM_HPP

#include <bits/stdc++.h>
using namespace std;

class Item {
protected :
    static int numOfItem;
    const int id;
    string name;
    string category;
public :
	// Constructor
    Item();
    Item(int id, string name, string category);
    // Destructor
    ~Item();
    // Getter
    int getId() const;
    string getName() const;
    string getCategory() const;
    friend bool operator==(const Item& i1, const Item& i2);
    virtual void use() = 0;
};

#endif