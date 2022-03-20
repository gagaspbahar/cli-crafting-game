#ifndef RECIPE_H
#define RECIPE_H

#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

class Recipe {
private:
    map<string, int> row, col, qty;
    map<string, string> item;
    map<string, vector<vector<string>>> recipe;
public:
    Recipe();
    Recipe(string path);
    int getRow(string item);
    int getCol(string item);
    int getQty(string item);
    string getItemName(string item);
    string getRecipeComponent(string item, int row, int col);
    void printRecipe(string item);
    void printInfo(string item);
};

#endif