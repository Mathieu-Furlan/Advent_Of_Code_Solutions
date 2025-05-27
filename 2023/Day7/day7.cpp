#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

int main(){
    std::ifstream infile("input");
    std::string s;
    std::vector<std::vector<int>> hands;
    std::vector<int> temp; 
    int divisor{0};
    int res{0};
    while(infile >> s){
        divisor++;
        if(divisor % 2 == 0){
            temp.push_back(stoi(s));
            hands.push_back(temp);
            temp.clear();
        }
        else{
            for(int i = 0; i <= s.length() - 1; i++){
                if(s[i] == 65){
                    temp.push_back(14);
                }
                else if(s[i] == 75){
                    temp.push_back(13);
                }
                else if(s[i] == 81){
                    temp.push_back(12);
                }
                else if(s[i] == 74){
                    temp.push_back(11);
                }
                else if(s[i] == 84){
                    temp.push_back(10);
                }
                else{
                    int cardValue = s[i] - '0';
                    temp.push_back(cardValue);
                }
            }
            std::unordered_map<int, int> typeHand;
            int figure{0};
            for(int i = 0; i <= temp.size() - 1; i++){
                std::cout << "temp[i] " << temp[i] << "\n";
                if(typeHand.find(temp[i]) != typeHand.end()){
                    typeHand.at(temp[i]) += 1;
                }
                else typeHand.insert(std::make_pair(temp[i], 1));
            }
            for(auto& [key, value]: typeHand){                 // vérifie le type de la main
                std::cout << "key " << key << "\n";
                std::cout << "value " << value << "\n";
                std::cout << "figure " << figure << "\n";
                if(value == 2){
                    if(figure == 1){
                        figure = 2;
                    }
                    else if(figure == 3){
                        figure = 4;
                    }
                    else figure = 1;                 
                }
                if(value == 3){
                    if(figure == 1){
                        figure = 4;
                    }
                    else figure = 3;
                }
                if(value == 4){
                    figure = 5;
                }
                if(value == 5){
                    figure = 6;
                }
            }
            temp.push_back(figure);
        }
    }
    std::sort(hands.begin(), hands.end(), [](const std::vector<int>& a, const std::vector<int>& b){
        if(a[5] < b[5]){            // si le type de la main est supérieur à l'autre
            return true;
        }
        else if(a[5] > b[5]){
            return false;
        }
        else{
            for(int i = 0; i < 5; i++){   // si les deux mains ont chacune des cartes totalement distinctes
                if(a[i] < b[i]){
                    return true;
                }
                else if(a[i] > b[i]){
                    return false;
                }
            }
        }
        return true;
    });
    for(int j = 0; j <= hands.size() - 1; j++){
        res += (j + 1) * hands[j][6];
        std::cout << "new hand " << "\n";
        for(int m = 0; m <= hands[j].size() - 1; m++){
            std::cout << "card " << hands[j][m] << "\n";
        }
    }
    std::cout << res << "\n";
    return res;
}