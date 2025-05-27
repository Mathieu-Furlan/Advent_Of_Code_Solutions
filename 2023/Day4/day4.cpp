#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    while(getline(file, s)){
        std::cout << "new card" << "\n";
        std::vector<int> winning;
        std::vector<int> nbr;
        std::string temp;
        int i{10};
        while(s[i] != 124){
            if(s[i] <= 57 && s[i] >= 48){
                temp.push_back(s[i]);
            }
            else if(temp.length() > 0){
                std::cout << "wtemp: " << temp << "\n";
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
                std::cout << "nbrtemp: " << temp << "\n";
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
        int points{0};
        while(w < winning.size() && n < nbr.size()){
            std::cout << "winning: " << winning[w] << "\n";
            std::cout << "number: " << nbr[n] << "\n";
            if(winning[w] > nbr[n]){
                n++;
            }
            else if(nbr[n] > winning[w]){
                w++;
            }
            else{
                if(points == 0){
                    points = 1;
                }
                else points *= 2;
                n++;
            }
        }
        res += points;
    }
    std::cout << res << "\n";
    return res;
}