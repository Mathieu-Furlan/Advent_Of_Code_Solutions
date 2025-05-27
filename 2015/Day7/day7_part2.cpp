#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <array>

int logicalProcessing(std::string gate, std::unordered_map<std::string, std::array<std::string, 3>>& logic, std::unordered_map<std::string, int>& val){
    if(val.find(gate) != val.end()){        // si on a déjà la valeur
        return val.at(gate);
    }
    else if(gate[0] > 47 && gate[0] < 58){      // dans le cas où il s'agit d'un entier
        return std::stoi(gate);
    }
    std::string operand{logic.at(gate)[0]};
    std::string operator1{logic.at(gate)[1]};
    std::string operator2;
    if(logic.at(gate)[2].length() > 0){
        operator2 = logic.at(gate)[2];
    }
    if(operand.length() == 0){
        return logicalProcessing(operator1, logic, val);
    }
    int op1{logicalProcessing(logic.at(gate)[1], logic, val)};
    int op2;
    if(operator2.length() > 0){
        op2 = logicalProcessing(logic.at(gate)[2], logic, val);
    }
    if(operand == "AND"){
        int res{op1 & op2};
        val.insert(std::make_pair(gate, res));
        return res;
    }
    else if(operand == "OR"){
        int res{op1 | op2};
        val.insert(std::make_pair(gate, res));
        return res;
    }
    else if(operand == "NOT"){
        int res{~op1};
        val.insert(std::make_pair(gate, res));
        return res;
    }
    else if(operand == "RSHIFT"){
        int res{op1 >> op2};
        val.insert(std::make_pair(gate, res));
        return res;
    }
    else if(operand == "LSHIFT"){
        int res{op1 << op2};
        val.insert(std::make_pair(gate, res));
        return res;
    }
    return 0;
}

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<std::string, std::array<std::string, 3>> logicGates;
    std::unordered_map<std::string, int> values;
    while(getline(file, s)){
        std::string outputWire;
        std::string inputWire;
        std::array<std::string, 3> prev;
        bool firstArg{true};
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] > 96 && s[i] < 123){
                int index{i};
                while(s[index] > 96 && s[index] < 123){
                    inputWire += s[index];
                    index++;
                }
                if(firstArg){
                    prev[1] = inputWire;
                    firstArg = false;
                    inputWire.clear();
                }
                else prev[2] = inputWire;
                i = index;
            }
            else if(s[i] > 47 && s[i] < 58){
                int index{i};
                while(s[index] > 47 && s[index] < 58){
                    inputWire += s[index];
                    index++;
                }
                if(firstArg){
                    prev[1] = inputWire;
                    firstArg = false;
                    inputWire.clear();
                }
                else prev[2] = inputWire;
                i = index;
            }
            else if(s[i] > 64 && s[i] < 91){
                int index{i};
                while(s[index] > 64 && s[index] < 91){
                    inputWire += s[index];
                    index++;
                }
                prev[0] = inputWire;
                inputWire.clear();
                i = index;
            }
            else if(s[i] == '>'){
                int index{i + 1};
                while(index < s.length()){
                    if(s[index] > 96 && s[index] < 123){
                        outputWire += s[index];
                    }
                    index++;
                }
                break;
            }
        }
        if(outputWire == "b"){
            values.insert(std::make_pair("b", 46065));
        }
        else if(prev[0].length() == 0 && prev[1][0] > 47 && prev[1][0] < 58){            // dans le cas où la valeur est donnée directement
            values.insert(std::make_pair(outputWire, std::stoi(prev[1])));
        }
        else logicGates.insert(std::make_pair(outputWire, prev));
    }
    /*for(auto& [key, val] : logicGates){
        std::cout << key << " ";
        for(auto& op : val){
            std::cout << op << " ";
        }
        std::cout << "\n";
    }
    for(auto& [key, val] : values){
        std::cout << key << " " << val << "\n";
    }
    std::cout << "end populate" << "\n";*/
    int res{logicalProcessing("a", logicGates, values)};
    std::cout << res << "\n";
    return 0;
}