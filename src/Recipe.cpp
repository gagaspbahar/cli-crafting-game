#include "../header/Recipe.hpp"

Recipe::Recipe(){
    this->row = map<string, int>();
    this->col = map<string, int>();
    this->item = map<string, string>();
    this->qty = map<string, int>();
    this->recipe = map<string, vector<vector<string>>>();
}

Recipe::Recipe(string path) {
    // get all recipe txt file
    vector<string> recipePathList;
    for (const auto & entry : filesystem::directory_iterator(path)){
        recipePathList.push_back(entry.path().string());
    }

    // adding every recipe to map
    for(auto it = begin(recipePathList); it != end(recipePathList); ++it) {
        ifstream file(*it);
        string line;
        int row, col, qty;
        string item;
        vector<vector<string>> recipe;

        getline(file, line);
        stringstream ss(line);
        ss >> row >> col;

        for (int i = 0; i < row; i++) {
            getline(file,line);
            stringstream ss(line);
            vector<string> row;
            for (int j = 0; j < col; j++) {
                string item;
                ss >> item;
                row.push_back(item);
            }
            recipe.push_back(row);
        }

        getline(file, line);
        stringstream sr(line);
        sr >> item >> qty;

        this->item[item] = item;
        this->row[item] = row;
        this->col[item] = col;
        this->qty[item] = qty;
        this->recipe[item] = recipe;

        file.close();
    }
}

int Recipe::getRow(string item) {
    return this->row[item];
}

int Recipe::getCol(string item) {
    return this->col[item];
}

int Recipe::getQty(string item) {
    return this->qty[item];
}

string Recipe::getItemName(string item) {
    return this->item[item];
}

string Recipe::getRecipeComponent(string item, int row, int col) {
    return this->recipe[item][row][col];
}

void Recipe::printRecipe(string item) {
    for (int i = 0; i < this->row[item]; i++) {
        for (int j = 0; j < this->col[item]; j++) {
            cout << this->recipe[item][i][j] << " ";
        }
        cout << "\n";
    }
}

void Recipe::printInfo(string item) {
    cout << "Size: " << getRow(item) << "x" << getCol(item) << endl;
    cout << "Item: " << getItemName(item) << endl;
    cout << "Qty: " << getQty(item) << endl;
    cout << "Recipe:" << endl;
    printRecipe(item);
}