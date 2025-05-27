#include <fstream>
#include <string>
#include <iostream>
#include <vector>

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<int> jumps;
    int res{0};
    while(getline(file, s)){
        if(s.length() > 0){
            jumps.push_back(std::stoi(s));
        }
    }
    int index{0};
    while(index < jumps.size() && index >= 0){
        int temp{index};
        index += jumps[index];
        jumps[temp]++;
        res++;
    }
    std::cout << res << "\n";
    return res;
}