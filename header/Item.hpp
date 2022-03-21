#ifndef ITEM_HPP
#define ITEM_HPP

#include <bits/stdc++.h>
using namespace std;

class Item {
protected :
    static int numOfItem;
    const int id;
    string name;
    string category;
public :
	// CONSTRUCTOR
    Item();
    Item(int id, string name, string category);
    
    // DESTRUCTOR
    ~Item();

    // GETTER
    int getId() const;
    string getName() const;
    string getCategory() const;

    // SETTER
    void setId(int);
    void setName(string);
    void setCategory(string);
    
    // OPERATOR ASSIGNMENT
    Item& operator=(const Item& item);
    
    // OPERATOR OVERLOADING
    virtual Item& operator +=(int) = 0;
    virtual Item& operator -=(int) = 0;
    friend bool operator==(const Item& i1, const Item& i2);
    
    // USE FUNCTION
    virtual void use() = 0;

    // FOR DYNAMIC CASTING
    template<typename T>
        bool isA() {
            return (dynamic_cast<T*>(this) != NULL);
        }
};

#endif