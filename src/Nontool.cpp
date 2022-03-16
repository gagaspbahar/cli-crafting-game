#include "../header/Nontool.hpp"
#include <iostream>
using namespace std;

NonTool::NonTool() : Item(){
    this->quantity = 0;
}

NonTool::NonTool(int id, string name, string type, int quantity) : Item(id, name, "NonTool"){
    this->type = type;
    this->quantity = 0;
}

NonTool::~NonTool(){

}

int NonTool::getQty() const{
    return this->quantity;
}

string NonTool::getType() const{
    return this->type;
}

void NonTool::use(){

}