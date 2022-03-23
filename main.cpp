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
      // TODO
    }
    else if (command == "DISCARD"){
      // TODO
      string inventorySlot;
      int itemQty;
      inventory.discardItem(inventorySlot, itemQty);
    }
    else if (command == "MOVE"){
      string slotSrc;
      int slotQty;
      string slotDest;
      cin >> slotSrc >> slotQty >> slotDest;
      // TODO: need to parse slotDest for multiple destinations.
      // TODO
    }
    else if (command == "USE"){
      string inventorySlot;
      cin >> inventorySlot;
      // TODO
    }
    else if (command == "CRAFT"){
      // TODO
    }
    else if (command == "EXPORT"){
      string outputPath;
      cout << "Enter your desired export filename: ";
      cin >> outputPath;
      outputPath = "./output/" + outputPath;
      // TODO
    }
    else if (command == "HELP"){
      // TODO
      
    }
    else if (command == "QUIT"){
      // TODO
      return 0;
    }
    else{
      cout << "Invalid command! Please try again." << endl;
    }
  }
  return 0;
}