#ifndef NONTOOL_HPP
#define NONTOOL_HPP

#include <bits/stdc++.h>
#include <iostream>
#include "Item.hpp"
using namespace std;

class NonTool : public Item {
protected :
	int quantity;
    string type;
public :
    // CONSTRUCTOR
	NonTool();
    NonTool(int id, string name, string type, int quantity);
    
    // DESTRUCTOR
    ~NonTool();
    
    // GETTER
    int getQty() const;
    string getType() const;
    
    // SETTER
    void setQty(int);
    void setType(string);
    
    // USE
    void use();
    
    // OPERATOR OVERLOADING
    friend ostream & operator <<(ostream&, const NonTool&);
    Item& operator +=(int);
    Item& operator -=(int);
};
//(derivation from nonTool -> Stone dll)

#endif