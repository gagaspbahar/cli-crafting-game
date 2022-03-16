#ifndef NONTOOL_HPP
#define NONTOOL_HPP

#include <bits/stdc++.h>
#include "Item.hpp"
using namespace std;

class NonTool : public Item {
protected :
	int quantity;
    string nttype;
public :
	NonTool();
    NonTool(int id, string name, string type, int quantity);
    ~NonTool();
    int getQty() const;
    string getNtType() const;
    void use();
};
//(derivation from nonTool -> Stone dll)

#endif