#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

// pour obtenir le graphique: neato -Tsvg graphDay25.gv -o graphDay25.svg
void dfsNodes(std::unordered_set<std::string>& group, std::vector<std::string>& listNode, std::unordered_map<std::string, std::unordered_set<std::string>>& graphRep, std::array<std::string, 3>& banned){
    std::vector<std::string> nextNodes;
    for(int i = 0; i < listNode.size(); i++){
        for(auto& related : graphRep.at(listNode[i])){
            if(std::find(group.begin(), group.end(), related) == group.end() && std::find(banned.begin(), banned.end(), related) == banned.end()){
                group.insert(related);
                nextNodes.push_back(related);
            }
        }
    }
    if(nextNodes.size() == 0){
        return;
    }
    else dfsNodes(group, nextNodes, graphRep, banned);
}

int main(){
    std::ofstream outfile ("graphDay25.gv");
    outfile << "strict graph G {" << std::endl;        // strict pour qu'il n'y ait pas deux fois le même lien entre deux noeuds 
    std::ifstream file("input");
    std::string s;
    std::unordered_map<std::string, std::unordered_set<std::string>> edges;
    std::string undirectedRelation{" -- "};
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
                    if(edges.find(lesserNode) == edges.end()){
                        edges.insert(std::make_pair(lesserNode, std::unordered_set<std::string>{mainNode}));
                    }
                    else edges.at(lesserNode).insert(mainNode);
                    outfile << mainNode << undirectedRelation << lesserNode << ';' << std::endl;
                    lesserNode.clear();
                }
            }
        }
    }
    outfile << "}" << std::endl;
    std::unordered_set<std::string> group1{"vgf", "fdb", "nmz"};
    std::vector<std::string> start1{"vgf", "fdb", "nmz"};
    std::array<std::string, 3> bannedFrom1{"jpn", "mnl", "txm"};        // d'après la représentation en svg du graphique
    dfsNodes(group1, start1, edges, bannedFrom1);
    std::unordered_set<std::string> group2{"jpn", "mnl", "txm"};
    std::vector<std::string> start2{"jpn", "mnl", "txm"};
    std::array<std::string, 3> bannedFrom2{"vgf", "fdb", "nmz"};        // d'après la représentation en svg du graphique
    dfsNodes(group2, start2, edges, bannedFrom2);
    unsigned long res{group1.size() * group2.size()};
    std::cout << group1.size() << "\n";
    std::cout << group2.size() << "\n";
    std::cout << res << "\n";
    return 0;
}