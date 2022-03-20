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
  int id;
  string name;
  string parentClass;
  string category;
};

class Config {
  private:
    vector<ItemConfig> itemList;
    vector<Recipe> recipeList;
    int itemCount;
    int recipeCount;
    static string directory;
    static string recipe_directory;
  public:
    Config();
    void printItems();
    void getItemFromText();
    void getRecipes();
};


#endif