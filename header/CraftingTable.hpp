#ifndef CRAFTINGTABLE_H
#define CRAFTINGTABLE_H

#include <vector>
#include "Config.hpp"
#include "Item.hpp"
#include "Tool.hpp"
#include "Nontool.hpp"

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
        vector<string> getNonToolOnTable();
        vector<Item*> getToolOnTable();
        bool isAllTool();
        bool isAllNonTool();
        bool isTwoTool();
        bool isCompositionValid(Config,string);
        bool isPatternValid(Config,string);
        vector<vector<vector<Item*>>> getSubmatrices(int, int);
        Item* craft(Config);
        void printTable();
};

#endif