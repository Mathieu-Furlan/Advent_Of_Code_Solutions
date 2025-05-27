#include <iostream>
#include <deque>

int main(){
    std::deque<bool> tape{false};
    int cursor{0};
    int state{0};
    int steps{0};
    while(steps < 12399302){
        if(state == 0){
            if(tape[cursor] == false){
                tape[cursor] = true;
                cursor++;
                state = 1;
            }
            else{
                tape[cursor] = false;
                cursor++;
                state = 2;
            }
        }
        else if(state == 1){
            if(tape[cursor] == false){
                cursor--;
                state = 0;
            }
            else{
                tape[cursor] = false;
                cursor++;
                state = 3;
            }
        }
        else if(state == 2){
            if(tape[cursor] == false){
                tape[cursor] = true;
                cursor++;
                state = 3;
            }
            else{
                cursor++;
                state = 0;
            }
        }
        else if(state == 3){
            if(tape[cursor] == false){
                tape[cursor] = true;
                cursor--;
                state = 4;
            }
            else{
                tape[cursor] = false;
                cursor--;
            }
        }
        else if(state == 4){
            if(tape[cursor] == false){
                tape[cursor] = true;
                cursor++;
                state = 5;
            }
            else{
                cursor--;
                state = 1;
            }
        }
        else if(state == 5){
            if(tape[cursor] == false){
                tape[cursor] = true;
                cursor++;
                state = 0;
            }
            else{
                cursor++;
                state = 4;
            }
        }
        if(cursor == tape.size()){
            tape.push_back(0);
        }
        else if(cursor == -1){
            tape.push_front(0);
            cursor = 0;
        }
        steps++;
    }
    int res{0};
    for(auto& slot : tape){
        if(slot == true){
            res++;
        }
    }
    std::cout << res << "\n";
    return res;
}