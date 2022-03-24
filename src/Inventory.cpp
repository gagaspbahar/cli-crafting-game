#include "../header/Inventory.hpp"

Inventory::Inventory(){
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            this->buffer[i][j] = new NonTool();
        }
    }
}

// // Inventory::Inventory(const Inventory& inventory){
// //     for(int i = 0; i < ROW; i++){
// //         for(int j = 0; j < COL; j++){
// //             this->buffer[i][j] = inventory.buffer[i][j];
// //         }
// //     }
// // }
// Inventory::Inventory& operator=(const Inventory& inventory){
//     for(int i = 0; i < ROW; i++){
//         for(int j = 0; j < COL; j++){
//             this->buffer[i][j] = inventory->buffer[i][j];
//         }
//     }
//     return *this;
// }

Inventory::~Inventory(){
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            delete this->buffer[i][j];
        }
    }
}

int getRowInv(int integer) {
    return (int)(integer / 9);
}

int getColInv(int integer) {
    return (integer % 9);
}

int getRowCraft(int integer) {
    return (int)(integer / 3);
}

int getColCraft(int integer) {
    return (integer % 3);
}

int convertIdToInt(string id) {
    string s = id.substr(1);
    return stoi(s);
}

// Getter
Item* Inventory::getItemFromSlot(string id){
    int newId = convertIdToInt(id);
    return this->buffer[getRowInv(newId)][getColInv(newId)];
}

// Give & Discard
bool Inventory::containSpecificItem(Item* item, int row, int col){
    return (this->buffer[row][col]->getId() == item->getId());
}


int Inventory::givePossibleSlot(Item* item){
    // check untuk item yg sama di inven, kalo tool gausah nyari yang udah ada
    if(item->getCategory() == "NONTOOL"){
      for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
          if(containSpecificItem(item, i, j) && this->buffer[i][j]->getQty() != 64){
            return i*9 + j;
          }
        }
      }
    }

    // case item blm ada
    for(int i = 0; i < ROW; i++){
      for(int j = 0; j < COL; j++){
        if(this->buffer[i][j]->getId() == 0){
          return i*9 + j;
        }
      }
    }
    return -1;
}

void Inventory::giveItem(Item* item, int q){
    // Check available slot
    int slot = givePossibleSlot(item);
    int slotRow;
    int slotCol;
    int quantity = q;
    if(quantity == 0){
      // do nothing
    }
    else{
      while(quantity > 0 && slot != -1){
        slotRow = getRowInv(slot);
        slotCol = getColInv(slot);
        if(this->buffer[slotRow][slotCol]->getId() == 0){
            //NONTOOL KOTAK KOSONG
            if(item->getCategory() == "NONTOOL"){
                if(quantity < 64){
                    this->buffer[slotRow][slotCol] = new NonTool(item->getId() , item->getName(), item->getType() , quantity);
                    quantity = 0;
                }
                else{
                    this->buffer[slotRow][slotCol] = new NonTool(item->getId() , item->getName(), item->getType() , 64);
                    quantity -= 64;
                }
            }
            //TOOL KOTAK KOSONG
            else{
                this->buffer[slotRow][slotCol] = new Tool(item->getId() , item->getName(), 10);
                quantity -=1;
            }
        }
        
        // BUKAN KOTAK KOSONG (HANYA MUNGKIN NONTOOL)
        else{
            int currQty = this->buffer[slotRow][slotCol]->getQty();
            int toAdd = (quantity + currQty > 64 ? 64 - currQty : quantity);
            this->buffer[slotRow][slotCol]->setQty(currQty+toAdd);
            quantity -= toAdd;
        }

        //check next slot possibility
        slot = givePossibleSlot(item);
      }
    }
}

void Inventory::discardItem(string slot_id, int quantity){
    int newId = convertIdToInt(slot_id);
    Item* temp = this->buffer[getRowInv(newId)][getColInv(newId)];
    if(temp->getCategory() == "NONTOOL"){
        if(temp->getQty() > quantity){
            temp->setQty(temp->getQty() - quantity);
        } else{
            // erase to item sampah
            this->buffer[getRowInv(newId)][getColInv(newId)] = new NonTool();
        }
    }else{
        // erase to item sampah
        this->buffer[getRowInv(newId)][getColInv(newId)] = new NonTool();
    }
}

bool Inventory::isSlotIdValid(int id){
  return id >= 0 && id <= 26;
}

// Move
void Inventory::invToInv(string idSrc, string idDest){
  
  // I.S. :
    // 1. Jumlah Item pada INVENTORY_SLOT_ID_SRC sebanyak Qty1.
    // 2. Jumlah Item pada INVENTORY_SLOT_ID_DEST sebanyak Qty2.
  // F.S. :
    // 1. Jumlah Item pada INVENTORY_SLOT_ID_SRC sebanyak 0 (item
    // hilang / habis), jika memungkinkan.
    // 2. Jumlah Jumlah Item pada INVENTORY_SLOT_ID_DEST sebanyak Qty1
    // + Qty2, namun maksimal sebanyak 64
  
  int srcSlot = convertIdToInt(idSrc);
  int destSlot = convertIdToInt(idDest);
  
  if(!isSlotIdValid(srcSlot) || !isSlotIdValid(destSlot)){
    cout << "Invalid slot input." << endl;
    cout << srcSlot << destSlot << endl;
    return;
  }

  int srcSlotRow = getRowInv(srcSlot);
  int srcSlotCol = getColInv(srcSlot);

  int destSlotRow = getRowInv(destSlot);
  int destSlotCol = getColInv(destSlot);
  

  // DARI KOSONG -> DO NOTHING
  if(this->buffer[srcSlotRow][srcSlotCol]->getId() == 0){
    // do nothing
  }
  // ISI KE KOSONG -> PINDAHIN
  else if(this->buffer[destSlotRow][destSlotCol]->getId() == 0){
      this->buffer[destSlotRow][destSlotCol] = this->buffer[srcSlotRow][srcSlotCol];
      this->buffer[srcSlotRow][srcSlotCol] = new NonTool();
  }
  else{
    bool idNonToolSama = this->buffer[srcSlotRow][srcSlotCol]->getId() == this->buffer[destSlotRow][destSlotCol]->getId() && this->buffer[srcSlotRow][srcSlotCol]->getCategory() == "NONTOOL";

    if(idNonToolSama){
      // ISI KE ISI DAN SAMA JENIS ITEM (NON TOOL) DAN CUKUP -> TUMPUK
      if(this->buffer[srcSlotRow][srcSlotCol]->getQty() + this->buffer[destSlotRow][destSlotCol]->getQty() <= 64){
        // new qty in dest
        this->buffer[destSlotRow][destSlotCol]->setQty(this->buffer[destSlotRow][destSlotCol]->getQty() + this->buffer[srcSlotRow][srcSlotCol]->getQty());
        // delete src
        this->buffer[srcSlotRow][srcSlotCol] = new NonTool();
      }
      // ISI KE ISI DAN GA CUKUP -> PINDAHIN SEBAGIAN
      else{
        // TIDAK CUKUP SLOT
        // gaada delete src
        this->buffer[srcSlotRow][srcSlotCol]->setQty(this->buffer[srcSlotRow][srcSlotCol]->getQty() - (64 - this->buffer[destSlotRow][destSlotCol]->getQty()));
        this->buffer[destSlotRow][destSlotCol]->setQty(64);
      }
    }

    // ISI KE ISI DAN BEDA OR TOOL -> DO NOTHING
    else{
      // Do nothing
    }
  }
}

void Inventory::singleInvToCrafting(string slotIdInventory, string slotIdCrafting, CraftingTable* table){
    int idInv = convertIdToInt(slotIdInventory);
    int rowInv = getRowInv(idInv) , colInv = getColInv(idInv);

    int idCraft = convertIdToInt(slotIdCrafting);
    int rowCraft = getRowCraft(idCraft) , colCraft = getColCraft(idCraft);

    // ISI KE KOSONG
    if(table->getItem(rowCraft,colCraft)->getId() == 0){
        if(this->buffer[rowInv][colInv]->getCategory() == "NONTOOL"){
            Item* nontool = new NonTool(this->buffer[rowInv][colInv]->getId(), this->buffer[rowInv][colInv]->getName(), this->buffer[rowInv][colInv]->getType(), 1);
            table->setItem(nontool, rowCraft, colCraft);
            discardItem(slotIdInventory,1);
        }
        else{
          Item* tool = new Tool(this->buffer[rowInv][colInv]->getId(), this->buffer[rowInv][colInv]->getName(), this->buffer[rowInv][colInv]->getDura());
          table->setItem(this->buffer[rowInv][colInv], rowCraft, colCraft);
          discardItem(slotIdInventory,1);
        }
    }
    // ISI KE ISI 
    else{
      // ISI KE ISI TAPI SALAH (BEDA) (TOLAK)
      if(this->buffer[rowInv][colInv]->getId() != table->getItem(rowCraft,colCraft)->getId()){
          cout << "Slot " << slotIdCrafting << " sudah terisi item " << table->getItem(rowCraft, colCraft)->getName() << endl;
      }
      // ISI KE ISI TAPI SAMA
      else{
        // NONTOOL TUMPUK
        if(this->buffer[rowInv][colInv]->getCategory() == "NONTOOL"){
            table->getItem(rowCraft, colCraft)->setQty(table->getItem(rowCraft, colCraft)->getQty() + 1);
            discardItem(slotIdInventory,1);
        }
        // TOOL GAGAL
        else{
          cout << "Slot " << slotIdCrafting << " sudah terisi item Tool berupa " << table->getItem(rowCraft, colCraft)->getName() << endl;
        }  
      }
    }
}

void Inventory::invToCrafting(string slotIdInventory, int N, vector<string> slotIdCrafting, CraftingTable* table){
    // MOVE <INVENTORY_SLOT_ID> N <CRAFTING_SLOT_ID_1>
    // <CRAFTING_SLOT_ID_2> ...
    // MOVE I0 N C0 C1 C2 ... CN

    // I.S. : Jumlah Item pada INVENTORY_SLOT_ID sebanyak Qty, dengan Qty
    // >= N (jumlah slot crafting).
    // F.S. :
    // 1. Jumlah Item pada INVENTORY_SLOT_ID sebanyak Qty - N.
    // 2. CRAFTING_SLOT_ID_1 hingga N berisi Item yang sama dengan
    // INVENTORY_SLOT_ID dengan jumlah masing-masing 1
    bool status = true;
  
    if(!isSlotIdValid(convertIdToInt(slotIdInventory))){
      status = false;
    //   cout << "1" << endl;
    }

    for(int i = 0; i < N && status; i++){
        int idCraft = convertIdToInt(slotIdCrafting[i]);
        status = idCraft >= 0 && idCraft <= 8;
        // cout << "2" << endl;
    }

    if (status){
        // cout << "3" << endl;
        Item* currItem = this->buffer[getRowInv(convertIdToInt(slotIdInventory))][getColInv(convertIdToInt(slotIdInventory))];
        if(currItem->getId() == 0){
            // do nothing
        } else{
            int currItemCount = currItem->getQty();
            // HANDLE LOOP
            for(int i = 0; i < slotIdCrafting.size() && currItemCount != 0; i++){
                // cout << table->getItem(0,1)->getId() << endl;
                // cout << "4" << endl;
                singleInvToCrafting(slotIdInventory, slotIdCrafting[i], table);
                // cout << "in da loop" << i << endl;
                currItemCount--;
            }
        }
        
    }else{
      cout << "Invalid slot input." << endl;
    }
}

void Inventory::craftingToInv(CraftingTable* table, string slotIdCrafting, string slotIdInventory){
// MOVE <CRAFTING_SLOT_ID> 1 <INVENTORY_SLOT_ID>
// MOVE C0 1 I0

// I.S. :
// CRAFTING_SLOT_ID tidak kosong.
// INVENTORY_SLOT_ID kosong / berisi item dengan jenis yang sama dan tidak penuh.
// F.S. : 
// CRAFTING_SLOT_ID kosong.
// Jumlah Item pada INVENTORY_SLOT_ID bertambah 1.
    int idInv = convertIdToInt(slotIdInventory);
    int rowInv = getRowInv(idInv) , colInv = getColInv(idInv);

    int idCraft = convertIdToInt(slotIdCrafting);
    int rowCraft = getRowCraft(idCraft) , colCraft = getColCraft(idCraft);  
    
    // DARI KOSONG
    if(table->getItem(rowCraft, colCraft)->getId() == 0){
        // do nothing
    }
    else{
        // ISI KE KOSONG
        if(this->buffer[rowInv][colInv]->getId() == 0){
            if(table->getItem(rowCraft, colCraft)->getCategory() == "NONTOOL"){
                Item* nontool = new NonTool(table->getItem(rowCraft, colCraft)->getId(), table->getItem(rowCraft, colCraft)->getName(), table->getItem(rowCraft, colCraft)->getType(), 1);
                this->buffer[rowInv][colInv] = nontool;
                
                if(table->getItem(rowCraft, colCraft)->getQty() == 1){
                    // erase
                    table->setItem(new NonTool(), rowCraft, colCraft);
                }
                else{
                    // kurangin satu
                    table->getItem(rowCraft, colCraft)->setQty(table->getItem(rowCraft, colCraft)->getQty() - 1);
                }
            }
            else{
                
                Item* tool = new Tool(table->getItem(rowCraft, colCraft)->getId(), table->getItem(rowCraft, colCraft)->getName(), table->getItem(rowCraft, colCraft)->getDura());
                this->buffer[rowInv][colInv] = tool;
                // erase on crafting
                table->setItem(new NonTool(), rowCraft, colCraft);
            }
        }
          
        else{
          // ISI KE ISI TAPI BEDA
          if(table->getItem(rowCraft,colCraft)->getId() != this->buffer[rowInv][colInv]->getId()){
              cout << "Slot " << slotIdInventory << " sudah terisi item " << this->buffer[rowInv][colInv]->getName() << endl;
          } // ISI KE ISI TAPI SAMA
          else{
            // NONTOOL
              if(table->getItem(rowCraft, colCraft)->getCategory() == "NONTOOL"){
              // JUMLAHNYA BELUM PENUH
                if(this->buffer[rowInv][colInv]->getQty() <= 63){
                    this->buffer[rowInv][colInv]->setQty(this->buffer[rowInv][colInv]->getQty() + 1);
                    if(table->getItem(rowCraft, colCraft)->getQty() == 1){
                        // erase
                        table->setItem(new NonTool(), rowCraft, colCraft);
                    }
                    else{
                        // kurangin satu
                        table->getItem(rowCraft, colCraft)->setQty(table->getItem(rowCraft, colCraft)->getQty() - 1);
                    }
                }
              // PENUH
                else {
                    cout << "Slot " << slotIdInventory << " sudah terisi penuh " << endl;
                }
                  
              }
            // TOOL -> GAGAL
            else {
                cout << "Slot " << slotIdInventory << " sudah terisi item Tool berupa " << this->buffer[rowInv][colInv]->getName() << endl;
            }
          }
        }
    }
}

// Show
void Inventory::showInventory(){
    // Get Max ItemName length
	int mw = 4; // Inisialisasi dengan jumlah huruf apabila penulisan I 26
	for(int i = 0 ; i < ROW; i++){
		for(int j = 0 ; j < COL ;j++){
			int tempLength = this->buffer[i][j]->getName().length() + 3;
			if (tempLength > mw){
				mw = tempLength;
			}
		}
	}
    
    //Print inventory
	for(int line = 0 ; line < mw*9 + 10 ; line++){
		cout << "-";
	}
    cout << endl;
    int slotId = 0;
    for (int i = 0; i < ROW; i++){
        for (int j = 0; j < COL; j++){
            int ws;
            cout << "|";
            // Kasus Slot Kosong
            if (this->buffer[i][j]->getId() == 0){
                ws = 4;
                for(int space = 0 ; space < (mw - ws)/2 ; space++){
                    cout << " ";
                }
                cout << "I " << slotId;
                for(int space = 0 ; space < (mw - ws)/2 + (ws%2 != 0); space++){
                    cout << " ";
                }
            } 
            // Kasus Slot Tidak Kosong
            else {
                ws = this->buffer[i][j]->getName().length() + 3;
                for(int space = 0 ; space < (mw - ws)/2 ; space++){
                    cout << " ";
                }
                cout << this->buffer[i][j]->getName() << " ";
                // Kasus Nontool (print durability)
                if (this->buffer[i][j]->getCategory() == "NONTOOL"){
                    cout << this->buffer[i][j]->getQty();
                } 
                // Kasus Tool (print quantity)
                else {
                    cout << this->buffer[i][j]->getDura();
                }
                for(int space = 0 ; space < (mw - ws)/2 + (ws%2 != 0); space++){
                    cout << " ";
                }
            }
            slotId++;
        }
        cout << "|" << endl;
        for(int line = 0 ; line < mw*9 + 10 ; line++){
            cout << "-";
        }
        cout << endl;
    }
}

// Export
void Inventory::exportInventory(string outputPath) {
    ofstream outputFile(outputPath);
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            if (this->buffer[i][j]->getId() == 0) { // KASUS GAK ADA ITEM
                outputFile << 0 << ":" << 0 << endl; 
            } 
            else if (this->buffer[i][j]->getCategory() == "TOOL"){ // KASUS TOOL
                outputFile << this->buffer[i][j]->getId() << ":" << this->buffer[i][j]->getDura() << endl;
            }
            else { // KASUS NONTOOL
                 outputFile << this->buffer[i][j]->getId() << ":" << this->buffer[i][j]->getQty() << endl;
            }
        } 
    }
    outputFile.close();
}