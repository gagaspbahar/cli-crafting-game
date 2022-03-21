#ifndef CRAFTINGTABLE_H
#define CRAFTINGTABLE_H

#include <vector>
#include "Config.hpp"
#include "Item.hpp"

class CraftingTable {
    private:
        vector<vector<Item*>> table;
    public:
        CraftingTable();
        CraftingTable(vector<vector<Item*>>);
        Item* getItem(int, int);
        void setItem(Item*, int, int);
        CraftingTable mirrorTable();
        void printTable();
};

#endif