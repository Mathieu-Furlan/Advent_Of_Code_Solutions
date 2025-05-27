#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<std::string, int> registers;
    while(getline(file, s)){
        std::string elem;
        std::string comparator;
        bool decrease{false};
        bool increase{false};
        int firstAmount{0};
        bool secondPart{false};
        bool equal{false};
        bool different{false};
        bool inferior{false};
        bool inferiorEgal{false};
        bool superior{false};
        bool superiorEgal{false};
        int secondAmount{0};
        for(int i = 0; i <= s.length() - 1; i++){
            if(i == 0){
                while(s[i] > 96 && s[i] < 123){
                    elem += s[i];
                    i++;
                }
                if(registers.find(elem) == registers.end()){
                    registers.insert(std::make_pair(elem, 0));
                }
            }
            else if(i > 0 && i == elem.length() + 1){
                if(s[i] == 'd'){
                    decrease = true;
                }
                else if(s[i] == 'i'){
                    increase = true;
                }
            }
            else if(firstAmount == 0 && (s[i] == '-' || (s[i] > 47 && s[i] < 58))){
                std::string temp;
                temp += s[i];
                i++;
                while(s[i] > 47 && s[i] < 58){
                    temp += s[i];
                    i++;
                }
                firstAmount = std::stoi(temp);
            }
            else if(!secondPart && s[i] == 'i' && s[i + 1] == 'f' && s[i + 2] == 32){
                secondPart = true;
                i++;
            }
            else if(secondPart && s[i] > 96 && s[i] < 123){
                while(s[i] > 96 && s[i] < 123){
                    comparator += s[i];
                    i++;
                }
                if(registers.find(comparator) == registers.end()){
                    registers.insert(std::make_pair(comparator, 0));
                }
            }
            else if(comparator.length() > 0){
                if(s[i] == '-' || (s[i] > 47 && s[i] < 58)){
                    std::string temp;
                    temp += s[i];
                    i++;
                    while(s[i] > 47 && s[i] < 58){
                        temp += s[i];
                        i++;
                    }
                    secondAmount = std::stoi(temp);
                }
                else if(s[i] == '!'){
                    different = true;
                }
                else if(s[i] == '=' && s[i + 1] == '='){
                    equal = true;
                }
                else if(s[i] == '>'){
                    if(s[i + 1] == '='){
                        superiorEgal = true;
                    }
                    else superior = true;
                }
                else if(s[i] == '<'){
                    if(s[i + 1] == '='){
                        inferiorEgal = true;
                    }
                    else inferior = true;
                }
            }
        }
        std::cout << "elem " << elem << "\n";
        std::cout << "comparator " << comparator << "\n";
        if(equal){
            if(registers.at(comparator) == secondAmount){
                if(increase){
                    registers.at(elem) += firstAmount;
                }
                else registers.at(elem) -= firstAmount;
            }
        }
        else if(different){
            if(registers.at(comparator) != secondAmount){
                if(increase){
                    registers.at(elem) += firstAmount;
                }
                else registers.at(elem) -= firstAmount;
            }
        }
        else if(superiorEgal){
            if(registers.at(comparator) >= secondAmount){
                if(increase){
                    registers.at(elem) += firstAmount;
                }
                else registers.at(elem) -= firstAmount;
            }
        }
        else if(superior){
            if(registers.at(comparator) > secondAmount){
                if(increase){
                    registers.at(elem) += firstAmount;
                }
                else registers.at(elem) -= firstAmount;
            }
        }
        else if(inferiorEgal){
            if(registers.at(comparator) <= secondAmount){
                if(increase){
                    registers.at(elem) += firstAmount;
                }
                else registers.at(elem) -= firstAmount;
            }
        }
        else if(inferior){
            if(registers.at(comparator) < secondAmount){
                if(increase){
                    registers.at(elem) += firstAmount;
                }
                else registers.at(elem) -= firstAmount;
            }
        }
    }
    int res{0};
    for(auto& [key, value] : registers){
        if(value > res){
            res = value;
        }
    }
    std::cout << res << "\n";
    return res;
}