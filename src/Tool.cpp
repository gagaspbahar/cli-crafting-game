#include "../header/Tool.hpp"
#include <iostream>
using namespace std;

// CONSTRUCTOR
Tool::Tool() : Item(){
    this->durability = 10;
}

Tool::Tool(int id, string name, int durability) : Item(id, name, "TOOL"){
    this->durability = durability ;
}

Tool::Tool(int id, string name) : Item(id, name, "Tool"){
    this->durability = 10 ;
}

// DESTRUCTOR
Tool::~Tool(){

}

// GETTER
int Tool::getDura() const{
    return this->durability;
}

// int Tool::getQty() const{
//     return -1;
// }

// string Tool::getType() const{
//     return "";
// }

// SETTER
void Tool::setDura(int Dura){
    this->durability = Dura;
}

// void Tool::setQty(int Qty){
    
// }

// USE
void Tool::use(){
    this->durability--;
}

// bool Tool::isTool(){
//     return true;
// }

// OPERATOR OVERLOADING
ostream & operator <<(ostream& os, const Tool& nt){
    os << "[" << nt.getId() << " " << nt.getDura() << "]";
    return os;
}

Tool& Tool::operator=(const Tool& item){
    this->name = item.name;
    this->id = item.id;
    this->category = item.category;
    this->durability = item.durability;
    return *this;
}

// Tool& Tool::operator +=(int Dura){
//     int newDura = this->getDura() + Dura;
//     this->setDura(newDura);
//     return *this;
// }

// Tool& Tool::operator -=(int Dura){
//     int newDura = this->getDura() - Dura;
//     if (newDura < 0) newDura = 0;
//     this->setDura(newDura);
//     return *this;
// }