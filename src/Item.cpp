#include "../header/Item.hpp"
#include <iostream>
using namespace std;

int Item::numOfItem = 0;

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

Item::~Item(){
}

int Item::getId() const{
    return this->id;
}

string Item::getCategory() const{
    return this->category;
}

string Item::getName() const{
    return this->name;
}

bool operator==(const Item& i1, const Item& i2){
    return ((i1.getId() == i2.getId()) && (i1.getName() == i2.getName()) && (i1.getCategory() == i2.getCategory()));
}