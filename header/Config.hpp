#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "Recipe.hpp"

using namespace std;

struct ItemConfig {
  // Empty ItemConfig = {-1,"","",""} (for crafting table use)
  int id;
  string name;
  string parentClass;
  string category;
};

class Config {
  private:
    vector<ItemConfig> itemList;
    Recipe recipe;
    int itemCount;
    int recipeCount;
    static string directory;
    static string recipe_directory;
    static string input_directory;
  public:
    Config();
    void printHelp();
    void printItems();
    void getItemFromText();
    void getRecipesFromText();
    Recipe getRecipe();
    string getNameFromID(int id);
    string getTypeFromID(int id);
    string getCategoryFromID(int id);
    int getIDFromName(string name);
    vector<ItemConfig> getItemList();
    static vector<string> stringParse(string s);
    vector<pair<int, int>> loadInventoryFromText(string filename);
};


#endif