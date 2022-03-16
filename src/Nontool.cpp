#include "../header/Nontool.hpp"
#include <iostream>
using namespace std;

NonTool::NonTool() : Item(){
    this->quantity = 0;
}

NonTool::NonTool(int id, string name, string type, int quantity) : Item(id, name, "NonTool"){
    this->quantity = 0;
}

NonTool::~NonTool(){

}

int NonTool::getQty() const{
    return this->quantity;
}

string NonTool::getNtType() const{
    return this->nttype;
}

void NonTool::use(){

}