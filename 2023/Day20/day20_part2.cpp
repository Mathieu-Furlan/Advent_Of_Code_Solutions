#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <array>
#include <queue>
#include <numeric>

// pour obtenir le graphique en png: dot -Tpng graphDay20.gv -o graphDay20.png
int main(){
    std::ofstream outfile ("graphDay20.gv");
    outfile << "digraph G {" << std::endl;
    std::ifstream file("input");
    std::string s;
    std::string arrowRelation{"-> "};
    std::vector<std::string> conjunctionList;
    std::unordered_map<std::string, std::vector<std::string>> flipFlop;
    std::unordered_map<std::string, bool> flipFlopStatus;
    std::unordered_map<std::string, std::vector<std::string>> conjunction;
    std::unordered_map<std::string, std::vector<std::array<std::string, 2>>> conjunctionInput;
    std::vector<std::string> broadCast;
    while(getline(file, s)){
        long unsigned int firstSpaceIndex{s.find(' ')};
        std::string from{s.substr(1, firstSpaceIndex)};
        if(s[0] == '&'){
            conjunctionList.push_back(from);
        }
        std::string to;
        for(int i = firstSpaceIndex + 1; i < s.length(); i++){
            if(s[i] >= 97 && s[i] <= 122){
                to += s[i];
            }
            else if(s[i] == ','){
                outfile << from << arrowRelation << to << ';' << std::endl;
                to.clear();
            }
        }
        outfile << from << arrowRelation << to << ';' << std::endl;
        if(s[0] == '%'){
            std::vector<std::string> values;
            std::string temp;
            std::string key;
            int index{1};
            while(s[index] > 96 && s[index] < 123){
                key.push_back(s[index]);
                index++;
            }
            for(int i = 6; i < s.length(); i++){
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
            flipFlopStatus.insert(std::make_pair(key, false));
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
            for(int i = 6; i < s.length(); i++){
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
            for(int i = 14; i < s.length(); i++){
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
    for(int i = 0; i < conjunctionList.size(); i++){
        outfile << conjunctionList[i] << " [style=filled,color=\"yellow\"];" << std::endl;
    }
    outfile << "rx [style=filled,color=\"red\"];" << std::endl;
    outfile << "}" << std::endl;
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
    std::array<int, 4> loopsSizes;
    for(int i = 0; i < broadCast.size(); i++){
        std::queue<std::array<std::string, 3>> pulseOrder;
        bool lowSent{false};
        int loopLength{0};
        while(!lowSent){
            pulseOrder.push({"low", broadCast[i], "broadcaster"});          // tant que l'on ne connait pas la taille de la boucle on envoie un signal faible
            loopLength++;
            while(pulseOrder.size() > 0 && !lowSent){
                long unsigned level{pulseOrder.size()};
                while(level > 0){
                    std::string currPulse{pulseOrder.front()[0]};
                    std::string currElem{pulseOrder.front()[1]};
                    std::string sender{pulseOrder.front()[2]};
                    if(currPulse == "low" && (currElem == "dt" || currElem == "qs" || currElem == "js" || currElem == "ts")){
                        std::cout << "loopLength: " << loopLength << "\n";
                        loopsSizes[i] = loopLength;
                        lowSent = true;
                        break;
                    }
                    pulseOrder.pop();
                    if(flipFlop.find(currElem) != flipFlop.end()){
                        if(currPulse == "low"){
                            if(flipFlopStatus.at(currElem) == true){
                                flipFlopStatus.at(currElem) = false;
                                for(auto& output : flipFlop.at(currElem)){
                                    pulseOrder.push({"low", output, currElem});
                                }
                            }
                            else{
                                flipFlopStatus.at(currElem) = true;
                                for(auto& output : flipFlop.at(currElem)){
                                    pulseOrder.push({"high", output, currElem});
                                }
                            }
                        }
                    }
                    else if(conjunction.find(currElem) != conjunction.end()){
                        for(auto& input : conjunctionInput.at(currElem)){
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
                            }
                        }
                        else{
                            for(auto& receiver : conjunction.at(currElem)){
                                pulseOrder.push({"high", receiver, currElem});
                            }
                        }
                    }
                    level--;
                }
            }
        }  
    }
    long long lcmArg2Arg3{std::lcm(loopsSizes[2], loopsSizes[3])};
    long long lcmArg1Arg2Arg3{std::lcm(loopsSizes[1], lcmArg2Arg3)};
    long long lowestCommonMultiple{std::lcm(loopsSizes[0], lcmArg1Arg2Arg3)};
    std::cout << lowestCommonMultiple << "\n";
    return 0;
}