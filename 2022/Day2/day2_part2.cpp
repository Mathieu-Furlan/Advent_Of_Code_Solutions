#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    while(getline(file, s)){
        if(s[0] == 'A'){
            if(s[2] == 'X'){
                res += 3;
            }
            else if(s[2] == 'Y'){
                res += 4;
            }
            else if(s[2] == 'Z'){
                res += 8;
            }
        }
        else if(s[0] == 'B'){
            if(s[2] == 'X'){
                res += 1;
            }
            else if(s[2] == 'Y'){
                res += 5;
            }
            else if(s[2] == 'Z'){
                res += 9;
            }
        }
        else if(s[0] == 'C'){
            if(s[2] == 'X'){
                res += 2;
            }
            else if(s[2] == 'Y'){
                res += 6;
            }
            else if(s[2] == 'Z'){
                res += 7;
            }
        }
    }
    std::cout << res << "\n";
    return res;
}