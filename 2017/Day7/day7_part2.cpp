#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <vector>

std::unordered_map<std::string, int> programsWeights;
std::unordered_map<std::string, std::vector<std::string>> abovePrograms;

int computeProgramWeight(std::string prog){
    if(abovePrograms.find(prog) == abovePrograms.end()){             // s'il s'agit d'un élément au sommet
        return programsWeights.at(prog);
    }
    else{
        int cumulWeight{0};
        std::vector<int> subPathes;
        for(auto& elem : abovePrograms.at(prog)){
            int currWeight = computeProgramWeight(elem);
            cumulWeight += currWeight;
            subPathes.push_back(currWeight);
        }
        int prevSum{0};
        for(auto& path : subPathes){
            if(prevSum > 0 && prevSum != path){
                std::cout << "progOwnValue " << programsWeights.at(prog) << "\n";
                std::cout << prog << "\n";
                for(auto& path : subPathes){          //les éléments dans une unordered map sont itérés par ordre d'insertion, 
                    std::cout << path << "\n";        //on regarde dans le fichier l'élément dont l'indice correspond à l'élément différent du vecteur
                }
            }
            prevSum = path;
        }
        cumulWeight += programsWeights.at(prog);
        return cumulWeight;
    }
}

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    while(getline(file, s)){
        bool above{false};
        std::string programName;
        std::string weight;
        std::string temp;
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] > 96 && s[i] < 123){
                if(above){
                    temp += s[i];
                }
                else programName += s[i];
            }
            else if(s[i] > 47 && s[i] < 58){
                weight += s[i];
            }
            else if(s[i] == '>'){
                above = true;
            }
            else if(temp.length() > 0){
                if(above){
                    if(abovePrograms.find(programName) != abovePrograms.end()){
                        abovePrograms.at(programName).push_back(temp);
                    }
                    else{
                        std::vector<std::string> progConst;
                        progConst.push_back(temp);
                        abovePrograms.insert(std::make_pair(programName, progConst));
                    }
                    temp.clear();
                }
            }
        }
        programsWeights.insert(std::make_pair(programName, std::stoi(weight)));
        if(temp.length() > 0){
            abovePrograms.at(programName).push_back(temp);
        }
    }
    computeProgramWeight("eugwuhl");  // eugwuhl est l'élément tout en bas d'après le résultat de la partie 1
    return 0;
}