#ifndef ITEM_HPP
#define ITEM_HPP

#include <iostream>
#include <string>
using namespace std;

class Item {
protected :
    int id;
    string name;
    string category;
public :
	// CONSTRUCTOR
    Item();
    Item(int, string, string);
    Item(const Item&);
    
    // DESTRUCTOR
    ~Item();

    // GETTER
    int getId() const;
    string getName() const;
    string getCategory() const;
    virtual string getType() const;
    virtual int getDura() const;
    virtual int getQty() const;

    // SETTER
    void setId(int);
    void setName(string);
    void setCategory(string);
    virtual void setDura(int);
    virtual void setQty(int);
    
    // OPERATOR ASSIGNMENT
    Item& operator=(const Item& item);
    
    // OPERATOR OVERLOADING
    // virtual Item& operator +=(int);
    // virtual Item& operator -=(int);
    friend bool operator==(const Item&, const Item&);
    
    // USE FUNCTION
    virtual void use();
    // virtual bool isTool();

    // FOR DYNAMIC CASTING
    template<typename T>
        bool isA() {
            return (dynamic_cast<T*>(this) != NULL);
        }
};

#endif