#include <iostream>
#include "./header/Config.hpp"
#include "./header/CraftingTable.hpp"
#include "./header/Exception.hpp"
#include "./header/Inventory.hpp"
#include "./header/InventoryException.hpp"
#include "./header/Item.hpp"
#include "./header/Nontool.hpp"
#include "./header/Recipe.hpp"
#include "./header/SlotInventory.hpp"
#include "./header/Tool.hpp"

using namespace std;

int main(){
  cout << "Welcome to M1necraft!" << endl;
  cout << "Please wait for the configs to load.." << endl;

  Config config;
  config.getItemFromText();
  config.getRecipesFromText();

  Inventory inventory;

  CraftingTable table;

  cout << "Done!\n" << endl;
  cout << "What do you want to do?" << endl;

  string command;
  while(cin >> command){
    if(command == "SHOW"){
      inventory.showInventory();
    }
    else if (command == "GIVE"){
      string itemName;
      int itemQty;
      cin >> itemName >> itemQty;
      int itemID = config.getIDFromName(itemName);
      string itemCategory = config.getCategoryFromID(itemID);
      Item* tempItem = new Item(itemID, itemName, itemCategory);
      inventory.giveItem(tempItem, itemQty);
    }
    else if (command == "DISCARD"){
      string inventorySlot;
      int itemQty;
      inventory.discardItem(inventorySlot, itemQty);
    }
    else if (command == "MOVE"){
      string slotSrc;
      int slotQty;
      string slotDest;
      cin >> slotSrc >> slotQty >> slotDest;

      if (slotSrc[0] == 'I' && slotDest[0] == 'C'){
        // Case inven to crafting
        string* stringArray = Config::stringParse(slotDest);
        inventory.moveToCrafting(slotSrc, slotQty, stringArray, table);
      } else if (slotSrc[0] == 'I' && slotDest[0] == 'I'){
        // Case inven to inven
        inventory.moveItem(slotSrc, slotDest);
      } else if (slotSrc[0] == 'C' && slotDest[0] == 'I'){
        // case crafting to inven
        // TODO
      }

    }
    else if (command == "USE"){
      string inventorySlot;
      cin >> inventorySlot;
      // TODO: Getter inventoryslot return item?
    }
    else if (command == "CRAFT"){
      table.craft(config);
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
    else if (command == "QUIT"){
      return 0;
    }
    else{
      cout << "Invalid command! Please try again." << endl;
    }
  }
  return 0;
}