#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <algorithm>
#include <cmath>

const int CARDS_NUMBER{10007};

void newStack(std::array<int, CARDS_NUMBER>& deck){
    return std::reverse(deck.begin(), deck.end());
}

void cutN(std::array<int, CARDS_NUMBER>& deck, int cut){
    if(cut > 0){
        std::rotate(deck.begin(), deck.begin() + cut, deck.end());
    }
    else std::rotate(deck.rbegin(), deck.rbegin() + std::abs(cut), deck.rend());             // rbegin, rend: reverse iterator to reverse beginning, reverse iterator to reverse end
    return;
}

std::array<int, CARDS_NUMBER> incrementN(std::array<int, CARDS_NUMBER>& deck, int increment){
    std::array<int, CARDS_NUMBER> shuffled;
    int counter{0};
    for(int i = 0;; i = (i + increment) % CARDS_NUMBER){
        shuffled[i] = deck[counter];
        counter++;
        if(counter == CARDS_NUMBER){
            break;
        }
    }
    return shuffled;
}

int main(){
    std::ifstream file("input");
    std::string s;
    std::array<int, CARDS_NUMBER> cards;
    for(int i = 0; i < CARDS_NUMBER; i++){
        cards[i] = i;
    }
    while(getline(file, s)){
        if(s[0] == 'c'){
            std::string numBuilder{s.substr(4)};
            cutN(cards, std::stoi(numBuilder));
        }
        else if(s[5] == 'w'){
            std::string numBuilder{s.substr(20)};
            cards = incrementN(cards, std::stoi(numBuilder));
        }
        else newStack(cards);
    }
    for(int i = 0; i < CARDS_NUMBER; i++){
        if(cards[i] == 2019){
            std::cout << i << "\n";
        }
    }
    return 0;
}