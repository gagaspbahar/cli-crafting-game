#ifndef _SLOTINVENTORY_HPP_
#define _SLOTINVENTORY_HPP_

#include <iostream>
#include <string>
#include "Item.hpp"
#include "Tool.hpp"
#include "Nontool.hpp"
#include "InventoryException.hpp"
using namespace std;

class SlotInventory {
    protected:
        Item* slotContainer;
        const int capacity = 64;
        int quantity;
        int slotId;
    public:
        SlotInventory();
        SlotInventory(Item* slotContainer, int quantity, int slotId);
        SlotInventory(const SlotInventory& si);
        SlotInventory& operator=(const SlotInventory& si);
        virtual ~SlotInventory();

        // Getter
        int getSlotId();
        int getQuantity();
        int getEmptyQuantity();
        Item* getItemInfo();
        string getNameFromSlotItem();
        string getCategoryFromSlotItem();

        // Setter
        void setSlotId(int slotId);
        void setQuantity(int currentQuantity);
        
        // Adder
        void addQuantity(int quantity);
        void addItemToSlot(Item* item, int quantity);

        // Remover
        void removeItem(int quantity);
};

#endif