#include <fstream>
#include <string>
#include <iostream>

long long processlength(long timesDuplicate, std::string& toBeDuplicated){
    long long addToLength{0};
    for(int i = 0; i < toBeDuplicated.length(); i++){
        if(toBeDuplicated[i] == 40){
            int sequenceLength;
            int timesRepetion;
            std::string numBuilder;
            i++;
            while(toBeDuplicated[i] > 47 && toBeDuplicated[i] < 58){
                numBuilder += toBeDuplicated[i];
                i++;
            }
            sequenceLength = std::stoi(numBuilder);
            numBuilder.clear();
            i++;
            while(toBeDuplicated[i] > 47 && toBeDuplicated[i] < 58){
                numBuilder += toBeDuplicated[i];
                i++;
            }
            timesRepetion = std::stoi(numBuilder);
            i++;
            std::string nextToDuplicate{toBeDuplicated.substr(i, sequenceLength)};
            addToLength += processlength(timesRepetion, nextToDuplicate);
            i += sequenceLength - 1;
        }
        else addToLength++;
    }
    return addToLength * timesDuplicate;
}

int main(){
    long long res{0};
    std::ifstream file("input");
    std::string s;
    getline(file, s);
    for(int i = 0; i < s.length(); i++){
        if(s[i] == 40){
            int sequenceLength;
            int timesRepetion;
            std::string numBuilder;
            i++;
            while(s[i] > 47 && s[i] < 58){
                numBuilder += s[i];
                i++;
            }
            sequenceLength = std::stoi(numBuilder);
            numBuilder.clear();
            i++;
            while(s[i] > 47 && s[i] < 58){
                numBuilder += s[i];
                i++;
            }
            timesRepetion = std::stoi(numBuilder);
            i++;
            std::string toDuplicate{s.substr(i, sequenceLength)};
            res += processlength(timesRepetion, toDuplicate);
            i += sequenceLength - 1;
        }
        else res++;
    }
    std::cout << res << "\n";
    return 0;
}