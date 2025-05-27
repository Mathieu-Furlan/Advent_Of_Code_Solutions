#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cstdlib>
#include <ctime>

// 537138 too low    // 598094 not correct
int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<std::string, std::unordered_set<std::string>> edges;
    int edgeCount{0};
    while(getline(file, s)){
        std::string mainNode{s.substr(0, 3)};
        if(edges.find(mainNode) == edges.end()){
            edges.insert(std::make_pair(mainNode, std::unordered_set<std::string>{}));
        }
        std::string lesserNode;
        for(int i = 5; i <= s.length() - 1; i++){
            if(s[i] != ' '){
                lesserNode += s[i];
                if(lesserNode.length() == 3){
                    edges.at(mainNode).insert(lesserNode);
                    edgeCount++;
                    if(edges.find(lesserNode) == edges.end()){
                        edges.insert(std::make_pair(lesserNode, std::unordered_set<std::string>{mainNode}));
                    }
                    else edges.at(lesserNode).insert(mainNode);
                    edgeCount++;
                    lesserNode.clear();
                }
            }
        }
    }
    srand((unsigned)time(0));
    while(edges.size() > 2){
        int chosenVert{(rand() % edgeCount) + 1};
        int iterate{0};
        for(auto& [key, val] : edges){
            for(auto& edge : val){
                iterate++;
                if(iterate == chosenVert){
                    std::string newVertice{key + edge};
                    edges.insert(std::make_pair(newVertice, std::unordered_set<std::string>{}));
                    for(auto& neighbor : edges.at(key)){
                        if(neighbor != edge){
                            edges.at(newVertice).insert(neighbor);
                            edges.at(neighbor).erase(key);
                            edges.at(neighbor).insert(newVertice);
                        }
                    }
                    for(auto& neighbor : edges.at(edge)){
                        if(neighbor != key){
                            edges.at(newVertice).insert(neighbor);
                            edges.at(neighbor).erase(edge);
                            edges.at(neighbor).insert(newVertice);
                        }
                    }
                    edges.erase(edge);
                    edges.erase(key);
                    iterate = -1;
                    break;
                }
            }
            if(iterate == -1){
                break;
            }
        }
    }
    int res{0};
    for(auto& [key, val] : edges){
        std::cout << key << "\n";
        if(res == 0){
            res += key.length() / 3;
        }
        else res *= key.length() / 3;
    }
    std::cout << res << "\n";
    return 0;
}