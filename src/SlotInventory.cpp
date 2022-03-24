#include "../header/SlotInventory.hpp"
#include <iostream>
using namespace std;

SlotInventory::SlotInventory() {
    this->quantity = 0;
    this->slotId = -1;
    this->item = new NonTool();
}

SlotInventory::SlotInventory(Item* item, int quantity, int slotId) {
    this->slotId = slotId;
    if (quantity <= capacity) {
        this->quantity = quantity;
        this->item = item;
    } else {
        FullException* err = new FullException();
        throw err;
    }
}

SlotInventory::SlotInventory(const SlotInventory& si) {
    this->slotId = si.slotId;
    if (quantity <= capacity){
        this->quantity = si.quantity;
        this->item = si.item;
    } else {
        FullException* err = new FullException();
        throw err;
    }
}

SlotInventory& SlotInventory::operator=(const SlotInventory& si){
    this->slotId = si.slotId;
    if (quantity <= capacity){
        this->quantity = si.quantity;
        this->item = si.item;
    } else {
        FullException* err = new FullException();
        throw err;
    }
    return *this;
}

SlotInventory::~SlotInventory() {
    delete item;
}

int SlotInventory::getSlotId() {
    return this->slotId;
}

int SlotInventory::getQuantity() {
    return this->quantity;
}

int SlotInventory::getEmptyQuantity() {
    return (capacity - quantity);
}

Item* SlotInventory::getItemInfo() {
    return this->item;
}

string SlotInventory::getNameFromSlotItem() {
    return getItemInfo()->getName();
}

string SlotInventory::getCategoryFromSlotItem() {
    return getItemInfo()->getCategory();
}

void SlotInventory::setSlotId(int slotId) {
    this->slotId = slotId;
}

void SlotInventory::setQuantity(int quantity) {
    this->quantity = quantity;
}

void SlotInventory::addQuantity(int quantity) {
    this->quantity += quantity;
}

void SlotInventory::addItemToSlot(Item* item, int quantity) {
    Item* temp;
    if(item->getCategory() == "TOOL"){
        temp = new Tool(item->getId() , item->getName() , item->getDura());
    }else{
        temp = new NonTool(item->getId() , item->getName() , item->getType(), item->getQty() + quantity);
    }
    this->item = temp;
    this->quantity += quantity;
}

void SlotInventory::removeItem(int quantity) {
    this->quantity -= quantity;
}