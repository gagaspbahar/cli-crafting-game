#include <iostream>
#include "./header/Config.hpp"

using namespace std;

int main(){
  Config config;
  config.getItemFromText();
  config.printItems();
}