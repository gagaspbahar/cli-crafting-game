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
    string getName();
    virtual void use() = 0;
};

#endif