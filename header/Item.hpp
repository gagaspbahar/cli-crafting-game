#ifndef ITEM_HPP
#define ITEM_HPP

#include <bits/stdc++.h>
using namespace std;

class Item {
protected :
    const int id;
    string name;
    string type;
public :
	Item();
    ~Item();
};

class Tool : public Item {
protected :
	int quantity;
public :
	
};

//(derivation from Tool -> Pickaxe, Axe, Sword)

class NonTool : public Item {
protected :
	int durability;
public :
	
};
//(derivation from nonTool -> Stone dll)


#endif