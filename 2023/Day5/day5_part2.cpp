#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <algorithm>
#include <limits>
#include <vector>

int main(){
    std::ifstream file("input");
    std::string s;
    std::string temp;
    std::vector<std::array<long, 2>> elements;
    std::array<long, 2> construct;
    int ind{0};
    getline(file, s);
    for(int i = 7; i <= s.length() - 1; i++){
        if(s[i] == 32){
            ind++;
            if(ind % 2 == 0){
                construct[1] = stol(temp);
                construct[1] += construct[0];
                elements.push_back(construct);
                temp.clear();
            }
            else{
                construct[0] = stol(temp);
                temp.clear();
            }
        }
        else temp.push_back(s[i]);
    }
    construct[1] = stol(temp);
    construct[1] += construct[0];
    elements.push_back(construct);
    getline(file, s);
    std::vector<std::array<long, 2>> addStep;
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
            long supLimit{source + rangeTo};
            long destLimit{destination + rangeTo};
            for(int j = 0; j <= elements.size() - 1; j++){
                if(elements[j][0] == -1){
                    continue;
                }
                std::cout << "0: " << elements[j][0] << "\n";
                std::cout << "1: " << elements[j][1] << "\n";
                if(elements[j][0] >= source && elements[j][1] <= supLimit){
                    addStep.push_back({destination + (elements[j][0] - source), destination + (elements[j][1] - source)});
                    elements[j][0] = -1;
                }
                else if(elements[j][0] <= source && elements[j][1] >= supLimit){
                    addStep.push_back({destination, destLimit});
                    elements.push_back({supLimit, elements[j][1]});
                    elements[j][1] = source;                   // garder source dans l'intervalle, pas source - 1;
                }
                else if(elements[j][0] <= source && elements[j][1] < supLimit && elements[j][1] > source){
                    addStep.push_back({destination, destination + (elements[j][1] - source)});
                    elements[j][1] = source;                      // garder source dans l'intervalle, pas source - 1;
                }
                else if(elements[j][0] > source && elements[j][0] < supLimit && elements[j][1] > supLimit){
                    addStep.push_back({destination + (elements[j][0] - source), destLimit});
                    elements[j][0] = supLimit;                  // garder supLimit dans l'intervalle, pas supLimit + 1;
                }
            }
        }
        else if(s[0] > 96 && s[0] < 123){
            std::cout << "new category" << "\n";
            elements.insert(elements.end(), addStep.begin(), addStep.end());
            addStep.clear();
        }
    }
    elements.insert(elements.end(), addStep.begin(), addStep.end());
    double res{std::numeric_limits<double>::infinity()};
    for(int k = 0; k <= elements.size() - 1; k++){
        std::cout << elements[k][0] << "\n";
        if(elements[k][0] < res && elements[k][0] > -1){
            res = elements[k][0];
        }
    }
    std::cout << std::fixed << res << "\n";  // fixed pour ne pas utiliser l'écriture scientifique avec exposant
    return 0;
}