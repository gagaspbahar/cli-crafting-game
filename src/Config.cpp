#include "../header/Config.hpp"
#include "../header/Exception.hpp"

string Config::directory = "./config/";

string Config::recipe_directory = "./config/recipe";

Config::Config()
{
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
  vector<string> recipePathList;
  for (const auto & entry : filesystem::directory_iterator(recipe_directory)){
    recipePathList.push_back(entry.path().string());
  }
  // TODO: masukin hasil recipenya ke config
}