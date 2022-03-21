#include "../header/SlotInventory.hpp"
#include <iostream>
using namespace std;

SlotInventory::SlotInventory() {
    this->quantity = 0;
    this->slotId = -1;
    for (int i = 0; i < capacity; i++) {
        this->slotContainer[i].setId(-1);
        this->slotContainer[i].setName("");
        this->slotContainer[i].setCategory("");
    } 
}

SlotInventory::SlotInventory(Item* slotContainer, int quantity, int slotId) {
    this->slotId = slotId;
    if (quantity <= capacity) {
        this->quantity = quantity;
        this->slotContainer = slotContainer;
    } else {
        FullException* err = new FullException();
        throw err;
    }
}

SlotInventory::SlotInventory(const SlotInventory& si) {
    this->slotId = si.slotId;
    if (quantity <= capacity){
        this->quantity = si.quantity;
        this->slotContainer = si.slotContainer;
    } else {
        FullException* err = new FullException();
        throw err;
    }
}

SlotInventory::~SlotInventory() {
    // cout << "SlotInventory has been destroyed" << endl;
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
    return this->slotContainer;
}

string SlotInventory::getNameFromSlotItem() {
    return this->slotContainer[0].getName();
}

string SlotInventory::getCategoryFromSlotItem() {
    return this->slotContainer[0].getCategory();
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
    int currentQuantity = this->quantity + quantity;
    for (int i = this->quantity; i < currentQuantity; i++) {
        this->slotContainer[i] = item[i - this->quantity];
    }
    this->quantity = currentQuantity;
}

void SlotInventory::removeItem(int quantity) {
    int currentQuantity = this->quantity - quantity;
    for (int i = currentQuantity; i < this->quantity; i++) {
        this->slotContainer[i].setId(-1);
        this->slotContainer[i].setName("");
        this->slotContainer[i].setCategory("");
    }
    this->quantity = currentQuantity;
}