#ifndef TOOL_HPP
#define TOOL_HPP

#include <bits/stdc++.h>
#include <iostream>
#include "Item.hpp"
using namespace std;

class Tool : public Item {
protected :
	int durability;
public :
    // CONSTRUCTOR
	NonTool();
    NonTool(int id, string name, string type, int quantity);
    
    // DESTRUCTOR
    ~NonTool();
    
    // GETTER
    int getQty() const;
    
    // SETTER
    void setQty(int);
    
    // USE
    void use();
    
    // OPERATOR OVERLOADING
    friend ostream & operator <<(ostream&, const NonTool&);
    Item& operator +=(int);
    Item& operator -=(int);
};
};

//(derivation from Tool -> Pickaxe, Axe, Sword)

#endif