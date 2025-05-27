#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<std::string, std::vector<std::string>> flipFlop;
    std::unordered_map<std::string, bool> flipFlopStatus;
    std::unordered_map<std::string, std::vector<std::string>> conjunction;
    std::unordered_map<std::string, std::vector<std::array<std::string, 2>>> conjunctionInput;
    std::vector<std::string> broadCast;
    while(getline(file, s)){
        if(s[0] == '%'){
            std::vector<std::string> values;
            std::string temp;
            std::string key;
            int index{1};
            while(s[index] > 96 && s[index] < 123){
                key.push_back(s[index]);
                index++;
            }
            for(int i = 6; i <= s.length() - 1; i++){
                if(s[i] > 96 && s[i] < 123){
                    temp.push_back(s[i]);
                }
                else if(s[i] == ','){
                    values.push_back(temp);
                    temp.clear();
                }
            }
            values.push_back(temp);
            flipFlop.insert(std::make_pair(key, values));
            flipFlopStatus.insert(std::make_pair(key, false));   // false indique off
        }
        else if(s[0] == '&'){
            std::vector<std::string> values;
            std::string temp;
            std::string key;
            int index{1};
            while(s[index] > 96 && s[index] < 123){
                key.push_back(s[index]);
                index++;
            }
            for(int i = 6; i <= s.length() - 1; i++){
                if(s[i] > 96 && s[i] < 123){
                    temp.push_back(s[i]);
                }
                else if(s[i] == ','){
                    values.push_back(temp);
                    temp.clear();
                }
            }
            values.push_back(temp);
            conjunction.insert(std::make_pair(key, values));
            std::vector<std::array<std::string, 2>> emptyVec;
            conjunctionInput.insert(std::make_pair(key, emptyVec));
        }
        else{
            std::string temp;
            for(int i = 14; i <= s.length() - 1; i++){
                if(s[i] > 96 && s[i] < 123){
                    temp.push_back(s[i]);
                }
                else if(s[i] == ','){
                    broadCast.push_back(temp);
                    temp.clear();
                }
            }
            broadCast.push_back(temp);
        }
    }
    for(auto& [key, value] : flipFlop){
        for(auto& elem : value){
            if(conjunction.find(elem) != conjunction.end()){
                conjunctionInput.at(elem).push_back({key, "low"});
            }
        }
    }
    for(auto& [key, value] : conjunction){
        for(auto& elem : value){
            if(conjunction.find(elem) != conjunction.end()){
                conjunctionInput.at(elem).push_back({key, "low"});
            }
        }
    }
    int countLow{0};
    int countHigh{0};
    for(int k = 1; k <= 1000; k++){
        countLow++;
        std::queue<std::array<std::string, 3>> pulseOrder;
        for(int j = 0; j <= broadCast.size() - 1; j++){
            pulseOrder.push({"low", broadCast[j], "broadcaster"});
            countLow++;
        }
        while(pulseOrder.size() > 0){
            long unsigned level{pulseOrder.size()};
            while(level > 0){
                std::string currPulse{pulseOrder.front()[0]};
                std::string currElem{pulseOrder.front()[1]};
                std::string sender{pulseOrder.front()[2]};              // l'élément qui a envoyé le signal requis pour mettre à jour le signal reçu des conjunctions
                pulseOrder.pop();
                if(flipFlop.find(currElem) != flipFlop.end()){
                    if(currPulse == "low"){
                        if(flipFlopStatus.at(currElem) == true){
                            flipFlopStatus.at(currElem) = false;
                            for(auto& output : flipFlop.at(currElem)){
                                pulseOrder.push({"low", output, currElem});
                                countLow++;
                            }
                        }
                        else{
                            flipFlopStatus.at(currElem) = true;
                            for(auto& output : flipFlop.at(currElem)){
                                pulseOrder.push({"high", output, currElem});
                                countHigh++;
                            }
                        }
                    }
                }
                else if(conjunction.find(currElem) != conjunction.end()){
                    for(auto& input : conjunctionInput.at(currElem)){       // la vérification des signaux reçus se fait avant d'envoyer d'autres pulsations
                        if(input[0] == sender){
                            input[1] = currPulse;
                            break;
                        }
                    }
                    bool pastInputs{true};
                    for(auto& elems : conjunctionInput.at(currElem)){
                        if(elems[1] == "low"){
                            pastInputs = false;
                            break;
                        }
                    }
                    if(pastInputs){
                        for(auto& receiver : conjunction.at(currElem)){
                            pulseOrder.push({"low", receiver, currElem});
                            countLow++;
                        }
                    }
                    else{
                        for(auto& receiver : conjunction.at(currElem)){
                            pulseOrder.push({"high", receiver, currElem});
                            countHigh++;
                        }
                    }
                }
                level--;
            }
        }
    }
    std::cout << countLow << "\n";
    std::cout << countHigh << "\n";
    long res{countLow * countHigh};
    std::cout << res << "\n";
    return 0;
}