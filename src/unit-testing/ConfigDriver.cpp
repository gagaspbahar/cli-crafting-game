#include "../../header/Config.hpp"
#include "../Config.cpp"

int main(){
    Config config;
    config.getItemFromText();
    config.getRecipesFromText();
    config.printItems();
    config.getRecipe().printRecipe("WOODEN_SWORD");
    return 0;
}