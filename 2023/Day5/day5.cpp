#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <algorithm>
#include <limits>

int main(){
    std::ifstream file("input");
    std::string s;
    std::string temp;
    long elements[20];
    int ind{0};
    getline(file, s);
    for(int i = 7; i <= s.length() - 1; i++){
        if(s[i] == 32){
            elements[ind] = stol(temp);
            ind++;
            temp.clear();
        }
        else temp.push_back(s[i]);
    }
    elements[ind] = stol(temp);
    bool foundDest[20];
    getline(file, s);
    while(getline(file, s)){
        if(s[0] < 58 && s[0] > 47){
            long destination{0};
            long source{0};
            long rangeTo{0};
            int counter{0};
            std::string convert;
            for(int i = 0; i <= s.length() - 1; i++){
                if(s[i] == 32){
                    if(counter == 0){
                        destination = stol(convert);
                        counter++;
                        convert.clear();
                    }
                    else if(counter == 1){
                        source = stol(convert);
                        counter++;
                        convert.clear();
                    }
                }
                else convert.push_back(s[i]);
            }
            rangeTo = stol(convert);
            for(int j = 0; j <= std::size(elements) - 1; j++){
                if(foundDest[j] != true && elements[j] >= source && elements[j] <= source + rangeTo){
                    elements[j] = destination + (elements[j] - source);
                    foundDest[j] = true;
                }
            }
        }
        else{
            std::fill(std::begin(foundDest), std::end(foundDest), false);    // réinitialise le tableau des valeurs pour lesquelles on a trouvé la destination
        }
    }
    double res{std::numeric_limits<double>::infinity()};
    for(int k = 0; k <= std::size(elements) - 1; k++){
        std::cout << elements[k] << "\n";
        if(elements[k] < res){
            res = elements[k];
        }
    }
    std::cout << std::fixed << res << "\n";  // fixed pour ne pas utiliser l'écriture scientifique avec exposant
    return 0;
}