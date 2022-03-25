#include "../../header/CraftingTable.hpp"
#include "../CraftingTable.cpp"

int main(){
    CraftingTable* table = new CraftingTable();

    Item* toolItem1 = new Item(13, "WOODEN_PICKAXE", "TOOL");
    Item* toolItem2 = new Item(17, "WOODEN_AXE", "TOOL");
    Item* toolItem3 = new Item(22, "STONE_SWORD", "TOOL");
    Item* nonToolItem1 = new Item(1, "OAK", "NONTOOL");
    Item* nonToolItem2 = new Item(5, "SPRUCE_PLANK", "NONTOOL");
    Item* nonToolItem3 = new Item(10, "IRON_INGOT", "NONTOOL");

    table->setItem(toolItem1, 0, 0);
    table->setItem(toolItem2, 0, 1);
    table->setItem(toolItem3, 0, 2);
    table->setItem(nonToolItem1, 1, 0);
    table->setItem(nonToolItem2, 1, 1);
    table->setItem(nonToolItem3, 1, 2);

    table->printTable();
    if (!table->isAllNonTool()){
        cout << "Tabel tidak semuanya berisi nontool" << endl;
    }
    if (!table->isAllTool()){
        cout << "Tabel tidak semuanya berisi tool" << endl;
    }

    return 0;
}