#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    int min{25};                    // par déduction en voyant le fichier
    int max{971};                   // par déduction en voyant le fichier
    bool ticketsInventory{false};
    int res{0};
    while(getline(file, s)){
        if(s[0] == 'n'){
            ticketsInventory = true;
        }
        else if(s.length() > 0 && ticketsInventory){
            std::string numb;
            for(int i = 0; i <= s.length() - 1; i++){
                if(s[i] == ','){
                    int current{std::stoi(numb)};
                    if(current < min || current > max){
                        res += current;
                    }
                    numb.clear();
                }
                else numb += s[i];
            }
            int current{std::stoi(numb)};
            if(current < min || current > max){
                res += current;
            }
        }
    }
    std::cout << res << "\n";
    return 0;
}