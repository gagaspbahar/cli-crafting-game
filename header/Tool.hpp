#ifndef TOOL_HPP
#define TOOL_HPP

#include <bits/stdc++.h>
#include <iostream>
#include "Item.hpp"
using namespace std;

class Tool : public Item {
protected :
	int durability;
	string type;
public :
	
};

//(derivation from Tool -> Pickaxe, Axe, Sword)

#endif