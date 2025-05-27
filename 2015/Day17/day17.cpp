#include <fstream>
#include <string>
#include <iostream>
#include <vector>

// les conteneurs ne s'utilisent qu'une fois, l'emploi de la brute force est assez rapide

int res{0};

void recursiveSolver(std::vector<int>& cont, int liters, int index){
    if(liters >= 150){
        if(liters == 150){
            res++;
        }
        return;
    }
    for(int j = index + 1; j <= cont.size() - 1; j++){
        liters += cont[j];
        recursiveSolver(cont, liters, j);
        liters -= cont[j];
    }
}

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<int> containers;
    while(getline(file, s)){
        containers.push_back(std::stoi(s));
    }
    for(int i = 0; i <= containers.size() - 1; i++){
        recursiveSolver(containers, containers[i], i);
    }
    std::cout << res << "\n";
    return res;
}