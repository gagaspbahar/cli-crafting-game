#ifndef CRAFTINGTABLE_H
#define CRAFTINGTABLE_H

#include <vector>
#include "Config.hpp"

class CraftingTable {
    private:
        vector<vector<int>> table;
    public:
        CraftingTable();
        CraftingTable(vector<vector<int>>);
        int getItem(int, int);
        void setItem(Item*, int, int);
        CraftingTable mirrorTable();
        void printTable(Config);
};

#endif