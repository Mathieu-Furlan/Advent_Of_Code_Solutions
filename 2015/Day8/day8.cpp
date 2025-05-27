#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    int code{0};
    int memory{0};
    while(getline(file, s)){
        code++;
        for(int i = 1; i <= s.length() - 2; i++){
            if(s[i] == 92){
                if(s[i + 1] == 92 || s[i + 1] == 34){
                    code += 2;
                    memory++;
                    i++;
                }
                else if(s[i + 1] == 'x'){
                    code += 4;
                    memory++;
                    i += 3;
                }
            }
        }
        code++;
    }
    std::cout << code - memory << "\n";
    return code - memory;
}