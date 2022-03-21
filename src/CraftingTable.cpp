#include "../header/CraftingTable.hpp"

int getRowCraft(int integer) {
    return (int)(integer / 3);
}

int getColCraft(int integer) {
    return (integer % 3);
}

CraftingTable::CraftingTable() {
	vector<vector<ItemConfig>> table;
	for (int i = 0; i < 3; i++) {
		vector<ItemConfig> row;
		for (int j = 0; j < 3; j++) {
			row.push_back(ItemConfig{-1,"","",""});
		}
		table.push_back(row);
	}
	this->table = table;
}

CraftingTable::CraftingTable(vector<vector<ItemConfig>> table) {
    this->table = table;
}

ItemConfig CraftingTable::getItem(int row, int col) {
    return this->table[row][col];
}

void CraftingTable::setItem(ItemConfig item, int row, int col) {
	this->table[row][col] = item;
}

void CraftingTable::delItem(int row, int col){
	this->table[row][col] = ItemConfig{-1,"","",""};
}

CraftingTable CraftingTable::mirrorTable() {
	/* I.S. : Crafting table terdefinisi */
	/* F.S. : Crafting table yang diciptakan adalah mirror dari table yang sudah ada terhadap sumbu-y*/
	vector<vector<ItemConfig>> mTable;
	for (int i = 0; i < 3; i++) {
		vector<ItemConfig> mRow;
		for (int j = 2; j >= 0; j--) {
			mRow.push_back(this->table[i][j]);
		}
		mTable.push_back(mRow);
	}
	return CraftingTable(mTable);
}

vector<ItemConfig> CraftingTable::getItemOnTable() {
	/* I.S. : Crafting Table terdefinisi */
	/* F.S. : Mengembalikan vector<string> yang berisi nama item yang ada di table */
	vector<ItemConfig> itemOnTable;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (this->table[i][j].id != -1) {
				itemOnTable.push_back(getItem(i, j));
			}
		}
	}
	sort(itemOnTable.begin(), itemOnTable.end());
	return itemOnTable;
}

vector<vector<vector<ItemConfig>> > CraftingTable::getSubmatrices(int w, int h) {
	vector<vector<vector<ItemConfig>>> submatrices;
	for (int i = 0 ; i < 4 - h ; i++){
		for(int j = 0 ; j < 4 - w ; j++){
			vector<vector<ItemConfig>> submatrix;
			for(int k = i ; k < i+h ; k++){
				vector<ItemConfig> subrow;
				for(int l = j ; l < j+w ; l++){
					subrow.push_back(this->table[k][l]);
				}
				submatrix.push_back(subrow);
			}
			submatrices.push_back(submatrix);
		}
	}
}

bool CraftingTable::isCompositionValid(Config config, string name) {
	/* I.S. : Config terdefinisi, name terdefinisi */
	/* F.S. : Mengembalikan true jika jumlah dan jenis bahan yang dibutuhkan untuk membuat item tersebut sesuai dengan resep*/
	vector<string> ingredients = config.getRecipe().getRecipeComponents(name);
	vector<ItemConfig> itemOnTable = getItemOnTable();
	
	if (itemOnTable.size() < ingredients.size()) {
		return false;
	}

	// Check by name
	bool nameStatus = true, typeStatus = true;
	for(int i = 0 ; i < ingredients.size() && (nameStatus || typeStatus) ; i++){
		nameStatus = ingredients[i] == itemOnTable[i].name;
		typeStatus = ingredients[i] == itemOnTable[i].parentClass;
	}

	return nameStatus || typeStatus;
}

bool CraftingTable::isPatternValid(Config config, string item){
	/* I.S. : Config terdefinisi, item terdefinisi */
	/* F.S. : Mengembalikan true jika pattern yang dibutuhkan untuk membuat item tersebut sesuai dengan resep*/
	vector<vector<string>> pattern = config.getRecipe().getRecipePattern(item);
	vector<vector<vector<ItemConfig>>> submatrices = this->getSubmatrices(pattern[0].size(), pattern.size());
	vector<vector<vector<ItemConfig>>> mirrorSubmatrices = this->mirrorTable().getSubmatrices(pattern[0].size(), 														   pattern.size());
	
	// Original table
	for (int i = 0; i < submatrices.size(); i++) {
		bool patternStatus = true;
		bool patternStatusMirorred = true;
		for (int j = 0; j < pattern.size() && (patternStatus||patternStatusMirorred); j++) {
			for (int k = 0; k < pattern[j].size() && (patternStatus||patternStatusMirorred); k++) {
				patternStatus = (pattern[j][k] == submatrices[i][j][k].name) 		||
								(pattern[j][k] == submatrices[i][j][k].parentClass) || 
								(pattern[j][k] == "-" && submatrices[i][j][k].id == -1);
				patternStatusMirorred = (pattern[j][k] == mirrorSubmatrices[i][j][k].name) 		||
										(pattern[j][k] == mirrorSubmatrices[i][j][k].parentClass) || 
										(pattern[j][k] == "-" && mirrorSubmatrices[i][j][k].id == -1);
			}
		}
		if (patternStatus || patternStatusMirorred) {
			return true;
		}
	}
	return false;
}

void CraftingTable::printTable() {
    // Get Max ItemName length
	int mw = 0;
	for(int i = 0 ; i < 3; i++){
		for(int j = 0 ; j < 3 ;j++){
			int tempLength = this->table[i][j].name.length();
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
			int ws = this->table[i][j].name.length();
			cout << "|";
			for(int space = 0 ; space < (mw - ws)/2 ; space++){
				cout << " ";
			} 
			cout << this->table[i][j].name;
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

