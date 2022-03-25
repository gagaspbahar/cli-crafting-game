#ifndef TOOL_HPP
#define TOOL_HPP

#include <string>
#include <iostream>
#include "Item.hpp"
using namespace std;

class Tool : public Item {
protected :
	int durability;
public :
    // CONSTRUCTOR
	Tool();
    Tool(int id, string name, int durability);
    Tool(int id, string name); // ini durability nya udah auto set 10 di awal
    
    // DESTRUCTOR
    ~Tool();
    
    // GETTER
    int getDura() const;
    
    // SETTER
    void setDura(int);
    
    // USE
    void use();
    bool isTool();
    
    // OPERATOR OVERLOADING
    friend ostream & operator <<(ostream&, const Tool&);
    Tool& operator=(const Tool& tool);
    Tool& operator +=(int);
    Tool& operator -=(int);
};

//(derivation from Tool -> Pickaxe, Axe, Sword)

#endif