#include <fstream>
#include <string>
#include <iostream>
#include <vector>

struct Node{
    int value;
    Node* prev{nullptr};
    Node* next{nullptr};
    Node(int val) : value(val){}                                  // constructor dans le cas où on ne donne qu'un seul paramètre
    Node(int val, Node* p) : value(val), prev(p){}                // constructor dans le cas où l'on donne deux paramètres
};                                     // point-virgule après la définition

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<Node*> toBeMoved;
    getline(file, s);
    Node* head{new Node(std::stoi(s))};
    toBeMoved.push_back(head);
    Node* prevNode{head};
    Node* zeroPointer;
    while(getline(file, s)){
        Node* temp{new Node(std::stoi(s))};
        if(temp -> value == 0){
            zeroPointer = temp;                    //un pointer vers l'élément 0 pour le résultat final
        }
        temp -> prev = prevNode;
        prevNode -> next = temp;
        prevNode = temp;
        toBeMoved.push_back(prevNode);
    }
    head -> prev = prevNode;            // le début et la fin de la liste se rejoignent pour former une liste circulaire
    prevNode -> next = head;
    for(int i = 0; i < toBeMoved.size(); i++){
        int movement{toBeMoved[i] -> value};
        if(movement > 0){
            while(movement > 0){
                Node* exchangeNextPointer{toBeMoved[i] -> next};
                Node* exchangePrevPointer{toBeMoved[i] -> prev};
                toBeMoved[i] -> prev = exchangeNextPointer;
                toBeMoved[i] -> next = toBeMoved[i] -> next -> next;
                exchangeNextPointer -> next -> prev = toBeMoved[i];
                exchangePrevPointer -> next = exchangeNextPointer;
                exchangeNextPointer -> prev = exchangePrevPointer;
                exchangeNextPointer -> next = toBeMoved[i];
                movement--;
            }
        }
        else if(movement < 0){
            while(movement < 0){
                Node* exchangeNextPointer{toBeMoved[i] -> next};
                Node* exchangePrevPointer{toBeMoved[i] -> prev};
                toBeMoved[i] -> prev = toBeMoved[i] -> prev -> prev;
                toBeMoved[i] -> next = exchangePrevPointer;
                exchangePrevPointer -> prev -> next = toBeMoved[i];
                exchangeNextPointer -> prev = exchangePrevPointer;
                exchangePrevPointer -> next = exchangeNextPointer;
                exchangePrevPointer -> prev = toBeMoved[i];
                movement++;
            }
        }
    }
    int startFromZero{0};
    int res{0};
    while(startFromZero < 3000){
        startFromZero++;
        zeroPointer = zeroPointer -> next;
        if(startFromZero == 1000 || startFromZero == 2000 || startFromZero == 3000){
            std::cout << zeroPointer -> value << "\n";
            res += zeroPointer -> value;
        }
    }
    std::cout << res << "\n";
    return 0;
}