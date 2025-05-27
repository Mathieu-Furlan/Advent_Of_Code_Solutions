// utiliser getline à la place de infile pour avoir une ligne complète avec les espaces

#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    while(getline(file, s)){
        std::cout << s << "\n";
        int red{0};
        int green{0};
        int blue{0};
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] == 103){
                std::string temp;
                for(int j = i - 3; j < i - 1; j++){
                    if(s[j] > 47){
                        temp.push_back(s[j]);
                    }
                }
                int nbre{std::stoi(temp)};
                if(nbre > green){
                    green = nbre;
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
                int nbre{std::stoi(temp)};
                if(nbre > blue){
                    blue = nbre;
                }
            }
            else if(s[i] == 114){
                std::string temp;
                for(int j = i - 3; j < i - 1; j++){
                    if(s[j] > 47){
                        temp.push_back(s[j]);
                    }
                }
                int nbre{std::stoi(temp)};
                if(nbre > red){
                    red = nbre;
                }
            }
        }
        std::cout << green << "\n";
        std::cout << blue << "\n";
        std::cout << red << "\n";
        res += green * blue * red;
    }
    std::cout << res << "\n";
    return 0;
}