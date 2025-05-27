#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream infile("input");
    std::string s;
    int res = 0;
    std::string nbre1;
    std::string nbre2;
    while(infile >> s){
        int gauche = 0;
        while(s[gauche] > 57){
            if(gauche < s.length() - 3 && s[gauche] == 111 && s[gauche + 1] == 110 && s[gauche + 2] == 101){
                nbre1 = "1";
                break;
            }
            else if(gauche < s.length() - 3 && s[gauche] == 116 && s[gauche + 1] == 119 && s[gauche + 2] == 111){
                nbre1 = "2";
                break;
            }
            else if(gauche < s.length() - 5 && s[gauche] == 116 && s[gauche + 1] == 104 && s[gauche + 2] == 114 && s[gauche + 3] == 101 && s[gauche + 4] == 101){
                nbre1 = "3";
                break;
            }
            else if(gauche < s.length() - 4 && s[gauche] == 102 && s[gauche + 1] == 111 && s[gauche + 2] == 117 && s[gauche + 3] == 114){
                nbre1 = "4";
                break;
            }
            else if(gauche < s.length() - 4 && s[gauche] == 102 && s[gauche + 1] == 105 && s[gauche + 2] == 118 && s[gauche + 3] == 101){
                nbre1 = "5";
                break;
            }
            else if(gauche < s.length() - 3 && s[gauche] == 115 && s[gauche + 1] == 105 && s[gauche + 2] == 120){
                nbre1 = "6";
                break;
            }
            else if(gauche < s.length() - 5 && s[gauche] == 115 && s[gauche + 1] == 101 && s[gauche + 2] == 118 && s[gauche + 3] == 101 && s[gauche + 4] == 110){
                nbre1 = "7";
                break;
            }
            else if(gauche < s.length() - 5 && s[gauche] == 101 && s[gauche + 1] == 105 && s[gauche + 2] == 103 && s[gauche + 3] == 104 && s[gauche + 4] == 116){
                nbre1 = "8";
                break;
            }
            else if(gauche < s.length() - 4 && s[gauche] == 110 && s[gauche + 1] == 105 && s[gauche + 2] == 110 && s[gauche + 3] == 101){
                nbre1 = "9";
                break;
            }
            gauche++;
        }
        if(s[gauche] <= 57){
            nbre1 = s[gauche];
        }
        int droite = s.length() - 1;
        while(s[droite] > 57){
            if(droite > 1 && s[droite - 2] == 111 && s[droite - 1] == 110 && s[droite] == 101){
                nbre2 = "1";
                break;
            }
            else if(droite > 1 && s[droite - 2] == 116 && s[droite - 1] == 119 && s[droite] == 111){
                nbre2 = "2";
                break;
            }
            else if(droite > 4 && s[droite - 4] == 116 && s[droite - 3] == 104 && s[droite - 2] == 114 && s[droite - 1] == 101 && s[droite] == 101){
                nbre2 = "3";
                break;
            }
            else if(droite > 3 && s[droite - 3] == 102 && s[droite - 2] == 111 && s[droite - 1] == 117 && s[droite] == 114){
                nbre2 = "4";
                break;
            }
            else if(droite > 3 && s[droite - 3] == 102 && s[droite - 2] == 105 && s[droite - 1] == 118 && s[droite] == 101){
                nbre2 = "5";
                break;
            }
            else if(droite > 2 && s[droite - 2] == 115 && s[droite - 1] == 105 && s[droite] == 120){
                nbre2 = "6";
                break;
            }
            else if(droite > 4 && s[droite - 4] == 115 && s[droite - 3] == 101 && s[droite - 2] == 118 && s[droite - 1] == 101 && s[droite] == 110){
                nbre2 = "7";
                break;
            }
            else if(droite > 4 && s[droite - 4] == 101 && s[droite - 3] == 105 && s[droite - 2] == 103 && s[droite - 1] == 104 && s[droite] == 116){
                nbre2 = "8";
                break;
            }
            else if(droite > 3 && s[droite - 3] == 110 && s[droite - 2] == 105 && s[droite - 1] == 110 && s[droite] == 101){
                nbre2 = "9";
                break;
            }
            droite--;
        }
        if(s[droite] <= 57){
            nbre2 = s[droite];
        }
        std::string nbre = std::string() + nbre1 + nbre2;
        int temp{std::stoi(nbre)};
        res = res + temp;
    }
    std::cout << res << "\n";
    return res;
}
