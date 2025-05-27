#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    std::unordered_map<int, int> inv;
    bool duplicate{false};
    while(getline(file, s)){
        for(int i = 0; i <= 13; i++){
            if(inv.find(s[i]) != inv.end()){
                inv.at(s[i])++;
            }
            else inv.insert(std::make_pair(s[i], 1));
        }
        for(int j = 14; j <= s.length() - 1; j++){
            for(auto& [key, value]: inv){
                std::cout << value << "\n";
                if(value > 1){
                    duplicate = true;
                }
            }
            if(!duplicate){
                res = j;
                break;
            }
            inv.at(s[j - 14])--;
            if(inv.find(s[j]) != inv.end()){
                inv.at(s[j])++;
            }
            else inv.insert(std::make_pair(s[j], 1));
            duplicate = false;
        }
    }
    std::cout << res << "\n";
    return res;
}