#include <fstream>
#include <string>
#include <iostream>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    std::array<bool, 7> fields{false, false, false, false, false, false, false};
    while(getline(file, s) || file.peek() == EOF){              // la dernière ligne vide est toujours ignorée
        if(s.length() == 0){
            bool allTrue{true};
            for(int i = 0; i < 7; i++){
                if(fields[i] == false){
                    allTrue = false;
                }
            }
            if(allTrue){
                res++;
            }
            for(int i = 0; i < 7; i++){
                fields[i] = false;
            }
        }
        else{
            for(int i = 3; i <= s.length() - 1; i++){
                if(s[i] == ':'){
                    if(s.substr(i - 3, 3) == "byr"){
                        fields[0] = true;
                    }
                    else if(s.substr(i - 3, 3) == "iyr"){
                        fields[1] = true;
                    }
                    else if(s.substr(i - 3, 3) == "eyr"){
                        fields[2] = true;
                    }
                    else if(s.substr(i - 3, 3) == "hgt"){
                        fields[3] = true;
                    }
                    else if(s.substr(i - 3, 3) == "hcl"){
                        fields[4] = true;
                    }
                    else if(s.substr(i - 3, 3) == "ecl"){
                        fields[5] = true;
                    }
                    else if(s.substr(i - 3, 3) == "pid"){
                        fields[6] = true;
                    }
                }
            }
        }
        if(file.eof()){
            break;
        }
    }
    std::cout << res << "\n";
    return 0;
}