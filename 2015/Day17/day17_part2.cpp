#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <limits>

int used{std::numeric_limits<int>::max()};
int res{0};

void recursiveSolver(std::vector<int>& cont, int liters, int index, int contUsed){
    if(liters >= 150){
        if(liters == 150 && contUsed <= used){
            if(contUsed < used){
                used = contUsed;
                res = 1;
            }
            else res++;     // si le nombre de conteneurs utilisés est égal au minimum trouvé jusqu'à présent
        }
        return;
    }
    for(int j = index + 1; j <= cont.size() - 1; j++){
        liters += cont[j];
        recursiveSolver(cont, liters, j, contUsed + 1);
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
        recursiveSolver(containers, containers[i], i, 1);
    }
    std::cout << res << "\n";
    return res;
}