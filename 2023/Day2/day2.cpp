// utiliser getline à la place de infile pour avoir une ligne complète avec les espaces

#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    int game{0};
    while(getline(file, s)){
        game++;
        bool possible{true};
        std::cout << s << "\n";
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] == 103){
                std::string temp;
                for(int j = i - 3; j < i - 1; j++){
                    if(s[j] > 47){
                        temp.push_back(s[j]);
                    }
                }
                std::cout << temp << "\n";
                int nbre{std::stoi(temp)};
                if(nbre > 13){
                    possible = false;
                }
                i++;
            }
            else if(s[i] == 98){
                std::string temp;
                for(int j = i - 3; j < i - 1; j++){
                    if(s[j] > 47){
                        temp.push_back(s[j]);
                    }
                }
                std::cout << temp << "\n";
                int nbre{std::stoi(temp)};
                if(nbre > 14){
                    possible = false;
                }
            }
            else if(s[i] == 114){
                std::string temp;
                for(int j = i - 3; j < i - 1; j++){
                    if(s[j] > 47){
                        temp.push_back(s[j]);
                    }
                }
                std::cout << temp << "\n";
                int nbre{std::stoi(temp)};
                if(nbre > 12){
                    possible = false;
                }
            }
        }
        if(possible){
            res += game;
        }
    }
    std::cout << res << "\n";
    return 0;
}