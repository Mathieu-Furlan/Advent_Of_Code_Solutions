#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <stack>

int main(){
    std::ifstream file("input");
    std::string s;
    std::unordered_map<int, std::vector<int>> nodes;
    std::unordered_set<int> visited;
    while(getline(file, s)){
        bool communicateTo{false};
        std::string mainNode;
        for(int i = 0; i <= s.length() - 1; i++){
            if(i == 0){
                while(s[i] > 47 && s[i] < 58){
                    mainNode += s[i];
                    i++;
                }
                std::vector<int> temp;
                nodes.insert(std::make_pair(stoi(mainNode), temp));
            }
            else if(s[i] == '>'){
                communicateTo = true;
            }
            else if(communicateTo && s[i] > 47 && s[i] < 58){
                std::string nodeBuilder;
                while(s[i] > 47 && s[i] < 58){
                    nodeBuilder += s[i];
                    i++;
                }
                nodes.at(std::stoi(mainNode)).push_back(std::stoi(nodeBuilder));
            }
        }
    }
    int res{0};
    std::stack<int> processNodes;
    processNodes.push(0);
    visited.insert(0);
    res++;
    while(processNodes.size() > 0){
        int currNode{processNodes.top()};
        processNodes.pop();
        for(auto& connect : nodes.at(currNode)){
            if(visited.find(connect) == visited.end()){
                visited.insert(connect);
                processNodes.push(connect);
                res++;
            }
        }
    }
    std::cout << res << "\n";
    return res;
}