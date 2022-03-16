#ifndef ITEM_HPP
#define ITEM_HPP

#include <bits/stdc++.h>
using namespace std;

class Item {
protected :
    static int numOfItem;
    const int id;
    string name;
    string type;
public :
	// Constructor
    Item();
    Item(int id, string name, string type);
    // Destructor
    ~Item();
    // Getter
    int getId() const;
    string getName() const;
    string getType() const;
    friend bool operator==(const Item& i1, const Item& i2);
    virtual void use() = 0;
};

#endif