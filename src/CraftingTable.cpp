#include "../header/CraftingTable.hpp"

CraftingTable::CraftingTable() {
    this->table = vector<vector<int>>(3, vector<int>(3));
}

CraftingTable::CraftingTable(vector<vector<int>> table) {
    this->table = table;
}

int CraftingTable::getItem(int row, int col) {
    return this->table[row][col];
}

void CraftingTable::setItem(Item* item, int row, int col) {
	this->table[row][col] = item;
}

CraftingTable CraftingTable::mirrorTable() {
	vector<vector<int>> mTable;
	for (int i = 0; i < 3; i++) {
		vector<int> mRow;
		for (int j = 2; j >= 0; j--) {
			mRow.push_back(this->table[i][j]);
		}
		mTable.push_back(mRow);
	}
	return CraftingTable(mTable);
}

void CraftingTable::printTable(Config config) {
    // Get Max ItemName length
	int mw = 0;
	for(int i = 0 ; i < 3; i++){
		for(int j = 0 ; j < 3 ;j++){
			int tempLength = config.getNameFromID(this->table[i][j]).length();
			if (tempLength > mw){
				mw = tempLength;
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
			int ws = config.getNameFromID(this->table[i][j]).length();
			cout << "|";
			for(int space = 0 ; space < (mw - ws)/2 ; space++){
				cout << " ";
			} 
			cout << config.getNameFromID(this->table[i][j]).length();
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

