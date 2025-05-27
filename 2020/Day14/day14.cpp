#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <bitset>

int main(){
    std::ifstream file("input");
    std::string s;
    std::string mask;
    std::unordered_map<int, long> mem;
    while(getline(file, s)){
        if(s[1] == 'a'){
            mask = s.substr(7);
            std::cout << "mask " << mask << "\n";
        }
        else{
            std::string addressMem;
            int index{4};
            while(s[index] > 47 && s[index] < 58){
                addressMem += s[index];
                index++;
            }
            std::cout << "addressMem " << addressMem << "\n";
            int location{std::stoi(addressMem)};
            std::string temp;
            index += 4;
            while(index < s.length()){
                temp += s[index];
                index++;
            }
            std::cout << "value " << temp << "\n";
            long value{std::stol(temp)};
            std::string bitRep = std::bitset<36>(value).to_string();        // représentation binaire
            std::string toBeInserted;
            for(int i = 0; i < 36; i++){
                if(mask[i] == 'X'){
                    toBeInserted += bitRep[i];
                }
                else toBeInserted += mask[i];
            }
            long binaryToLong = std::stol(toBeInserted, nullptr, 2);        // binaire vers long
            if(mem.find(location) == mem.end()){
                mem.insert(std::make_pair(location, binaryToLong));
            }
            else mem.at(location) = binaryToLong;
        }
    }
    long res{0};
    for(auto& [key, val] : mem){
        res += val;
    }
    std::cout << res << "\n";
    return 0;
}