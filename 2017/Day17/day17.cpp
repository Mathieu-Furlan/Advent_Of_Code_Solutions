#include <vector>
#include <iostream>

int main(){
    std::vector<int> circularBuffer{0};
    int nextInsertion{1};
    int currPos{0};
    while(nextInsertion <= 2017){
        int spinSteps{370};
        while(spinSteps > 0){
            currPos++;
            spinSteps--;
            if(currPos == circularBuffer.size()){
                currPos = 0;
            }
        }
        int index;
        index = currPos + 1;
        if(nextInsertion == 2017){
            std::cout << circularBuffer[index] << "\n";
            break;
        }
        else{
            circularBuffer.insert(circularBuffer.begin() + index, nextInsertion);
            currPos++;
            if(currPos == circularBuffer.size()){
                currPos = 0;
            }
            nextInsertion++;
        }
    }
    return 0;
}