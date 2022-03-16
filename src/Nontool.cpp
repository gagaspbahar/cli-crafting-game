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

void NonTool::use(){

}