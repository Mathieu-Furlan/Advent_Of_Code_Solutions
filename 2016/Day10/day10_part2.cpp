#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <unordered_map>
#include <vector>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<int, std::array<int, 2>> giveTo;
    std::unordered_map<int, std::array<int, 2>> chips;
    std::vector<int> bots;
    std::array<int, 3> outputs;
    while(getline(file, s)){
        if(s[0] == 'v'){
            std::string numBuilder;
            int index{6};
            while(s[index] > 47 && s[index] < 58){
                numBuilder += s[index];
                index++;
            }
            int value{std::stoi(numBuilder)};
            index += 13;
            numBuilder.clear();
            while(s[index] > 47 && s[index] < 58){
                numBuilder += s[index];
                index++;
            }
            int bot{std::stoi(numBuilder)};
            if(chips.find(bot) == chips.end()){
                std::array<int, 2> temp{{value, - 1}};
                chips.insert(std::make_pair(bot, temp));
            }
            else{
                chips.at(bot)[1] = value;
                bots.push_back(bot);
            }
        }
        else{
            std::string numBuilder;
            int index{4};
            while(s[index] > 47 && s[index] < 58){
                numBuilder += s[index];
                index++;
            }
            int bot{std::stoi(numBuilder)};
            index += 18;
            if(s[index] < 48 || s[index] > 57){             // dans le cas où il y a output à la place de bot
                index += 3;
            }
            numBuilder.clear();
            while(s[index] > 47 && s[index] < 58){
                numBuilder += s[index];
                index++;
            }
            int low{std::stoi(numBuilder)};
            index += 17;
            if(s[index] < 48 || s[index] > 57){             // dans le cas où il y a output à la place de bot
                index += 3;
            }
            numBuilder.clear();
            while(s[index] > 47 && s[index] < 58){
                numBuilder += s[index];
                index++;
            }
            int high{std::stoi(numBuilder)};
            std::array<int, 2> temp{{low, high}};
            giveTo.insert(std::make_pair(bot, temp));
        }
    }
    bool found{false};
    int res;
    while(!found){
        std::vector<int> next;
        for(int i = 0; i < bots.size(); i++){
            int maxVal = std::max(chips.at(bots[i])[0], chips.at(bots[i])[1]);
            int minVal = std::min(chips.at(bots[i])[0], chips.at(bots[i])[1]);
            if(maxVal == 61 && minVal == 17){
                res = bots[i];
                found = true;
                break;
            }
            int botMax{giveTo.at(bots[i])[1]};
            int botMin{giveTo.at(bots[i])[0]};
            if(chips.find(botMax) == chips.end()){
                std::array<int, 2> temp{{maxVal, -1}};
                chips.insert(std::make_pair(botMax, temp));
            }
            else{
                chips.at(botMax)[1] = maxVal;
                next.push_back(botMax);
            }
            if(chips.find(botMin) == chips.end()){
                std::array<int, 2> temp{{minVal, -1}};
                chips.insert(std::make_pair(botMin, temp));
            }
            else{
                chips.at(botMin)[1] = minVal;
                next.push_back(botMin);
            }
        }
        bots = next;
    }
    std::cout << res << "\n";
    return 0;
}