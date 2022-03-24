#ifndef _INVENTORY_HPP_
#define _INVENTORY_HPP_

#include <iostream>
#include <ostream>
#include <string>
#include "SlotInventory.hpp"
#include "InventoryException.hpp"
#include "CraftingTable.hpp"
using namespace std;

int convertIdToInt(string id);
int getRowInv(int integer);
int getColInv(int integer);
int getRowCraft(int integer);

class Inventory {
    protected:
        vector<vector<SlotInventory>> inventoryContainer;
        const int sizeRow = 3;
        const int sizeCol = 9;
        int quantity;
    public:
        Inventory();
        Inventory(const Inventory& inventory);
        Inventory& operator=(const Inventory& inventory);
        virtual ~Inventory();

        // Getter
        SlotInventory getSlotInventory(string id);

        // Give & Discard
        bool containItem(Item* item);
        void giveItem(Item* item, int quantity);
        void discardItem(string id, int quantity);

        // Move
        void moveItem(string idSrc, string idDest);
        void moveToCrafting(string slotIdInventory, int N, string* slotIdCrafting, CraftingTable table);
        void moveToInventory(CraftingTable table, string slotIdCrafting, string slotIdInventory);
       
        // Show
        void showInventory();

        // Export
        void exportInventory(string outputPath);

};

#endif