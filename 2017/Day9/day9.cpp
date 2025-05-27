#include <fstream>
#include <string>
#include <iostream>

int res{0};

int processGarbage(int index, std::string& streamBlocks){
    for(int i = index; i <= streamBlocks.length() - 1; i++){
        if(streamBlocks[i] == '!'){
            i++;
        }
        else if(streamBlocks[i] == '>'){
            return i - index;
        }
    }
    return 0;
}

int processGroup(int score, int index, std::string& streamBlocks){
    res += score;
    for(int i = index; i <= streamBlocks.length() - 1; i++){
        if(streamBlocks[i] == '!'){
            i++;
        }
        else if(streamBlocks[i] == '}'){
            return i;
        }
        else if(streamBlocks[i] == '{'){
            i = processGroup(score + 1, i + 1, streamBlocks);
        }
        else if(streamBlocks[i] == '<'){
            i += processGarbage(i + 1, streamBlocks);
        }
    }
    return index;
}

int main(){
    std::ifstream file("input");
    std::string s;
    getline(file, s);
    processGroup(0, 0, s);
    std::cout << res << "\n";
    return res;
}