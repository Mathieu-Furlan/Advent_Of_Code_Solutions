#include <fstream>
#include <string>
#include <iostream>
#include <array>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    std::array<bool, 7> fields{false, false, false, false, false, false, false};
    while(getline(file, s) || file.peek() == EOF){
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
                        if(std::stoi(s.substr(i + 1, 4)) >= 1920 && std::stoi(s.substr(i + 1, 4)) <= 2002){
                            fields[0] = true;
                        }
                    }
                    else if(s.substr(i - 3, 3) == "iyr"){
                        if(std::stoi(s.substr(i + 1, 4)) >= 2010 && std::stoi(s.substr(i + 1, 4)) <= 2020){
                            fields[1] = true;
                        }
                    }
                    else if(s.substr(i - 3, 3) == "eyr"){
                        if(std::stoi(s.substr(i + 1, 4)) >= 2020 && std::stoi(s.substr(i + 1, 4)) <= 2030){
                            fields[2] = true;
                        }
                    }
                    else if(s.substr(i - 3, 3) == "hgt"){
                        if((s.length() - i >= 6 && s.substr(i + 4, 2) == "cm" && std::stoi(s.substr(i + 1, 3)) >= 150 && std::stoi(s.substr(i + 1, 3)) <= 193) || (s.length() - i >= 5 && s.substr(i + 3, 2) == "in" && std::stoi(s.substr(i + 1, 2)) >= 59 && std::stoi(s.substr(i + 1, 2)) <= 76)){
                            fields[3] = true;
                        }
                    }
                    else if(s.substr(i - 3, 3) == "hcl"){
                        if(s[i + 1] == '#'){
                            bool valid{true};
                            for(int j = i + 2; j <= i + 7; j++){
                                if(!s[i] >= 48 && !s[i] <= 57 || !s[i] >= 97 && !s[i] <= 102){
                                    valid = false;
                                    break;
                                }
                                if(j == i + 7 && s[j + 1] != '\n' && s[j + 1] != ' '){
                                    valid = false;
                                }
                            }
                            if(valid){
                                fields[4] = true;
                            }
                        }
                    }
                    else if(s.substr(i - 3, 3) == "ecl"){
                        if(s[i + 4] == '\n' || s[i + 4] == ' ' && s.substr(i + 1, 3) == "amb" || s.substr(i + 1, 3) == "blu" || s.substr(i + 1, 3) == "brn" || s.substr(i + 1, 3) == "gry" || s.substr(i + 1, 3) == "grn" || s.substr(i + 1, 3) == "hzl" || s.substr(i + 1, 3) == "oth"){
                            fields[5] = true;
                        }
                    }
                    else if(s.substr(i - 3, 3) == "pid"){
                        bool valid{true};
                        for(int j = i + 2; j <= i + 10; j++){
                            if(s[i] <= 47 && s[i] >= 58){
                                valid = false;
                                break;
                            }
                            if(j == i + 10 && s[j + 1] != '\n' && s[j + 1] != ' '){
                                valid = false;
                            }
                        }
                        if(i + 11 > s.length() - 1 && s[i + 11] != ' '){
                            valid = false;
                        }
                        if(valid){
                            fields[6] = true;
                        }
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