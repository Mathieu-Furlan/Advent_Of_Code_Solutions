#include <iostream>
#include <vector>
#include <cmath>

int main(){
    bool found{false};
    int houseNumber{2};
    while(!found){
        int house{houseNumber};
        std::vector<int> factors;
        while(houseNumber % 2 == 0){                                // on cherche tous les facteurs du numéro de maison
            factors.push_back(2);
            houseNumber /= 2;
        }
        for(int i = 3; i <= std::sqrt(houseNumber); i = i + 2){
            while(houseNumber % i == 0){
                factors.push_back(i);
                houseNumber /= i;
            }
        }
        if(houseNumber > 2){                                    // si le numéro de maison est un nombre premier supérieur à deux il ne sera pas réduit à 1 par les calculs précédents
            factors.push_back(houseNumber);
        }
        int presents{1};
        int res{1};
        int power{1};
        for(int i = 0; i <= factors.size() - 1; i++){           // on cherche la somme des facteurs
            if(i == 0 || factors[i] != factors[i - 1]){
                presents *= res;
                res = factors[i] + 1;
                power = 2;
            }
            else{
                res += std::pow(factors[i], power);
                power++;
            }
        }
        presents *= res;
        if(presents >= 3400000){
            found = true;
            std::cout << house << "\n";
        }
        houseNumber = house + 1;
    }
    return 0;
}