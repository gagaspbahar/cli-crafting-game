#include "../header/Item.hpp"
#include "../header/Config.hpp"
#include <iostream>
using namespace std;

// CONSTRUCTOR
Item::Item() {
    this->id = 0;
    this->name = "";
    this->category = "";
}

Item::Item(int id, string name, string category){
    this->name = name;
    this->category = category; // Tool or NonTool
    this->id = id;
}


Item::Item(const Item& i){
    this->id = i.id;
    this->name = i.name;
    this->category = i.category;
}

// DESTRUCTOR
Item::~Item() {
}

// GETTER
int Item::getId() const {
    return this->id;
}

string Item::getCategory() const {
    return this->category;
}

string Item::getName() const {
    return this->name;
}

// SETTER
void Item::setId(int id) {
    //this->id = id;
    // TODO : id mending const atau ga?
}

void Item::setName(string name) {
    this->name = name;
}

void Item::setCategory(string category) {
    this->category = category;
}

// OPERATOR ASSIGNMENT
Item& Item::operator=(const Item& item){
    this->name = item.name;
    this->id = item.id;
    this->category = item.category;
    return *this;
}

// OPERATOR OVERLOADING
bool operator==(const Item& i1, const Item& i2) {
    return ((i1.getId() == i2.getId()) && (i1.getName() == i2.getName()) && (i1.getCategory() == i2.getCategory()));
}