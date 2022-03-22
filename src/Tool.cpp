#include "../header/Tool.hpp"
#include <iostream>
using namespace std;

// CONSTRUCTOR
Tool::Tool() : Item(){
    this->durability = 10;
}

Tool::Tool(int id, string name, int durability) : Item(id, name, "Tool"){
    this->type = type;
    this->durability = durability ;
}

Tool::Tool(int id, string name) : Item(id, name, "Tool"){
    this->type = type;
    this->durability = 10 ;
}

// DESTRUCTOR
Tool::~Tool(){

}

// GETTER
int Tool::getDura() const{
    return this->durability;
}

// SETTER
void Tool::setDura(int Dura){
    this->durability = Dura;
}

// USE
void Tool::use(){
    this->durability--;
}

// OPERATOR OVERLOADING
ostream & operator <<(ostream& os, const Tool& nt){
    os << "[" << nt.getId() << " " << nt.getDura() << "]";
}

Item& Tool::operator +=(int Dura){
    int newDura = this->getDura() + Dura;
    this->setDura(newDura);
}

Item& Tool::operator -=(int Dura){
    int newDura = this->getDura() - Dura;
    if (newDura < 0) newDura = 0;
    this->setDura(newDura);
}