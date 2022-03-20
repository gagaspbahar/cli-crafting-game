#include "../header/Inventory.hpp"
#include <iostream>
using namespace std;

int convertIdToInt(string id) {
    int temp;
    for (int i = 1; i < id.size(); i++) { // Mulai dari i = 1 karena asumsi id slot diawali dengan 'C' atau 'I' untuk menandakan crafting atau inventory
        temp += id[i] * pow(10, id.size() - 1 - i);
    }
    return temp;
}

int getRow(int integer) {
    return (int)(integer / 9);
}

int getCol(int integer) {
    return (integer % 9);
}

Inventory::Inventory() {
    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeCol; j++) {
            inventoryContainer[i][j] = SlotInventory();
        }
    }
    this->quantity = 0;
}

Inventory::Inventory(const Inventory& inv) {
    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeCol; j++) {
            this->inventoryContainer[i][j] = inv.inventoryContainer[i][j];
        }
    }
    this->quantity = inv.quantity;
}

Inventory& Inventory::operator=(const Inventory& inv) {
    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeCol; j++) {
            this->inventoryContainer[i][j] = inv.inventoryContainer[i][j];    
        }
    }
    this->quantity = inv.quantity;
    return *this;
}

Inventory::~Inventory() {
    // cout << "Inventory has been destroyed" << endl;
}

// containItem
bool Inventory::containItem(Item* item) {
    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeCol; j++) {
            Item* temp = this->inventoryContainer[i][j].getItemInfo();
            if (temp->getName() == item->getName() && this->inventoryContainer[i][j].getQuantity() < 64) {
                return true;
            }
        }
    }
    return false;
}

// giveItem
void Inventory::giveItem(Item* item, int quantity) {
    int slotId = 0;
    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeCol; j++) {
            if (quantity != 0) {
                Item* temp = this->inventoryContainer[i][j].getItemInfo();
                if ((this->inventoryContainer[i][j].getQuantity() == 0) && (!(containItem(item)))) {
                    this->inventoryContainer[i][j] = SlotInventory(item, quantity, slotId); // Menyimpan item di slot baru
                    quantity = 0;
                } else if (temp->getName() == item->getName()) {
                    if (temp->isA<NonTool>()) {
                        if (this->inventoryContainer[i][j].getQuantity() + quantity <= 64) {
                            this->inventoryContainer[i][j].addItemToSlot(item, quantity);
                            quantity = 0;
                        } else {
                            int quantityLeft = this->inventoryContainer[i][j].getQuantity() + quantity;
                            quantityLeft -= 64;
                            quantity -= quantityLeft;
                            this->inventoryContainer[i][j].addItemToSlot(item, quantity);
                        }
                    }
                }
            } else {
                return;
            }
            slotId++;
        }
    }
}

// discardItem
void Inventory::discardItem(string id, int quantity) {
    int slotId = convertIdToInt(id);
    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeCol; j++) {
            Item* temp = this->inventoryContainer[i][j].getItemInfo();
            if (this->inventoryContainer[i][j].getSlotId() == slotId) {
                if (temp->isA<NonTool>()) {
                    if (this->inventoryContainer[i][j].getQuantity() >= quantity) {
                        this->inventoryContainer[i][j].removeItem(quantity);
                        if (this->inventoryContainer[i][j].getQuantity() <= 0) {
                            this->inventoryContainer[i][j] = SlotInventory();
                        }
                    } else {
                        cout << "Insufficient number of items, discarding process failed." << endl;
                    }
                }
            }
        }
    }
}

// moveItem
void Inventory::moveItem(string idSrc, string idDest) {
    int rowSrc = getRow(convertIdToInt(idSrc));
    int colSrc = getCol(convertIdToInt(idSrc));
    int rowDest = getRow(convertIdToInt(idDest));
    int colDest = getCol(convertIdToInt(idDest));
    if ((this->inventoryContainer[rowSrc][colSrc].getNameFromSlotItem() == this->inventoryContainer[rowDest][colDest].getNameFromSlotItem()) && (this->inventoryContainer[rowSrc][colSrc].getCategoryFromSlotItem() == this->inventoryContainer[rowDest][colDest].getCategoryFromSlotItem()) && ((this->inventoryContainer[rowSrc][colSrc].getItemInfo())->isA<NonTool>()) && ((this->inventoryContainer[rowDest][colDest].getItemInfo())->isA<NonTool>())) {
        // Move
        int quantityToMove;
        if (this->inventoryContainer[rowSrc][colSrc].getQuantity() <= this->inventoryContainer[rowDest][colDest].getEmptyQuantity()) {
            // Move seluruh item dari origin slot ke destination slot
            quantityToMove = this->inventoryContainer[rowSrc][colSrc].getQuantity();
        } else {
            // Move sebagian item, yakni sejumlah sisa kapasitas destination slot yang ada
            quantityToMove = this->inventoryContainer[rowDest][colDest].getEmptyQuantity();
        }
        // Add
        this->inventoryContainer[rowDest][colDest].addItemToSlot(this->inventoryContainer[rowSrc][colSrc].getItemInfo(), quantityToMove);
        // Remove
        this->inventoryContainer[rowSrc][colSrc].removeItem(quantityToMove);
    } else {
        cout << "You can't stack two different items, moving process failed." << endl;
    }
}

// moveToCrafting
void Inventory::moveToCrafting(string slotIdInventory, int N, string* slotIdCrafting, Crafting table) {
    int rowInventory = getRow(convertIdToInt(slotIdInventory));
    int colInventory = getCol(convertIdToInt(slotIdInventory)); 
    int rowCrafting, colCrafting;
    int idx = N;
    if (this->inventoryContainer[rowInventory][colInventory].getQuantity() >= N) {
        if (N < 9) {
            for (int i = N - 1; i >= 0; i--) {
                idx--;
                rowCrafting = getRow(convertIdToInt(slotIdCrafting[idx]));
                colCrafting = getCol(convertIdToInt(slotIdCrafting[idx]));
                // Add item to crafting
                table.setItem(this->inventoryContainer[rowInventory][colInventory].getItemInfo(), rowCrafting, colCrafting);
            }
            // Remove item from inventory
            this->inventoryContainer[rowInventory][colInventory].removeItem(N);
        }
    }
}

// Export inventory
void Inventory::exportInventory(string outputPath) {
    ofstream outputFile(outputPath);
    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeCol; j++) {
            Item* temp = this->inventoryContainer[i][j].getItemInfo();
            if (temp->isA<NonTool>()) {
                outputFile << temp->getId() << ":" << this->inventoryContainer[i][j].getQuantity() << endl;
            } else {
                Tool* t = dynamic_cast<Tool*>(temp);
                outputFile << t->getId() << ":" << t->getDura() << endl;
            }
        }
    }
}
