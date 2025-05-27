#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <vector>

int main(){
    std::ifstream file("input");
    std::string s;
    std::string string1{"HRBDZFLS"};
    std::string string2{"TBMZR"};
    std::string string3{"ZLCHNS"};
    std::string string4{"SCFJ"};
    std::string string5{"PGHWRZB"};
    std::string string6{"VJZGDNMT"};
    std::string string7{"GLNWFSPQ"};
    std::string string8{"MZR"};
    std::string string9{"MCLGVRT"};
    std::array<std::string, 9> stringCluster{string1, string2, string3, string4, string5, string6, string7, string8, string9};
    while(getline(file, s)){
        if(s[0] == 109){
            std::string moves;
            moves += s[5];
            if(s[6] > 47){
                moves += s[6];
            }
            int stringGive{-1};
            int stringReceive{-1};
            for(int i = 10; i <= s.length() - 1; i++){
                if(s[i] > 47 && s[i] < 58){
                    if(stringGive == -1){
                        stringGive = s[i] - '0' - 1;            // détermine l'idex de la pile qui donne des éléments
                    }
                    else stringReceive = s[i] - '0' - 1;       // détermine l'idex de la pile qui reçoit des éléments
                }
            }
            int transfer{stoi(moves)};
            stringCluster[stringReceive].append(stringCluster[stringGive].substr(stringCluster[stringGive].length() - transfer));  // ajoute à la pile qui reçoit les éléments
            stringCluster[stringGive].erase(stringCluster[stringGive].length() - transfer);          // supprime de la pile qui donne des éléments
        }
    }
    std::string res;
    for(int j = 0; j <= stringCluster.size() - 1; j++){
        res += stringCluster[j][stringCluster[j].length() - 1];
    }
    std::cout << res << "\n";
    return 0;
}