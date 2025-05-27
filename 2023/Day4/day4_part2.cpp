#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    int cards[189];
    std::fill(std::begin(cards), std::end(cards), 1);   // toutes les valeurs du tableau à 1;
    int currentCard{0};
    while(getline(file, s)){
        std::vector<int> winning;
        std::vector<int> nbr;
        std::string temp;
        int i{10};
        res += cards[currentCard];
        std::cout << cards[currentCard] << "\n";
        while(s[i] != 124){
            if(s[i] <= 57 && s[i] >= 48){
                temp.push_back(s[i]);
            }
            else if(temp.length() > 0){
                winning.push_back(stoi(temp));
                temp.clear();
            }
            i++;
        }
        while(i <= s.length() - 1){
            if(s[i] <= 57 && s[i] >= 48){
                temp.push_back(s[i]);
            }
            else if(temp.length() > 0){
                nbr.push_back(stoi(temp));
                temp.clear();
            }
            i++;
        }
        nbr.push_back(stoi(temp));
        temp.clear();
        std::sort(winning.begin(), winning.end());
        std::sort(nbr.begin(), nbr.end());
        int w{0};
        int n{0};
        int card{currentCard + 1};
        while(w < winning.size() && n < nbr.size()){
            if(winning[w] > nbr[n]){
                n++;
            }
            else if(nbr[n] > winning[w]){
                w++;
            }
            else{
                cards[card] += cards[currentCard];
                card++;
                n++;
            }
        }
        std::cout << "points: " << card - 1 << "\n";
        std::cout << "card: " << currentCard << "\n";
        std::cout << "nbre: " << cards[currentCard] << "\n";
        currentCard++;
    }
    std::cout << res << "\n";
    return res;
}