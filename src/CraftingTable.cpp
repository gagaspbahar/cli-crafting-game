#include "../header/CraftingTable.hpp"

CraftingTable::CraftingTable() {
    this->table = vector<vector<Item*>>(3, vector<Item*>(3));
}

CraftingTable::CraftingTable(vector<vector<Item*>> table) {
    this->table = table;
}

Item* CraftingTable::getItem(int row, int col) {
    return this->table[row][col];
}

void CraftingTable::setItem(Item* item, int row, int col) {
	this->table[row][col] = item;
}

CraftingTable CraftingTable::mirrorTable() {
	vector<vector<Item*>> mTable;
	for (int i = 0; i < 3; i++) {
		vector<Item*> mRow;
		for (int j = 2; j >= 0; j--) {
			mRow.push_back(this->table[i][j]);
		}
		mTable.push_back(mRow);
	}
	return CraftingTable(mTable);
}

vector<vector<vector<Item*>> > CraftingTable::getSubmatrices(int w, int h) {
	vector<vector<vector<Item*>>> submatrices;
	for (int i = 0 ; i < 4 - h ; i++){
		for(int j = 0 ; j < 4 - w ; j++){
			vector<vector<Item*>> submatrix;
			for(int k = i ; k < i+h ; k++){
				vector<Item*> subrow;
				for(int l = j ; l < j+w ; l++){
					subrow.push_back(this->table[k][l]);
				}
				submatrix.push_back(subrow);
			}
			submatrices.push_back(submatrix);
		}
	}
}

void CraftingTable::printTable() {
    // Get Max ItemName length
	int mw = 0;
	for(int i = 0 ; i < 3; i++){
		for(int j = 0 ; j < 3 ;j++){
			int tempLength = this->table[i][j]->getName().length();
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
			int ws = this->table[i][j]->getName().length();
			cout << "|";
			for(int space = 0 ; space < (mw - ws)/2 ; space++){
				cout << " ";
			} 
			cout << this->table[i][j]->getName();
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

