#include <fstream>
#include <string>
#include <iostream>
#include <unordered_set>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    std::unordered_set<std::string> candidates;
    std::unordered_set<std::string> dismissed;
    while(getline(file, s)){
        bool above{false};
        std::string temp;
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] > 96 && s[i] < 123){
                temp += s[i];
            }
            else if(s[i] == '>'){
                above = true;
            }
            else if(temp.length() > 0){
                if(above){
                    if(candidates.find(temp) != candidates.end()){
                        candidates.erase(temp);
                    }
                    else dismissed.insert(temp);
                }
                else{
                    if(dismissed.find(temp) != dismissed.end()){
                        dismissed.erase(temp);
                    }
                    else candidates.insert(temp);
                }
                temp.clear();
            }
        }
        if(temp.length() > 0){
            if(candidates.find(temp) != candidates.end()){
                candidates.erase(temp);
            }
            else dismissed.insert(temp);
        }
    }
    for(auto& res : candidates){
        std::cout << res << "\n";
    }
    return 0;
}