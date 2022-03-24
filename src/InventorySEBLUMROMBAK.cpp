#include "../header/Inventory.hpp"
#include <cmath>
#include <vector>
using namespace std;

int getRowCraft(int integer) {
    return (int)(integer / 3);
}

int getColCraft(int integer) {
    return (integer % 3);
}

int convertIdToInt(string id) {
    int temp;
    for (int i = 1; i < id.size(); i++) { // Mulai dari i = 1 karena asumsi id slot diawali dengan 'C' atau 'I' untuk menandakan crafting atau inventory
        temp += id[i] * pow(10, id.size() - 1 - i);
    }
    return temp;
}

int getRowInv(int integer) {
    return (int)(integer / 9);
}

int getColInv(int integer) {
    return (integer % 9);
}

Inventory::Inventory() {
    vector<vector<SlotInventory*>> inventoryContainer;
    for (int i = 0; i < sizeRow; i++) {
        vector<SlotInventory*> temp;
        for (int j = 0; j < sizeCol; j++) {
            SlotInventory* tempslot = new SlotInventory();
            temp.push_back(tempslot);
        }
        inventoryContainer.push_back(temp);
    }
    this->quantity = 0;
    this->inventoryContainer = inventoryContainer;
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
    for(int i = 0 ; i < sizeRow ; i++){
        for (int j = 0 ; j < sizeCol ; j++){
            delete this->inventoryContainer[i][j];
        }
    }
}

// getSlotInventory
SlotInventory* Inventory::getSlotInventory(string id) {
    int convertedId = convertIdToInt(id);
    int row = getRowInv(convertedId);
    int col = getColInv(convertedId);
    return this->inventoryContainer[row][col];
}

// containItem
bool Inventory::containItem(Item* item) {
    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeCol; j++) {
            Item* temp = this->inventoryContainer[i][j]->getItemInfo();
            if (temp->getName() == item->getName() && this->inventoryContainer[i][j]->getQuantity() < 64) {
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
                Item* temp = this->inventoryContainer[i][j]->getItemInfo();
                if ((this->inventoryContainer[i][j]->getQuantity() == 0) && (!(containItem(item)))) {
                    this->inventoryContainer[i][j] = new SlotInventory(item, quantity, slotId); // Menyimpan item di slot baru
                    quantity = 0;
                } else if (temp->getName() == item->getName()) {
                    if (temp->getCategory() == "TOOL") {
                        if (this->inventoryContainer[i][j]->getQuantity() + quantity <= 64) {
                            this->inventoryContainer[i][j]->addItemToSlot(item, quantity);
                            quantity = 0;
                        } else {
                            int quantityLeft = this->inventoryContainer[i][j]->getQuantity() + quantity;
                            quantityLeft -= 64;
                            quantity -= quantityLeft;
                            this->inventoryContainer[i][j]->addItemToSlot(item, quantity);
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
            Item* temp = this->inventoryContainer[i][j]->getItemInfo();
            if (this->inventoryContainer[i][j]->getSlotId() == slotId) {
                if (temp->getCategory() == "NONTOOL") {
                    if (this->inventoryContainer[i][j]->getQuantity() >= quantity) {
                        this->inventoryContainer[i][j]->removeItem(quantity);
                        if (this->inventoryContainer[i][j]->getQuantity() <= 0) {
                            this->inventoryContainer[i][j] = new SlotInventory();
                        }
                    } else {
                        EmptyException* err = new EmptyException();
                        throw err;
                    }
                }
            }
        }
    }
}

// moveItem
void Inventory::moveItem(string idSrc, string idDest) {
    int rowSrc = getRowInv(convertIdToInt(idSrc));
    int colSrc = getColInv(convertIdToInt(idSrc));
    int rowDest = getRowInv(convertIdToInt(idDest));
    int colDest = getColInv(convertIdToInt(idDest));
    if ((this->inventoryContainer[rowSrc][colSrc]->getNameFromSlotItem() == this->inventoryContainer[rowDest][colDest]->getNameFromSlotItem()) && (this->inventoryContainer[rowSrc][colSrc]->getCategoryFromSlotItem() == this->inventoryContainer[rowDest][colDest]->getCategoryFromSlotItem()) && ((this->inventoryContainer[rowSrc][colSrc]->getItemInfo())->isA<NonTool>()) && ((this->inventoryContainer[rowDest][colDest]->getItemInfo())->isA<NonTool>())) {
        // Move
        int quantityToMove;
        if (this->inventoryContainer[rowSrc][colSrc]->getQuantity() <= this->inventoryContainer[rowDest][colDest]->getEmptyQuantity()) {
            // Move seluruh item dari origin slot ke destination slot
            quantityToMove = this->inventoryContainer[rowSrc][colSrc]->getQuantity();
        } else {
            // Move sebagian item, yakni sejumlah sisa kapasitas destination slot yang ada
            quantityToMove = this->inventoryContainer[rowDest][colDest]->getEmptyQuantity();
        }
        // Add
        this->inventoryContainer[rowDest][colDest]->addItemToSlot(this->inventoryContainer[rowSrc][colSrc]->getItemInfo(), quantityToMove);
        // Remove
        this->inventoryContainer[rowSrc][colSrc]->removeItem(quantityToMove);
    } else {
        DifferentItemException* err = new DifferentItemException();
        throw err;
    }
}

// moveToCrafting
void Inventory::moveToCrafting(string slotIdInventory, int N, string* slotIdCrafting, CraftingTable table) {
    int rowInventory = getRowInv(convertIdToInt(slotIdInventory));
    int colInventory = getColInv(convertIdToInt(slotIdInventory)); 
    int rowCrafting, colCrafting;
    int idx = N;
    if (this->inventoryContainer[rowInventory][colInventory]->getQuantity() >= N) {
        if (N < 9) {
            for (int i = N - 1; i >= 0; i--) {
                idx--;
                rowCrafting = getRowCraft(convertIdToInt(slotIdCrafting[idx]));
                colCrafting = getColCraft(convertIdToInt(slotIdCrafting[idx]));
                // Add item to crafting
                table.setItem(this->inventoryContainer[rowInventory][colInventory]->getItemInfo(), rowCrafting, colCrafting);
            }
            // Remove item from inventory
            this->inventoryContainer[rowInventory][colInventory]->removeItem(N);
        }
    }
}

// showInventory
void Inventory::showInventory() {
    int slotId = 0;
    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeCol; j++) {
            Item* temp = this->inventoryContainer[i][j]->getItemInfo();
            cout << this->inventoryContainer[i][j]->getQuantity() << endl;
            cout << "Item" << temp->getQty() << endl;

            if (this->inventoryContainer[i][j]->getQuantity() == 0) {
                cout << "[ I " << slotId << " ] ";
            } else if (temp->getCategory() == "NONTOOL") {                
                cout << "[ " << temp->getName() << "," << this->inventoryContainer[i][j]->getQuantity() << " ] ";
            } else {
                cout << "[ " << temp->getName() << "," << temp->getDura() << " ] ";
            }
            slotId++;
        }
        cout << endl;
    }
}

// exportInventory
void Inventory::exportInventory(string outputPath) {
    ofstream outputFile(outputPath);
    for (int i = 0; i < sizeRow; i++) {
        for (int j = 0; j < sizeCol; j++) {
            Item* temp = this->inventoryContainer[i][j]->getItemInfo();
            if (temp->getCategory() == "NONTOOL") {
                outputFile << temp->getId() << ":" << this->inventoryContainer[i][j]->getQuantity() << endl;
            } else {
                Tool* t = dynamic_cast<Tool*>(temp);
                outputFile << t->getId() << ":" << t->getDura() << endl;
            }
        }
    }
}


void Inventory::moveToInventory(CraftingTable table, string slotIdCrafting, string slotIdInventory) {
    int rowCrafting = getRowCraft(convertIdToInt(slotIdCrafting));
    int colCrafting = getColCraft(convertIdToInt(slotIdCrafting));
    int rowInventory = getRowInv(convertIdToInt(slotIdInventory));
    int colInventory = getColInv(convertIdToInt(slotIdInventory));
    Item* temp = table.getItem(rowCrafting, colCrafting);
    // Possible cases:
    // 1. Slot pada CraftingTable kosong -> tidak ada item yang bisa di-move
    if (temp->getId() == 0) {
        cout << "There is no item in slot " << slotIdCrafting << " in crafting table." << endl;
    } else {
        SlotInventory* inventoryContainer = this->getSlotInventory(slotIdInventory);
        // 2. Slot pada inventory yang dituju masih kosong -> bisa move item
        if (inventoryContainer->getQuantity() == 0) {
            inventoryContainer->addItemToSlot(temp, 1);
            table.setItem(new NonTool(), rowCrafting, colCrafting);
        } else {
            bool sameName = inventoryContainer->getNameFromSlotItem() == temp->getName();
            // 3. Slot pada inventory yang dituju telah terisi item yang sama
            if (sameName) {
                // Cek jenis item: Tool -> tidak bisa ditumpuk, NonTool -> lakukan move item
                if (temp->getCategory() == "TOOL") {
                    cout << "Item can't be moved since Tool can't be stacked." << endl;
                } else {
                    if (inventoryContainer->getEmptyQuantity() >= 1) {
                        inventoryContainer->addItemToSlot(temp, 1);
                    } else {
                        cout << "Slot " << slotIdInventory << " is full." << endl;
                    }
                }
            // 4. Slot pada inventory yang dituju telah terisi item yang berbeda -> tidak bisa move item
            } else {
                DifferentItemException* err = new DifferentItemException();
                throw err;
            }
        }
    }
}