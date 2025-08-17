#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <algorithm>

int main(){
    std::ifstream file("input");
    std::string s;
    while(getline(file, s)){
        std::array<std::array<int, 2>, 26> freqs;
        for(int i = 0; i < 26; i++){
            freqs[i][0] = i;
            freqs[i][1] = 0;
        }
        int id{0};
        std::string phrase;
        std::string checksum;
        for(int i = 0; i < s.length(); i++){
            if(s[i] > 96 && s[i] < 123){
                freqs[s[i] - 97][1]++;
            }
            else if(s[i] > 47 && s[i] < 58){
                phrase = s.substr(0, i - 1);
                std::string numBuilder;
                while(s[i] > 47 && s[i] < 58){
                    numBuilder += s[i];
                    i++;
                }
                i--;
                id = std::stoi(numBuilder);
            }
            else if(s[i] == '['){
                i++;
                while(s[i] != ']'){
                    checksum += s[i];
                    i++;
                }
            }
        }
        std::sort(freqs.begin(), freqs.end(), [](const std::array<int, 2>& a, const std::array<int, 2>& b){
            if(a[1] > b[1]){
                return true;
            }
            else if(a[1] < b[1]){
                return false;
            }
            else if(a[0] < b[0]){
                return true;
            }
            return false;
        });
        for(int i = 0; i < 5; i++){
            if(checksum[i] != freqs[i][0] + 97){
                break;
            }
            else if(i == 4){
                int rolls{id % 26};
                for(int k = 0; k < phrase.length(); k++){
                    if(phrase[k] == 45){
                        phrase[k] = 32;
                    }
                    else{
                        for(int j = 0; j < rolls; j++){
                            phrase[k] += 1;
                            if(phrase[k] == 123){
                                phrase[k] = 97;
                            }
                        }
                    }
                }
                std::cout << phrase << ' ' << id << "\n";
            }
        }
    }
    return 0;
}