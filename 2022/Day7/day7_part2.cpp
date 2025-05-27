#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <limits>

struct Node {                   // string et vector ont des valeurs par défaut prévues par l'initialisateur
    std::string folderName;         // chaîne de caractères vide par défaut
    Node *parent = nullptr;         // "=" pour indiquer une valeur par défaut
    int data = 0;
    std::vector<Node*> children;   // vecteur vide par défaut
};

const int REQUIRED_SPACE{30000000};
const int TOTAL_SPACE{70000000};
int occupiedSpace{0};
int target;
int res{std::numeric_limits<int>::max()};

int postOrderTraversal(Node *folder){
    int cumulatedSize{0};
    for(auto& next : folder -> children){
        cumulatedSize += postOrderTraversal(next);
    }
    cumulatedSize += folder -> data;
    if(cumulatedSize >= target && cumulatedSize < res){                    // si la taille du dossier est supérieure à la taille requise
        res = cumulatedSize;
    }
    return cumulatedSize;
}

int main(){
    std::ifstream file("input");
    std::string s;
    getline(file, s);              // la première ligne initialise l'arborescence
    Node root{"root"};
    Node* currentNode{&root};       // on donne l'adresse de root à currentNode
    Node* treeRoot{&root};
    std::string prevFolderName;
    while(getline(file, s)){
        if(s[0] == '$' && s[2] == 'c' && s[3] == 'd'){
            prevFolderName = s.substr(5);
            if(prevFolderName == ".."){
                currentNode = currentNode -> parent;                   // parent est déjà un pointeur
            }
            else{
                for(int i = 0; i <= currentNode -> children.size() - 1; i++){       // children contient des pointeurs
                    if(currentNode -> children[i]-> folderName == prevFolderName){
                        currentNode = currentNode -> children[i];         // on donne l'adresse de children[i] à currentNode
                        break;
                    }
                }
            }
        }
        else if(s[0] > 47 && s[0] < 58){
            std::string fileSize;
            int i{0};
            while(s[i] > 47 && s[i] < 58){
                fileSize.push_back(s[i]);
                i++;
            }
            currentNode -> data += std::stoi(fileSize);             // on augmente la taille au niveau du dossier sans prendre an compte les sous dossiers
            occupiedSpace += std::stoi(fileSize);                   // l'espace occupé total
        }
        else if(s[0] == 'd'){
            std::string childName{s.substr(4)};
            currentNode -> children.push_back(new Node{childName, currentNode});           // on insère une nouvelle node dans le vecteur
        } 
    }
    target = REQUIRED_SPACE - (TOTAL_SPACE - occupiedSpace);         // l'espace à libérer
    postOrderTraversal(treeRoot);                   // on traverse l'arbre pour obtenir la taille des dossiers en incluant les sous dossiers
    std::cout << "res " << res << "\n";
    return 0;
}