#include <iostream>
#include <unordered_map>

int main(){
    std::unordered_map<int, int> spoken;
    spoken.insert(std::make_pair(2, 1));
    spoken.insert(std::make_pair(0, 2));
    spoken.insert(std::make_pair(1, 3));
    spoken.insert(std::make_pair(9, 4));
    spoken.insert(std::make_pair(5, 5));
    spoken.insert(std::make_pair(19, 6));
    int numberSpoken{6};
    int prev;
    int indexesDiff;
    bool firstTime{true};
    while(numberSpoken < 30000000){
        numberSpoken++;
        if(firstTime){
            if(spoken.find(0) == spoken.end()){
                spoken.insert(std::make_pair(0, numberSpoken));
            }
            else{
                firstTime = false;
                indexesDiff = numberSpoken - spoken.at(0);
                spoken[0] = numberSpoken;
            }
            prev = 0;
        }
        else{
            if(spoken.find(indexesDiff) == spoken.end()){
                firstTime = true;
                spoken.insert(std::make_pair(indexesDiff, numberSpoken));
                prev = indexesDiff;
            }
            else{
                int temp{numberSpoken - spoken.at(indexesDiff)};
                spoken[indexesDiff] = numberSpoken;
                prev = indexesDiff;
                indexesDiff = temp;
            }
        }
    }
    std::cout << "prev " << prev << "\n";
    return 0;
}