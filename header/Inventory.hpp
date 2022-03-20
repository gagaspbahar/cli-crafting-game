#ifndef INVENTORY_HPP
#define INVENTORY_HPP

#include <iostream>
#include "Item.hpp"
#include <map>
using namespace std;

#define MAX_CAP 64 // Kapasitas maksimum per slot
#define MAX_SLOT 27 // Jumlah slot maksimum dalam inventory

template <class T>
class Inventory {
protected:
    map<T, int> inv;
    int size; // Total kapasitas yang terpakai
public:
    // Ctor
    Inventory() {
        this->inv = new map<T, int>[MAX_SLOT];
        this->size = 0;
    }

    // Mengembalikan total kapasitas yang sudah terpakai
    int getCapacity() const {
        return this->size;
    }

    // Mengembalikan indeks slot inventory dari item
    int getIdxItem(T item) {
        for (int idx = 0; idx < MAX_SLOT; idx++) {
            if (this->inv[idx].first == item) {
                return idx;
            }
        }
        return -1;
    }

    // Mengembalikan calon slot yang akan diisi berikutnya
    int getLastSlot() const {
        int idx = 0;
        while (this->inv[idx].second != 0) {
            idx++;
        }
        return idx;
    }

    // Mengembalikan apakah kapasitas slot sudah penuh atau belum
    bool isSlotFull(int idx) const {
        return this->inv[idx].second == MAX_CAP;
    }

    // Menambahkan item ke inventory
    void giveItem(T item, int qty) {
        idx = this->getIdxItem(item);
        if ((getIdxItem(item) != -1) && (this->inv[idx].second + qty < MAX_CAP)) {
            this->inv[idx].second += qty;
        } else {
            lastSlot =  this->getLastSlot();
            this->inv[lastSlot].first = item;
            this->inv[lastSlot].second = qty;
        }
        this->size++;
    }

    // Memindahkan item: memindahkan ke slot crafting, menumpuk, mengembalikan dari slot crafting ke inventory
    // Perlu buat fungsi terpisah atau gimana ya enaknya?
    void moveItem(T item) {
        
    }

    // Membuang item dari inventory
    void discardItem(int idx, int qty) {
        if (this->inv[idx].second >= qty) {
            this->inv[idx].second -= qty;
            if (this->inv[idx].second == 0)) {
                int lastSlot = this->getLastSlot();
                for (int i = idx; i < lastSlot; i++) {
                    this->inv[i] = this->inv[i + 1];
                }
            }
        } else {
            cout << "Jumlah item yang ingin dibuang tidak mencukupi" << endl;
        }
        this->size--;
    }

    // Menampilkan inventory
    void showInventory() {

    }
};

#endif