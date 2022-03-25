#include <iostream>
#include "./header/Config.hpp"
#include "./header/CraftingTable.hpp"
#include "./header/Exception.hpp"
#include "./header/Inventory.hpp"
#include "./header/Item.hpp"
#include "./header/Nontool.hpp"
#include "./header/Recipe.hpp"
#include "./header/Tool.hpp"

using namespace std;

int main(){
  cout << "                                         WELCOME TO" << endl;
  cout <<".___  ___.  __  .__   __.  _______  __  ___ .______          ___       _______ .___________." << endl;
  cout <<"|   \\/   | /_ | |  \\ |  | |   ____||  |/  / |   _  \\        /   \\     |   ____||           |" << endl;
  cout <<"|  \\  /  |  | | |   \\|  | |  |__   |  '  /  |  |_)  |      /  ^  \\    |  |__   `---|  |----`" << endl;
  cout <<"|  |\\/|  |  | | |  . `  | |   __|  |    <   |      /      /  /_\\  \\   |   __|      |  |     " << endl;
  cout <<"|  |  |  |  | | |  |\\   | |  |____ |  .  \\  |  |\\  \\----./  _____  \\  |  |         |  |     " << endl;
  cout << "|__|  |__|  |_| |__| \\__| |_______||__|\\__\\ | _| `._____/__/     \\__\\ |__|         |__|     " << endl;
                                                                                            
  cout << "Please wait for the configs to load.." << endl;

  Config config;
  config.getItemFromText();
  config.getRecipesFromText();
  cout << "Config loaded" << endl;
  Inventory inventory = Inventory();
  cout << "Inventory loaded" << endl;
  CraftingTable table = CraftingTable();

  cout << "Done!\n" << endl;
  cout << "What do you want to do?" << endl;

  string command;
  while(cout << ">> " && cin >> command){
    if(command == "SHOW"){
      cout << "===== CRAFTING TABLE =====" << endl;
      table.printTable();
      cout << "===== INVENTORY =====" << endl;
      inventory.showInventory();
    }
    else if (command == "GIVE"){
      string itemName;
      int itemQty;
      cin >> itemName >> itemQty;
      int itemID = config.getIDFromName(itemName);
      if(itemID == -1){
        cout << "No item with that name." << endl;
      }
      else{
        string itemCategory = config.getCategoryFromID(itemID);
        Item* tempItem = new Item(itemID, itemName, itemCategory);
        inventory.giveItem(tempItem, itemQty, config);
      }
    }
    else if (command == "DISCARD"){
      string inventorySlot;
      int itemQty;
      cin >> inventorySlot >> itemQty;
      Item* tempItem = inventory.getItemFromSlot(inventorySlot);
      if(tempItem->getQty() < itemQty){
        cout << "There is not enough item you're trying to discard." << endl;
      }
      else{
        inventory.discardItem(inventorySlot, itemQty);
      }
    }
    else if (command == "MOVE"){
      string slotSrc;
      int slotQty;
      string slotDest;
      cin >> slotSrc >> slotQty >> slotDest;

      if (slotSrc[0] == 'I' && slotDest[0] == 'C'){
        // Case inven to crafting
        vector<string> stringArray;
        stringArray.push_back(slotDest);
        string temps;
        for(int i = 1; i < slotQty; i++){
          cin >> temps;
          stringArray.push_back(temps);
        }
        if(slotQty != stringArray.size()){
          cout << "Slot N and amount of item is different. Command invalid. Array Length: " << stringArray.size() << endl;
        }
        else{
          inventory.invToCrafting(slotSrc, slotQty, stringArray, &table);
        }
      } else if (slotSrc[0] == 'I' && slotDest[0] == 'I'){
        // Case inven to inven
        inventory.invToInv(slotSrc, slotDest);
      } else if (slotSrc[0] == 'C' && slotDest[0] == 'I'){
        // case crafting to inven
        inventory.craftingToInv(&table, slotSrc, slotDest);
      }

    }
    else if (command == "USE"){
      string inventorySlot;
      cin >> inventorySlot;
      Item* currentItem = inventory.getItemFromSlot(inventorySlot);
      if(currentItem->getCategory() == "TOOL"){
        currentItem->use();
        if(currentItem->getDura() == 0){
          inventory.discardItem(inventorySlot,1);
        }
        
      }
      else{
        if (currentItem->getId() == 0){
          cout << "Empty slot can't be used." << endl;
        } else {
          cout << "Non-tool items can't be used." << endl;
        }
      }
    }
    else if (command == "CRAFT"){
      pair<Item*, int> tempItem = table.craft(config);
      inventory.giveItem(tempItem.first, tempItem.second, config);
    }
    else if (command == "EXPORT"){
      string outputPath;
      cout << "Enter your desired export filename: ";
      cin >> outputPath;
      outputPath = "./output/" + outputPath;
      inventory.exportInventory(outputPath);
    }
    else if (command == "HELP"){
      config.printHelp();
    }
    else if(command == "LOAD"){
      string inputPath;
      cout << "Enter your desired import filename (./config/input/): ";
      cin >> inputPath;
      vector<pair<int,int>> inv = config.loadInventoryFromText(inputPath);
      for(int i = 0; i < inv.size(); i++){
        try{
          int itemID = inv[i].first;
          if(itemID == -1){
            cout << "No item with that name." << endl;
            throw ItemNotFoundException();
          }
          else if(inv[i].second == 0){
            // do nothing
          }
          else{
            string itemCategory = config.getCategoryFromID(itemID);
            string itemName = config.getNameFromID(itemID);
            Item* tempItem = new Item(itemID, itemName, itemCategory);
            if(itemCategory == "NONTOOL"){
              inventory.giveItem(tempItem, inv[i].second, config);
            }
            else{
              inventory.giveItem(tempItem, 1, config);
            }
          }
        }
        catch(BaseException& e){
          e.printMessage();
        }
      }
    }
    else if (command == "QUIT"){
      return 0;
    }
    else{
      cout << "Invalid command! Please try again." << endl;
    }
    cout << endl;
  }
  return 0;
}