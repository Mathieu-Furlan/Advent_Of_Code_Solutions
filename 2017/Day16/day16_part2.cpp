#include <fstream>
#include <string>
#include <iostream>
#include <unordered_set>

int main(){
    std::ifstream file("input");
    std::string s;
    std::string programOrder{"abcdefghijklmnop"};
    std::string targetProgram;
    std::unordered_set<std::string> danceEnding;
    danceEnding.insert(programOrder);
    bool cycle{false};
    int cycleLength{0};
    getline(file, s);
    while(!cycle){           // on cherche l'ordre des caractères du cycle
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
                else{
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
        cycleLength++;
        if(danceEnding.find(programOrder) != danceEnding.end()){
            targetProgram = programOrder;
            programOrder = "abcdefghijklmnop";
            cycle = true;
        }
        else danceEnding.insert(programOrder);
    }
    int startCycle{0};
    while(programOrder != targetProgram){        // on cherche le point de départ du cycle
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
                else{
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
        startCycle++;
    }
    int cycleMove{cycleLength - startCycle};        // le nombre d'opérations dans le cycle
    int remainingCycle{(1000000000 - startCycle) % cycleMove};  // le nombre de cycles restants après le dernier cycle complet pour arriver à 1000000000
    while(remainingCycle > 0){
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
                else{
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
        remainingCycle--;
    }
    std::cout << programOrder << "\n";
    return 0;
}