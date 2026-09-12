#include <iostream>
#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>

int main(){
    std::ifstream file("inputtest");
    std::string s;
    std::unordered_map<std::string, std::vector<std::vector<std::string>>> alergens;
    std::unordered_map<std::string, int> ingredientCounter;
    while(getline(file, s)){
        std::string ingredient;
        std::vector<std::string> containedAlergens;
        for(int i = 0; i < s.length(); i++){
            if(s[i] >= 97 && s[i] <= 122){
                ingredient += s[i];
            }
            else if(s[i] == 32){
                containedAlergens.push_back(ingredient);
                if(ingredientCounter.find(ingredient) != ingredientCounter.end()){
                    ingredientCounter.at(ingredient)++;
                }
                else ingredientCounter.insert(std::make_pair(ingredient, 0));
                ingredient.clear();
            }
            else if(s[i] == 40){
                std::sort(containedAlergens.begin(), containedAlergens.end());
                int index{i + 10};
                std::string alergen;
                while(index < s.length()){
                    if(s[index] >= 97 && s[index] <= 122){
                        alergen += s[index];
                    }
                    else if(s[index] == 44 || s[index] == 41){
                        if(alergens.find(alergen) != alergens.end()){
                            alergens.at(alergen).push_back(containedAlergens);
                        }
                        else{
                            std::vector<std::vector<std::string>> temp{containedAlergens};
                            alergens.insert(std::make_pair(alergen, temp));
                        }
                        alergen.clear();
                    }
                    index++;
                }
                i = index;
            }
        }
    }
    for(auto& [key, val] : alergens){
        std::cout << "key: " << key << "\n";
        for(int i = 0; i < val.size(); i++){
            for(int j = 0; j < val[i].size(); j++){
                std::cout << val[i][j] << "\n";
            }
            std::cout << " next line " << "\n";
        }
        std::cout << "\n";
    }
    std::vector<std::string> containAlergen;
    for(auto& [key, val] : alergens){
        std::vector<std::string> commonIngredient;
        for(int i = 0; i < val.size(); i++){
            std::set_intersection(val[i].begin(), val[i].end(), commonIngredient.begin(), commonIngredient.end(), back_inserter(commonIngredient));
        }
        containAlergen.push_back(commonIngredient[0]);
    }
    int res{0};
    for(auto& [key, val] : ingredientCounter){
        if(std::find(containAlergen.begin(), containAlergen.end(), key) == containAlergen.end()){
            res += val;
        }
    }
    std::cout << res << "\n";
    return 0;
}