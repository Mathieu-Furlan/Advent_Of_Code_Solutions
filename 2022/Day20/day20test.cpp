#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <list>

struct Node{
    int value;
    bool alreadyMoved = false;
    Node(int val) : value(val){}                                  // constructor dans le cas où on ne donne qu'un seul paramètre
};                                     // point-virgule après la définition

int main(){
    std::ifstream file("input");
    std::string s;
    std::list<Node> sequence;
    getline(file, s);
    Node firstNode(std::stoi(s));
    sequence.push_back(firstNode);
    Node* zeroPointer{nullptr};
    while(getline(file, s)){
        Node temp(std::stoi(s));
        if(temp.value == 0){
            zeroPointer = &temp;                    //un pointer vers l'élément 0 pour le résultat final
        }
        sequence.push_back(temp);
    }
    for(auto& n : sequence){
        std::cout << n.value << "\n";
        if(!n.alreadyMoved){
            Node* movedNode{&n};
            int movement{n.value};
            if(movement > 0){
                while(movement > 0){
                    if(movedNode == sequence.end()){
                        movedNode = sequence.begin();
                    }
                    else sequence.splice(n + 1, sequence, n);
                    movement--;
                }
            }
            else if(movement < 0){
                while(movement < 0){
                    if(n == sequence.begin()){
                        n = sequence.end();
                    }
                    sequence.splice(n - 1, list, n);
                    movement++;
                }
            }
            n.alreadyMoved = true;
        }
    }
    int startFromZero{0};
    while(startFromZero < 3000){
        startFromZero++;
        zeroPointer = zeroPointer -> next;
        if(startFromZero == 1000 || startFromZero == 2000 || startFromZero == 3000){
            std::cout << zeroPointer -> value << "\n";
        }
    }
    return 0;
}