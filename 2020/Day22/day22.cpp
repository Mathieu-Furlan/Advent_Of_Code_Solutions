#include <fstream>
#include <string>
#include <iostream>
#include <deque>

int main(){
    std::ifstream file("input");
    std::string s;
    std::deque<int> hand1;
    bool cards1{false};
    std::deque<int> hand2;
    bool cards2{false};
    while(getline(file, s)){
        if(s.length() > 0 && s[0] == 'P'){
            if(s[7] == '1'){
                cards1 = true;
            }
            else{
                cards1 = false;
                cards2 = true;
            }
        }
        else if(s.length() > 0){
            if(cards1){
                hand1.push_back(std::stoi(s));
            }
            else hand2.push_back(std::stoi(s));
        }
    }
    while(hand1.size() > 0 && hand2.size() > 0){
        int player1{hand1.front()};
        hand1.pop_front();
        int player2{hand2.front()};
        hand2.pop_front();
        if(player1 > player2){
            hand1.push_back(player1);
            hand1.push_back(player2);
        }
        else{
            hand2.push_back(player2);
            hand2.push_back(player1);
        }
    }
    int multiplicator{1};
    int res{0};
    if(hand1.size() > 0){
        while(hand1.size() > 0){
            res += hand1.back() * multiplicator;
            multiplicator++;
            hand1.pop_back();
        }
    }
    else{
        while(hand2.size() > 0){
            res += hand2.back() * multiplicator;
            multiplicator++;
            hand2.pop_back();
        }
    }
    std::cout << res << "\n";
    return 0;
}