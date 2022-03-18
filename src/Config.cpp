#include "../header/Config.hpp"

string Config::directory = "./config/";

string Config::recipe_directory = "./config/recipe";

Config::Config()
{
  this->itemCount = 0;
  this->recipeCount = 0;
}

void Config::getItemFromText()
{
  ifstream input(directory + "item.txt");
  ItemConfig temp;
  string id, name, parentClass, category;
  while (input >> id >> name >> parentClass >> category)
  {
    temp = {stoi(id), name, parentClass, category};
    this->itemList.push_back(temp);
  }
}

void Config::printItems()
{
  for (auto it = this->itemList.begin(); it != this->itemList.end(); it++)
  {
    cout << it->id << " " << it->name << " " << it->parentClass << " " << it->category << endl;
  }
}
