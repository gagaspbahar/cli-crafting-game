#include <iostream>
#include "include.hpp"

using namespace std;

int main(){
  Config config;
  config.getItemFromText();
  config.printItems();
  config.getRecipes();
}