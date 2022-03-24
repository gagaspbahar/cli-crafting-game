#include "../header/CraftingTable.hpp"

using namespace std;

CraftingTable::CraftingTable() {
	vector<vector<Item*>> table;
	for (int i = 0; i < 3; i++) {
		vector<Item*> row;
		for (int j = 0; j < 3; j++) {
			Item* item = new NonTool();
			row.push_back(item);
		}
		table.push_back(row);
	}
	this->table = table;
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

void CraftingTable::delItem(int row, int col){
	this->table[row][col] = new NonTool();
}

CraftingTable CraftingTable::mirrorTable() {
	/* I.S. : Crafting table terdefinisi */
	/* F.S. : Crafting table yang diciptakan adalah mirror dari table yang sudah ada terhadap sumbu-y*/
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

vector<string> CraftingTable::getTypeOnTable() {
	/* I.S. : Crafting Table terdefinisi */
	/* F.S. : Mengembalikan vector<string> yang berisi nama item yang ada di table */
	vector<string> itemOnTable;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (this->table[i][j]->getId() != 0) {
				if(this->table[i][j]->getType() == "-"){
					itemOnTable.push_back(this->table[i][j]->getName());
				}
				else{
					itemOnTable.push_back(this->table[i][j]->getType());
				}
			}
		}
	}
	sort(itemOnTable.begin(), itemOnTable.end());
	return itemOnTable;
}

vector<string> CraftingTable::getNameOnTable() {
	/* I.S. : Crafting Table terdefinisi */
	/* F.S. : Mengembalikan vector<string> yang berisi nama item yang ada di table */
	vector<string> itemOnTable;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (this->table[i][j]->getId() != 0) {
				itemOnTable.push_back(this->table[i][j]->getName());
			}
		}
	}
	sort(itemOnTable.begin(), itemOnTable.end());
	return itemOnTable;
}

vector<Item*> CraftingTable::getToolOnTable() {
	/* I.S. : Crafting Table terdefinisi */
	/* F.S. : Mengembalikan vector<string> yang berisi nama item yang ada di table */
	vector<Item*> itemOnTable;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (this->table[i][j]->getId() != 0) {
				itemOnTable.push_back(getItem(i, j));
			}
		}
	}
	sort(itemOnTable.begin(), itemOnTable.end());
	return itemOnTable;
}

bool CraftingTable::isAllTool(){
	bool status = true;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if(this->table[i][j]->getId() != 0 && this->table[i][j]->getCategory() != "TOOL"){
				status = false;
				return status;
			}
		}
	}
	return status;
}

bool CraftingTable::isAllNonTool(){
	bool status = true;
	for (int i = 0; i < 3 && status; i++) {
		for (int j = 0; j < 3 && status; j++) {
			status = (this->table[i][j]->getId() == 0) || (this->table[i][j]->getCategory() == "NONTOOL");
		}
	}
	return status;
}

bool CraftingTable::isTwoTool(){
	int count = 0;
	for (int i = 0; i < 3 && count <= 2; i++) {
		for (int j = 0; j < 3 && count <= 2; j++) {
			count += this->table[i][j]->getId() != 0;
		}
	}
	return count == 2;
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
	return submatrices;
}

bool CraftingTable::isCompositionValid(Config config, string name) {
	/* I.S. : Config terdefinisi, name terdefinisi */
	/* F.S. : Mengembalikan true jika jumlah dan jenis bahan yang dibutuhkan untuk membuat item tersebut sesuai dengan resep*/
	vector<string> ingredients = config.getRecipe().getRecipeComponents(name);
	vector<string> typeOnTable = getTypeOnTable();
	vector<string> nameOnTable = getNameOnTable();
	
	if (typeOnTable.size() < ingredients.size()) {
		return false;
	}

	// Check by name
	bool statusName = true, statusType = true;
	for(int i = 0 ; i < ingredients.size() && (statusName || statusType) ; i++){
		statusName = ingredients[i] == nameOnTable[i];
		statusType = ingredients[i] == typeOnTable[i];
	}

	return statusName || statusType;
}

// TODO
bool CraftingTable::isPatternValid(Config config, string item){
	/* I.S. : Config terdefinisi, item terdefinisi */
	/* F.S. : Mengembalikan true jika pattern yang dibutuhkan untuk membuat item tersebut sesuai dengan resep*/
	vector<vector<string>> pattern = config.getRecipe().getRecipePattern(item);
	vector<vector<vector<Item*>>> submatrices = this->getSubmatrices(pattern[0].size(), pattern.size());
	vector<vector<vector<Item*>>> mirrorSubmatrices = this->mirrorTable().getSubmatrices(pattern[0].size(), 														   pattern.size());
	
	// Original table
	for (int i = 0; i < submatrices.size(); i++) {
		bool patternStatus = true;
		bool patternStatusMirorred = true;
		for (int j = 0; j < pattern.size() && (patternStatus||patternStatusMirorred); j++) {
			for (int k = 0; k < pattern[j].size() && (patternStatus||patternStatusMirorred); k++) {
				patternStatus = (pattern[j][k] == submatrices[i][j][k]->getName()) 		||
								(pattern[j][k] == submatrices[i][j][k]->getType()) || 
								(pattern[j][k] == "-" && submatrices[i][j][k]->getId() == 0);
				patternStatusMirorred = (pattern[j][k] == mirrorSubmatrices[i][j][k]->getName()) 		||
										(pattern[j][k] == mirrorSubmatrices[i][j][k]->getType()) || 
										(pattern[j][k] == "-" && mirrorSubmatrices[i][j][k]->getId() == 0);
			}
		}
		if (patternStatus || patternStatusMirorred) {
			return true;
		}
	}
	return false;
}

Item* CraftingTable::craft(Config config){
	cout << "fungsi" << endl;
	if(isAllTool() && isTwoTool()){
		vector<Item*> itemOnTable = getToolOnTable();
		int newDura = itemOnTable[0]->getDura() + itemOnTable[1]->getDura();
		if (newDura > 10){
			newDura = 10;
		}
		Item* item = new Tool(itemOnTable[0]->getId(),itemOnTable[0]->getName(), newDura);
		return item;
	}
	if(this->isAllNonTool()){
		Recipe recipe = config.getRecipe();
		for (int i=0; i< config.getItemList().size(); i++){
			cout << i << endl;
			if(isCompositionValid(config, config.getItemList()[i].name)){
				cout << "comp" << endl;
				if(isPatternValid(config, config.getItemList()[i].name)){
					cout << "pattern" << endl;
					// NGUMPULIN QTY BAHAN2 DI MEJA DIAMOND SWORD [ DIAMOND 2 , DIAMOND 2 , KAYU 1]
					// [ DIAMOND 1 , DIAMOND 1 , KAYU 1] -> min(2/1, 2/1, 1/1)
					int count = 64;
					for(int j=0; j<3; j++){
						for(int k=0; k<3; k++){
							if(this->table[j][k] != 0){
								if(count > this->table[i][j]->getQty()){
									count = this->table[i][j]->getQty();
								}
							}
						}
					}

					// Clean Up Crafting Table
					for(int j=0; j < 3 ; j++){
						for(int k =0; k<3 ; k++){
							if(this->table[j][k]->getId() != 0){
								this->table[j][k]->setQty(this->table[j][k]->getQty() - count);
								if(this->table[j][k]->getQty() == 0){
									this->table[j][k] = new NonTool();
								}
							}
						}
					}
					return new NonTool(config.getItemList()[i].id, config.getItemList()[i].name, config.getItemList()[i].parentClass, count*recipe.getQty(config.getItemList()[i].name));
				}
			}
		}
	}
	cout << "gamasuk apa apa jir" << endl;
	return new NonTool();
}

void CraftingTable::printTable() {
    // Get Max ItemName length
	int mw = 3; // c/: C 8
	for(int i = 0 ; i < 3; i++){
		for(int j = 0 ; j < 3 ;j++){
			int tempLength = this->table[i][j]->getName().length() + 2;
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
	int slotId = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			// Kasus Slot Kosong
			int ws;
			cout << "|";
			if (this->table[i][j]->getId() == 0){
				ws = 3;
                for(int space = 0 ; space < (mw - ws)/2 ; space++){
                    cout << " ";
                }
                cout << "C " << slotId;
                for(int space = 0 ; space < (mw - ws)/2 + (ws%2 != 0); space++){
                    cout << " ";
                }
			}
			// Kasus Slot Tidak Kosong
			else {
				ws = this->table[i][j]->getName().length();
				for(int space = 0 ; space < (mw - ws)/2 ; space++){
					cout << " ";
				} 
				cout << this->table[i][j]->getName() << " ";
				if (this->table[i][j]->getCategory() == "NONTOOL"){
                    cout << this->table[i][j]->getQty();
                } 
                // Kasus Tool (print quantity)
                else {
                    cout << this->table[i][j]->getDura();
                }
				for(int space = 0 ; space < (mw - ws)/2 + (ws%2 != 0); space++){
					cout << " ";
				} 
			}
			slotId++;
		}
		cout << "|" << endl;
		for(int line = 0 ; line < mw*3 + 4 ; line++){
			cout << "-";
		}
		cout << endl;
	}
}

