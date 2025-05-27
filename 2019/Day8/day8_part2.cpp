#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    while(getline(file, s)){
        for(int i = 0; i <= 5; i++){
            std::string row;
            for(int j = 0; j <= 24; j++){
                for(int k = i * 25 + j; k <= s.length() - 1; k = k + 150){
                    if(s[k] == '1'){                                           // les '1' forment des lettres
                        row += s[k];
                        break;
                    }
                    else if(s[k] == '0'){                                      // les '0' représentent les espaces entre les lettres
                        row += ' ';
                        break;
                    }
                }
            }
            std::cout << row << "\n";
        }
    }
    return 0;
}