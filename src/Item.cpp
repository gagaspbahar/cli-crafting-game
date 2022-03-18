#include "../header/Item.hpp"
#include <iostream>
using namespace std;

// INITIALIZE
int Item::numOfItem = 0;

// CONSTRUCTOR
Item::Item() : id(this->numOfItem + 1){
    this->name = "";
    this->category = "";
    Item::numOfItem++;
}

Item::Item(int id, string name, string category) : id(this->numOfItem + 1){
    this->name = name;
    this->category = category; // Tool or NonTool
    Item::numOfItem++;
}

// DESTRUCTOR
Item::~Item(){
}

// GETTER
int Item::getId() const{
    return this->id;
}

string Item::getCategory() const{
    return this->category;
}

string Item::getName() const{
    return this->name;
}

// SETTER
void Item::setId(int id){
    //this->id = id;
    // TODO : id mending const atau ga?
}

void Item::setName(string name){
    this->name = name;
}

void Item::setCategory(string category){
    this->category = category;
}

// OPERATOR OVERLOADING
bool operator==(const Item& i1, const Item& i2){
    return ((i1.getId() == i2.getId()) && (i1.getName() == i2.getName()) && (i1.getCategory() == i2.getCategory()));
}