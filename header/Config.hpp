#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

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
    int itemCount;
    int recipeCount;
    static string directory;
    static string recipe_directory;
  public:
    Config();
    void printItems();
    void getItemFromText();
};


#endif