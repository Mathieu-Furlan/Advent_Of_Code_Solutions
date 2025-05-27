#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    std::string programOrder{"abcdefghijklmnop"};
    getline(file, s);
    for(int i = 0; i <= s.length() - 1; i++){
        if(s[i] == 'x'){
            bool slash{false};
            std::string index1;
            std::string index2;
            for(int k = i + 1; k <= i + 5; k++){
                if(!slash && s[k] < 58 && s[k] > 47){
                    index1 += s[k];
                }
                else if(s[k] == '/'){
                    slash = true;
                }
                else if(slash && s[k] < 58 && s[k] > 47){
                    index2 += s[k];
                }
            }
            std::swap(programOrder[std::stoi(index1)], programOrder[std::stoi(index2)]);
            i += 3;
        }
        else if(s[i] == 's'){
            if(s[i + 2] == ','){
                std::string temp{programOrder.substr(programOrder.length() - (s[i + 1] - '0'))};
                programOrder.erase(programOrder.length() - (s[i + 1] - '0'));
                temp += programOrder;
                programOrder = temp;
            }
            else{                          // si l'index a deux chiffres
                std::string index;
                index += s[i + 1];
                index += s[i + 2];
                std::string temp{programOrder.substr(programOrder.length() - std::stoi(index))};
                programOrder.erase(programOrder.length() - std::stoi(index));
                temp += programOrder;
                programOrder = temp;
            }
            i++;
        }
        else if(s[i] == 'p'){
            char swap1{s[i + 1]};
            char swap2{s[i + 3]};
            for(int j = 0; j <= programOrder.length() - 1; j++){
                if(programOrder[j] == swap1){
                    programOrder[j] = swap2;
                }
                else if(programOrder[j] == swap2){
                    programOrder[j] = swap1;
                }
            }
            i += 3;
        }
    }
    std::cout << programOrder << "\n";
    return 0;
}