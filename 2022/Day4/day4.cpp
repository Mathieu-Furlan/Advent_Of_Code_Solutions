#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    while(getline(file, s)){
        std::string start1;
        std::string end1;
        std::string start2;
        std::string end2;
        int countDash{0};
        int countComma{0};
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] == '-'){
                countDash++;
            }
            else if(s[i] == ','){
                countComma++;
            }
            else if(countDash == 2){
                end2.push_back(s[i]);
            }
            else if(countComma == 1){
                start2.push_back(s[i]);
            }
            else if(countDash == 1){
                end1.push_back(s[i]);
            }
            else start1.push_back(s[i]);
        }
        int startinterval1{stoi(start1)};
        int endInterval1{stoi(end1)};
        int startInterval2{stoi(start2)};
        int endInterval2{stoi(end2)};
        std::cout << "start1 " << startinterval1 << "\n";
        std::cout << "end1 " << endInterval1 << "\n";
        std::cout << "start2 " << startInterval2 << "\n";
        std::cout << "end2 " << endInterval2 << "\n";
        if((startinterval1 <= startInterval2 && endInterval1 >= endInterval2) || (startInterval2 <= startinterval1 && endInterval2 >= endInterval1)){
            res++;
        }
    }
    std::cout << res << "\n";
    return res;
}