#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <bitset>
#include <vector>

void addressGenerator(std::vector<long>& found, std::string& address, int index, std::string current){
    if(index == address.length()){
        long binaryToLong = std::stol(current, nullptr, 2);         // binaire vers long
        found.push_back(binaryToLong);
        return;
    }
    else if(address[index] == '0' || address[index] == '1'){
        addressGenerator(found, address, index + 1, current + address[index]);
    }
    else if(address[index] == 'X'){
        addressGenerator(found, address, index + 1, current + '0');
        addressGenerator(found, address, index + 1, current + '1');
    }
}

int main(){
    std::ifstream file("input");
    std::string s;
    std::string mask;
    std::unordered_map<long, long> mem;
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
            std::string bitRep = std::bitset<36>(location).to_string();        // représentation binaire
            std::string toBeAddressed;
            for(int i = 0; i < 36; i++){
                if(mask[i] == '0'){
                    toBeAddressed += bitRep[i];
                }
                else toBeAddressed += mask[i];
            }
            std::cout << "tobeaddressed " << toBeAddressed << "\n";
            std::vector<long> toUpdate;
            addressGenerator(toUpdate, toBeAddressed, 0, "");
            for(auto& update : toUpdate){
                if(mem.find(update) == mem.end()){
                    mem.insert(std::make_pair(update, value));
                }
                else mem.at(update) = value;
            }
        }
    }
    long res{0};
    for(auto& [key, val] : mem){
        res += val;
    }
    std::cout << res << "\n";
    return 0;
}