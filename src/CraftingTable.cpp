#include "../header/CraftingTable.hpp"

CraftingTable::CraftingTable() {
    this->table = vector<vector<Item>>(3, vector<Item>(3));
}

CraftingTable::CraftingTable(vector<vector<Item>> table) {
    this->table = table;
}

Item& CraftingTable::getItem(int row, int col) {
    return this->table[row][col];
}

void CraftingTable::printTable() {
    // TODO: Search for pretty table libs
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << this->table[i][j].getId() << " ";
        }
        cout << endl;
    }
}

