#include <fstream>
#include <string>
#include <iostream>
#include <array>
#include <stack>

int main(){
    std::ifstream file("input");
    std::string s;
    std::stack<char> stack1;
    stack1.push('H');
    stack1.push('R');
    stack1.push('B');
    stack1.push('D');
    stack1.push('Z');
    stack1.push('F');
    stack1.push('L');
    stack1.push('S');
    std::stack<char> stack2;
    stack2.push('T');
    stack2.push('B');
    stack2.push('M');
    stack2.push('Z');
    stack2.push('R');
    std::stack<char> stack3;
    stack3.push('Z');
    stack3.push('L');
    stack3.push('C');
    stack3.push('H');
    stack3.push('N');
    stack3.push('S');
    std::stack<char> stack4;
    stack4.push('S');
    stack4.push('C');
    stack4.push('F');
    stack4.push('J');
    std::stack<char> stack5;
    stack5.push('P');
    stack5.push('G');
    stack5.push('H');
    stack5.push('W');
    stack5.push('R');
    stack5.push('Z');
    stack5.push('B');
    std::stack<char> stack6;
    stack6.push('V');
    stack6.push('J');
    stack6.push('Z');
    stack6.push('G');
    stack6.push('D');
    stack6.push('N');
    stack6.push('M');
    stack6.push('T');
    std::stack<char> stack7;
    stack7.push('G');
    stack7.push('L');
    stack7.push('N');
    stack7.push('W');
    stack7.push('F');
    stack7.push('S');
    stack7.push('P');
    stack7.push('Q');
    std::stack<char> stack8;
    stack8.push('M');
    stack8.push('Z');
    stack8.push('R');
    std::stack<char> stack9;
    stack9.push('M');
    stack9.push('C');
    stack9.push('L');
    stack9.push('G');
    stack9.push('V');
    stack9.push('R');
    stack9.push('T');
    std::array<std::stack<char>, 9> stackCluster{stack1, stack2, stack3, stack4, stack5, stack6, stack7, stack8, stack9};
    while(getline(file, s)){
        if(s[0] == 109){
            std::string moves;
            moves += s[5];
            if(s[6] > 47){
                moves += s[6];
            }
            int stackGive{-1};
            int stackReceive{-1};
            for(int i = 10; i <= s.length() - 1; i++){
                if(s[i] > 47 && s[i] < 58){
                    if(stackGive == -1){
                        stackGive = s[i] - '0' - 1;
                    }
                    else stackReceive = s[i] - '0' - 1;
                }
            }
            int transfer{stoi(moves)};
            std::cout << "transfer" << transfer << "\n";
            while(transfer > 0){
                std::cout << stackGive << "\n";
                std::cout << stackReceive << "\n";
                char elem{stackCluster[stackGive].top()};
                std::cout << "elem" << elem << "\n";
                stackCluster[stackGive].pop();
                stackCluster[stackReceive].push(elem);
                transfer--;
            }
            std::cout << "next" << "\n";
        }
    }
    std::string res;
    for(int j = 0; j <= stackCluster.size() - 1; j++){
        res += stackCluster[j].top();
    }
    std::cout << res << "\n";
    return 0;
}