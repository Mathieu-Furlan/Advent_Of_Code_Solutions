#include <iostream>
#include <bitset>
#include <string>

int main(){
    long genA{512};
    long genB{191};
    int factorA{16807};
    int factorB{48271};
    int divRemainder{2147483647};
    int res{0};
    for(int i = 0; i < 5000000; i++){
        do{
            genA *= factorA;   
            genA %= divRemainder;
        }while(genA % 4 != 0);
        do{
            genB *= factorB;
            genB %= divRemainder;
        }while(genB % 8 != 0);
        std::string strRepA = std::bitset< 16 >(genA).to_string();  // chaîne de caractères contenant les 16 chiffres les moins représentatifs de la représentation binaire
        std::string strRepB = std::bitset< 16 >(genB).to_string();
        if(strRepA.compare(strRepB) == 0){
            res++;
        }
    }
    std::cout << res << "\n";
    return res;
}