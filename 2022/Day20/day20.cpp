#include <fstream>
#include <string>
#include <iostream>
#include <unordered_map>
#include <list>

struct Node{
    int value;
    Node* prev = nullptr;
    Node* next = nullptr;
    bool alreadyMoved = false;
    Node(int val) : value(val){}                                  // constructor dans le cas où on ne donne qu'un seul paramètre
    Node(int val, Node* p) : value(val), prev(p){}                // constructor dans le cas où l'on donne deux paramètres
};                                     // point-virgule après la définition

int main(){
    std::ifstream file("input");
    std::string s;
    std::list<Node> sequence;
    getline(file, s);
    Node firstNode(std::stoi(s));
    sequence.push_back(firstNode);
    Node* previousNode{&firstNode};
    Node* beginningList{&firstNode};
    Node* zeroPointer{nullptr};
    while(getline(file, s)){
        Node temp(std::stoi(s), previousNode);
        if(temp.value == 0){
            zeroPointer = &temp;                    //un pointer vers l'élément 0 pour le résultat final
        }
        previousNode -> next = &temp;
        sequence.push_back(temp);
        previousNode = &temp;
    }
    beginningList -> prev = previousNode;            // le début et la fin de la liste se rejoignent pour former une liste circulaire
    previousNode -> next = beginningList;
    for(auto& n : sequence){
        std::cout << n.value << "\n";
        if(!n.alreadyMoved){
            Node* movedNode{&n};
            int movement{n.value};
            n.prev -> next = n.next;
            n.next -> prev = n.prev;
            sequence.erase(sequence.begin());    // à modifier
            if(movement > 0){
                while(movement > 0){
                    movedNode = movedNode -> next;
                    movement--;
                }
                n.next = movedNode -> next;
                n.prev = movedNode;
                movedNode -> next -> prev = &n;
                movedNode -> next = &n;
            }
            else if(movement < 0){
                while(movement < 0){
                    movedNode = movedNode -> prev;
                    movement++;
                }
                n.next = movedNode;
                n.prev = movedNode -> prev;
                movedNode -> prev -> next = &n;
                movedNode -> prev = &n;
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