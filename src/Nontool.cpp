#include "../header/Nontool.hpp"
#include <iostream>
using namespace std;

// CONSTRUCTOR
NonTool::NonTool() : Item(){
    this->quantity = 0;
}

NonTool::NonTool(int id, string name, string type, int quantity) : Item(id, name, "NonTool"){
    this->type = type;
    this->quantity = quantity;
}

// DESTRUCTOR
NonTool::~NonTool(){

}

// GETTER
int NonTool::getQty() const{
    return this->quantity;
}

string NonTool::getType() const{
    return this->type;
}

// SETTER
void NonTool::setQty(int qty){
    if (qty <= 64){
        this->quantity = qty;
    } else {
        this->quantity = 64;
    }
}

void NonTool::setType(string type){
    this->type = type;
}

void NonTool::use(){
    
}

// OPERATOR OVERLOADING
ostream & operator <<(ostream& os, const NonTool& nt){
    os << "[" << nt.getId() << " " << nt.getQty() << "]";
}

Item& NonTool::operator +=(int qty){
    int newQty = this->getQty() + qty;
    if (newQty <= 64){
        this->setQty(newQty);
    } else {
        this->setQty(64);
    }
}

Item& NonTool::operator -=(int qty){
    int newQty = this->getQty() - qty;
    if (newQty < 0) newQty = 0;
    this->setQty(newQty);
}