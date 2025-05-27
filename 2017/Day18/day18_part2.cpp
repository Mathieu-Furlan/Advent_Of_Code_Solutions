#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <array>

// le registre et les queues sont passés par référence pour que la fonction puisse les modifier

std::array<int, 5> readInstruction(std::unordered_map<char, long long>& registers, std::vector<std::string>& instructions, int index, std::queue<long long>& ownQueue, std::queue<long long>& otherQueue, bool otherWaiting, bool program1, int res, bool deadLock){
    int increaseIndex{0};
    bool waiting{false};
    if(index < 0 || index >= instructions.size()){       // si l'index dépasse la liste des instructions le programme s'arrête
        deadLock = true;
        return {0, 0, 0, otherWaiting, 1};
    }
    std::string currInstruction{instructions[index]};
    if(currInstruction[0] == 's' && currInstruction[1] == 'e'){
        int val;
        if(currInstruction[6] > 96 && currInstruction[6] < 123){
                val = registers.at(currInstruction[6]);
        }
        else{
            std::string value;
            int i{6};
            while(currInstruction[i] == '-' || (currInstruction[i] > 47 && currInstruction[i] < 58)){
                value += currInstruction[i];
                i++;
            }
            val = std::stoi(value);
        }
        registers.at(currInstruction[4]) = val;
        increaseIndex++;
    }
    else if(currInstruction[0] == 's' && currInstruction[1] == 'n'){  
        otherQueue.push(registers.at(currInstruction[4]));
        otherWaiting = false;
        if(program1){
            res++;
        }
        increaseIndex++;
    }
    else if(currInstruction[0] == 'a'){
        int val;
        if(currInstruction[6] > 96 && currInstruction[6] < 123){
            val = registers.at(currInstruction[6]);
        }
        else{
            std::string value;
            int i{6};
            while(currInstruction[i] == '-' || (currInstruction[i] > 47 && currInstruction[i] < 58)){
                value += currInstruction[i];
                i++;
            }
            val = std::stoi(value);
        }
        registers.at(currInstruction[4]) += val;
        increaseIndex++;
    }
    else if(currInstruction[0] == 'm' && currInstruction[1] == 'u'){
        int val;
        if(currInstruction[6] > 96 && currInstruction[6] < 123){
            val = registers.at(currInstruction[6]);
        }
        else{
            std::string value;
            int i{6};
            while(currInstruction[i] == '-' || (currInstruction[i] > 47 && currInstruction[i] < 58)){
                value += currInstruction[i];
                i++;
            }
            val = std::stoi(value);
        }
        registers.at(currInstruction[4]) *= val;
        increaseIndex++;
    }
    else if(currInstruction[0] == 'm' && currInstruction[1] == 'o'){
        int val;
        if(currInstruction[6] > 96 && currInstruction[6] < 123){
            val = registers.at(currInstruction[6]);
        }
        else{
            std::string value;
            int i{6};
            while(currInstruction[i] == '-' || (currInstruction[i] > 47 && currInstruction[i] < 58)){
                value += currInstruction[i];
                i++;
            }
            val = std::stoi(value);
        }
        registers.at(currInstruction[4]) %= val;
        increaseIndex++;
    }
    else if(currInstruction[0] == 'r'){
        if(ownQueue.size() > 0){
            registers.at(currInstruction[4]) = ownQueue.front();
            ownQueue.pop();
            increaseIndex++;
        }
        else waiting = true;
    }
    else if(currInstruction[0] == 'j'){
        int val;
        int evaluatedVal;             // le premier paramètre de jump peut être un entier
        if(currInstruction[4] > 47 && currInstruction[4] < 58){
            evaluatedVal = currInstruction[4] - '0';
        }
        else evaluatedVal = registers.at(currInstruction[4]);
        if(evaluatedVal > 0){
            if(currInstruction[6] > 96 && currInstruction[6] < 123){
                val = registers.at(currInstruction[6]);
            }
            else{
                std::string value;
                int i{6};
                while(currInstruction[i] == '-' || (currInstruction[i] > 47 && currInstruction[i] < 58)){
                    value += currInstruction[i];
                    i++;
                }
                val = std::stoi(value);
            }
            increaseIndex += val;
        }
        else increaseIndex++;
    }
    return {res, increaseIndex, waiting, otherWaiting, deadLock};
}

int main(){
    std::ifstream file("input");
    std::string s;
    std::vector<std::string> instructions;
    std::unordered_map<char, long long> registersA;
    std::unordered_map<char, long long> registersB;
    while(getline(file, s)){
        if(registersA.find(s[4]) == registersA.end()){
            registersA.insert(std::make_pair(s[4], 0));
        }
        if(registersB.find(s[4]) == registersB.end()){
            registersB.insert(std::make_pair(s[4], 0));
        }
        instructions.push_back(s);
    }
    registersB.at('p') = 1;        // le registre "p" du programme B commence à 1
    int indexA{0};
    int indexB{0};
    std::queue<long long> queueA;
    std::queue<long long> queueB;
    bool deadLockA{false};
    bool deadLockB{false};
    bool waitingA{false};
    bool waitingB{false};
    bool turn{true};
    int res{0};
    while(!deadLockA || !deadLockB){
        if(waitingA && waitingB){
            break;
        }
        if(turn){
            std::cout << "progA" << "\n";
            std::cout << "instrucA " << indexA << "\n";
            std::array<int, 5> instructionResult{readInstruction(registersA, instructions, indexA, queueA, queueB, waitingB, false, 0, deadLockA)};
            res += instructionResult[0];
            indexA += instructionResult[1];
            waitingA = instructionResult[2];
            waitingB = instructionResult[3];
            deadLockA = instructionResult[4];
            if(!waitingB && !deadLockB){      // si B n'est pas bloqué
                turn = false;
            }
        }
        else{
            std::cout << "progB" << "\n";
            std::cout << "instrucB " << indexB << "\n";
            std::array<int, 5> instructionResult{readInstruction(registersB, instructions, indexB, queueB, queueA, waitingA, true, 0, deadLockB)};
            res += instructionResult[0];
            indexB += instructionResult[1];
            waitingB = instructionResult[2];
            waitingA = instructionResult[3];
            deadLockB = instructionResult[4];
            if(!waitingA && !deadLockA){     // si A n'est pas bloqué
                turn = true;
            }
        }
    }
    std::cout << res << "\n";
    return res;
}