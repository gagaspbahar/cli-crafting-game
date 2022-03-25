#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <iostream>
#include <string>
using namespace std;

class BaseException {
  public:
    virtual void printMessage() = 0;
};

class FileNotFoundException : public BaseException {
  public:
    FileNotFoundException() {}
    void printMessage() {
      cout << "File input tidak tersedia." << endl;
    }
};

class FullException : public BaseException {
public:
    FullException() {}
    void printMessage() {
        cout << "Banyaknya item melebihi kapasitas inventory." << endl ;
    }
};

class EmptyException : public BaseException {
public:
    EmptyException() {}
    void printMessage() {
        cout << "Insufficient number of items, discarding process failed."<< endl;
    }
};

class DifferentItemException : public BaseException {
public:
    DifferentItemException() {}
    void printMessage() {
        cout << "You can't stack two different items, moving process failed."<< endl;
    }
};

class ToolException : public BaseException {
public:
    ToolException() {}
    void printMessage() {
        cout << "You can't stack tool."<< endl;
    }
};

class GiveZeroItemException : public BaseException {
public:
    GiveZeroItemException() {}
    void printMessage() {
        cout << "You can't give only 0 items."<< endl;
    }
};

class ItemSlotInvalid : public BaseException {
public:
    ItemSlotInvalid() {
    }
    void printMessage() {
      cout << "Invalid slot input." << endl;
    }
};

class NoItemException : public BaseException {
public:
    NoItemException() {}
    void printMessage() {
        cout << "Tidak ada item pada slot tersebut."<< endl;
    }
};

class SlotKeisiException : public BaseException {
public:
    SlotKeisiException() {}
    void printMessage() {
        cout << "Slot tersebut sudah berisi item."<< endl;
    }
};

class SlotPenuhException : public BaseException {
public:
    SlotPenuhException() {}
    void printMessage() {
        cout << "Slot tersebut sudah terisi penuh."<< endl;
    }
};

class sudahKeisiItemException : public BaseException {
public:
    string a;
    string b;
    sudahKeisiItemException(string a, string b) {
      this->a = a;
      this->b = b;
    }
    void printMessage() {
      cout << "Slot " << a << " sudah terisi item berupa " << b << endl;
    }
};



#endif