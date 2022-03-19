#ifndef CRAFTINGTABLE_H
#define CRAFTINGTABLE_H

#include <vector>
#include "Item.hpp"

class CraftingTable {
    private:
        vector<vector<Item>> table;
    public:
        CraftingTable();
        CraftingTable(vector<vector<Item>> table);
        Item& getItem(int row, int col);
        void printTable();
};

#endif