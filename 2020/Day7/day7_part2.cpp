#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>

int res{0};

void countContainedBags(std::string bag, int quantity, std::unordered_map<std::string, std::unordered_map<std::string, int>>& bags){
    if(bags.find(bag) != bags.end()){
        for(auto& [key, val] : bags.at(bag)){
            res += val * quantity;
            countContainedBags(key, quantity * val, bags);
        }
    }
}

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<std::string, std::unordered_map<std::string, int>> bags;
    while(getline(file, s)){
        std::string container;
        int spaces{0};
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] == ' '){
                spaces++;
            }
            else if(spaces <= 1){
                container += s[i];
            }
            else if(s[i] > 47 && s[i] < 58){
                int quantity{std::stoi(s.substr(i, 1))};
                std::string contained;
                int spaceCount{0};
                for(int j = i + 2;; j++){
                    if(s[j] == ' '){
                        spaceCount++;
                        if(spaceCount == 2){
                            break;
                        }
                    }
                    else if(spaceCount <= 1){
                        contained += s[j];
                    }
                    i++;
                }
                if(bags.find(container) == bags.end()){
                    std::unordered_map<std::string, int> init;
                    init.insert(std::make_pair(contained, quantity));
                    bags.insert(std::make_pair(container, init));      // on insère les sacs contenants en clé et les sacs contenus en valeur
                }
                else{
                    bags.at(container).insert(std::make_pair(contained, quantity));
                }
            }
        }
    }
    countContainedBags("shinygold", 1, bags);
    std::cout << res << "\n";
    return 0;
}