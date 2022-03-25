#include "../../header/Inventory.hpp"
#include "../Inventory.cpp"

int main(){
    Inventory* tas = new Inventory();
    CraftingTable* table = new CraftingTable();
    Config config;
    config.getItemFromText();
    config.getRecipesFromText();
    
    Item* toolItem1 = new Item(13, "WOODEN_PICKAXE", "TOOL");
    Item* toolItem2 = new Item(17, "WOODEN_AXE", "TOOL");
    Item* toolItem3 = new Item(22, "STONE_SWORD", "TOOL");
    Item* nonToolItem1 = new Item(1, "OAK", "NONTOOL");
    Item* nonToolItem2 = new Item(5, "SPRUCE_PLANK", "NONTOOL");
    Item* nonToolItem3 = new Item(10, "IRON_INGOT", "NONTOOL");

    // Mencoba show dengan tas kosong
    tas->showInventory();

    // Mencoba give item
    tas->giveItem(toolItem1, 1, config);
    tas->giveItem(nonToolItem1, 5, config);
    tas->showInventory();

    // Mencoba menambahkan item tool yang sudah ada
    tas->giveItem(toolItem1, 1, config);
    tas->showInventory();

    // Mencoba menambahkan item nontool yang sudah ada
    tas->giveItem(nonToolItem1, 5, config);
    tas->showInventory();

    // Mencoba menambahkan item nontool yang sudah ada, tapi melebihi kapasitas tas
    tas->giveItem(nonToolItem1, 60, config);
    tas->showInventory();

    // Mencoba memindahkan item dari inven ke inven
    tas->invToInv("I0", "I8");
    tas->invToInv("I0", "I3");
    tas->showInventory();

    // Mencoba memindahkan item dari crafting ke inv
    tas->craftingToInv(table, "I0", "C0");

    // Mencoba memindahkan item dari crafting ke inven
    vector<string> teppy;
    teppy.push_back("C2");
    tas->invToCrafting("I1", 1, teppy, table);
    table->printTable();
    tas->showInventory();
    
    // GIVE TOOL 102 BIJI THEN ERROR BOOM BOOM
    tas->giveItem(toolItem2, 102, config);

    return 0;
}