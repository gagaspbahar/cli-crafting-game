#ifndef CRAFTINGTABLE_H
#define CRAFTINGTABLE_H

#include <vector>
#include "Config.hpp"

class CraftingTable {
    private:
        vector<vector<ItemConfig>> table;
    public:
        CraftingTable();
        CraftingTable(vector<vector<ItemConfig>>);
        ItemConfig getItem(int, int);
        void setItem(ItemConfig, int, int);
        void delItem(int,int);
        CraftingTable mirrorTable();
        vector<ItemConfig> getItemOnTable();
        bool isCompositionValid(Config,string);
        bool isPatternValid(Config,string);
        vector<vector<vector<ItemConfig>>> getSubmatrices(int, int);
        void printTable();
};

#endif