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
    // Get Max ItemName length
	int mw = 0;
	for(int i = 0 ; i < 3; i++){
		for(int j = 0 ; j < 3 ;j++){
			if (this->table[i][j].getName().length() > mw){
				mw = this->table[i][j].getName().length();
			}
		}
	}

    //Print crafting table
	for(int line = 0 ; line < mw*3 + 4 ; line++){
		cout << "-";
	}
	cout << endl;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			int ws = this->table[i][j].getName().length();
			cout << "|";
			for(int space = 0 ; space < (mw - ws)/2 ; space++){
				cout << " ";
			} 
			cout << this->table[i][j].getName();
			for(int space = 0 ; space < (mw - ws)/2 + (ws%2 != 0); space++){
				cout << " ";
			} 
		}
		cout << "|" << endl;
		for(int line = 0 ; line < mw*3+4 ; line++){
			cout << "-";
		}
		cout << endl;
	}
}

