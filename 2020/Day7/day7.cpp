#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <unordered_set>

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<std::string, std::vector<std::string>> bags;
    int res{0};
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
                if(bags.find(contained) == bags.end()){
                    std::vector<std::string> init;
                    init.push_back(container);
                    bags.insert(std::make_pair(contained, init));      // on insère les sacs contenus en clé et les sacs contenants en valeur
                }
                else{
                    bags.at(contained).push_back(container);
                }
            }
        }
    }
    std::unordered_set<std::string> tally;
    std::stack<std::string> bagsStack;
    bagsStack.push("shinygold");
    while(bagsStack.size() > 0){
        std::string temp{bagsStack.top()};
        bagsStack.pop();
        for(auto& moreBags : bags.at(temp)){
            tally.insert(moreBags);                 // un set pour ne pas avoir de doublon
            if(bags.find(moreBags) != bags.end()){
                bagsStack.push(moreBags);
            }
        }
    }
    std::cout << tally.size() << "\n";
    return 0;
}