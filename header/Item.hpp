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

    // SETTER
    void setId(int);
    void setName(string);
    void setCategory(string);
    
    // OPERATOR ASSIGNMENT
    Item& operator=(const Item& item);
    
    // OPERATOR OVERLOADING
    virtual Item& operator +=(int) = 0;
    virtual Item& operator -=(int) = 0;
    friend bool operator==(const Item&, const Item&);
    
    // USE FUNCTION
    virtual void use() = 0;

    // FOR DYNAMIC CASTING
    template<typename T>
        bool isA() {
            return (dynamic_cast<T*>(this) != NULL);
        }
};

#endif