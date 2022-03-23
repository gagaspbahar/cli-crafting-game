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

void Config::getRecipesFromText() {
  this->recipe = Recipe(recipe_directory);
}

Recipe Config::getRecipe() {
  return this->recipe;
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

int Config::getIDFromName(string name) {
  for (auto i = this->itemList.begin(); i != itemList.end(); i++) {
    if (i->name == name) {
      return i->id;
    }
  }
  return -1;
}

vector<ItemConfig> Config::getItemList() {
  return this->itemList;
}

void Config::printHelp(){
  cout << "============== HELP ==============" << endl;
  cout << "SHOW : Menampilkan isi slot crafting dan inventory" << endl;
  cout << "GIVE <ITEM_NAME> <ITEM_QTY> : Menambahkan item sebanyak item_qty ke inventory" << endl;
  cout << "DISCARD <INVENTORY_SLOT_ID> <ITEM_QTY> : Membuang item di slot inventory dengan kuantitas yang diberikan." << endl;
  cout << "MOVE <INVENTORY_SLOT_ID> N <CRAFTING_SLOT_ID_1> ... : Memindahkan item ke slot crafting." << endl;
  cout << "MOVE <INVENTORY_SLOT_ID_SRC> 1 <INVENTORY_SLOT_ID_DEST> : Memindahkan atau menumpuk item non tool." << endl;
  cout << "MOVE <CRAFTING_SLOT_ID> 1 <INVENTORY_SLOT_ID> : Mengembalikan item dari slot crafting ke inventory" << endl;
  cout << "USE <INVENTORY_SLOT_ID> : Menggunakan item tool" << endl;
  cout << "CRAFT : Memulai crafting dengan item yang sudah ada pada crafting table" << endl;
  cout << "EXPORT <NAMA_FILE> : Mengexport isi inventory ke file argumen." << endl;
  cout << "HELP : Menunjukkan menu bantuan untuk command-command." << endl;
  cout << "EXIT : Keluar dari program." << endl;
}