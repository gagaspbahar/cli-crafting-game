#include "../header/Item.hpp"
#include <iostream>
using namespace std;

int Item::numOfItem = 0;

Item::Item() : id(this->numOfItem + 1){
    this->name = "";
    this->type = "";
    Item::numOfItem++;
}

Item::Item(int id, string name, string type) : id(this->numOfItem + 1){
    this->name = name;
    this->type = type; // Tool or NonTool
    Item::numOfItem++;
}

Item::~Item(){

}

int Item::getId() const{
    this->id;
}

string getName(){

}