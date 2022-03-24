#ifndef _INVENTORY_HPP_
#define _INVENTORY_HPP_

#include <iostream>
#include <ostream>
#include <string>
#include <cmath>
#include "Exception.hpp"
#include "CraftingTable.hpp"
#define ROW 3
#define COL 9

using namespace std;

int convertIdToInt(string id);
int getRowInv(int integer);
int getColInv(int integer);
int getRowCraft(int integer);

class Inventory {
    protected:
        Item* buffer[ROW][COL];
    public:
        Inventory();
        //Inventory(const Inventory& inventory);
        Inventory& operator=(const Inventory& inventory);
        ~Inventory();

        // Getter
        Item* getItemFromSlot(string id);

        // Give & Discard
        bool containSpecificItem(Item* item, int row, int col);
        int givePossibleSlot(Item* item);
        void giveItem(Item* item, int quantity);
        void discardItem(string slot_id, int quantity);

        // Move
        void invToInv(string idSrc, string idDest);
        
        void invToCrafting(string slotIdInventory, int N, vector<string> slotIdCrafting, CraftingTable* table);
        void singleInvToCrafting(string slotIdInventory, string slotIdCrafting, CraftingTable* table);

        void craftingToInv(CraftingTable* table, string slotIdCrafting, string slotIdInventory);
       
        // Show
        void showInventory();

        // Export
        void exportInventory(string outputPath);

        bool isSlotIdValid(int id);

};

#endif