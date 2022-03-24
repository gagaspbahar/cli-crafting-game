#ifndef CRAFTINGTABLE_H
#define CRAFTINGTABLE_H

#include <vector>
#include "Config.hpp"
#include "Item.hpp"
#include "Tool.hpp"
#include "Nontool.hpp"
#include "Inventory.hpp"
#include "InventoryException.hpp"

int getRowCraft(int integer);
int getColCraft(int integer);

class CraftingTable {
    private:
        vector<vector<Item*>> table;
    public:
        CraftingTable();
        CraftingTable(vector<vector<Item*>>);
        Item* getItem(int, int);
        void setItem(Item*, int, int);
        void delItem(int,int);
        CraftingTable mirrorTable();
        vector<string> getTypeOnTable();
        vector<string> getNameOnTable();
        vector<Item*> getToolOnTable();
        bool isAllTool();
        bool isAllNonTool();
        bool isTwoTool();
        bool isCompositionValid(Config,string);
        bool isPatternValid(Config,string);
        vector<vector<vector<Item*>>> getSubmatrices(int, int);
        Item* craft(Config);
        void moveToInventory(Inventory&, string, string);
        void printTable();
};

#endif