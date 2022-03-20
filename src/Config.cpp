#include "../header/Config.hpp"
#include "../header/Exception.hpp"

string Config::directory = "./config/";

string Config::recipe_directory = "./config/recipe";

Config::Config()
{
  this->itemList = vector<ItemConfig>();
  this->recipe = Recipe();
  this->itemCount = 0;
  this->recipeCount = 0;
}

void Config::getItemFromText()
{
  try
  {
    ifstream input(directory + "item.txt");
    if (input.fail())
    {
      throw FileNotFoundException();
    }
    ItemConfig temp;
    string id, name, parentClass, category;
    while (input >> id >> name >> parentClass >> category)
    {
      temp = {stoi(id), name, parentClass, category};
      this->itemList.push_back(temp);
    }
  }
  catch (BaseException& e)
  {
    e.printMessage();
  }
}

void Config::printItems()
{
  for (auto it = this->itemList.begin(); it != this->itemList.end(); it++)
  {
    cout << it->id << " " << it->name << " " << it->parentClass << " " << it->category << endl;
  }
}

void Config::getRecipes() {
  this->recipe = Recipe(recipe_directory);
}

string Config::getNameFromID(int id) {
  for (auto i = this->itemList.begin(); i != itemList.end(); i++) {
    if (i->id == id) {
      return i->name;
    }
  }
  return "notfound";
}

string Config::getTypeFromID(int id) {
  for (auto i = this->itemList.begin(); i != itemList.end(); i++) {
    if (i->id == id) {
      return i->parentClass;;
    }
  }
  return "notfound";
}

string Config::getCategoryFromID(int id) {
  for (auto i = this->itemList.begin(); i != itemList.end(); i++) {
    if (i->id == id) {
      return i->category;
    }
  }
  return "notfound";
}