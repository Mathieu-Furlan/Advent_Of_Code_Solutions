#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    long res{0};
    while(getline(file, s)){
        long powerFive{1};
        long snafuNumb{0};
        for(int i = s.length() - 1; i >= 0; i--){
            if(s[i] == '1'){
                snafuNumb += powerFive;
            }
            else if(s[i] == '2'){
                snafuNumb += powerFive * 2;
            }
            else if(s[i] == '-'){
                snafuNumb -= powerFive;
            }
            else if(s[i] == '='){
                snafuNumb -= powerFive * 2;
            }
            powerFive *= 5;
        }
        res += snafuNumb;
    }
    std::cout << res << "\n";
    std::string snafuRes;
    long powerOfFive{1};
    long nextPowerOfFive{5};
    long currentValue{0};
    while(currentValue != res){
        long modulo{(res % nextPowerOfFive - currentValue) / powerOfFive};          // formule basée sur une approche consistant à essayer et à apprendre des erreurs
        if(modulo == 0 || modulo == 5){
            snafuRes = '0' + snafuRes;
        }
        else if(modulo == 1){
            snafuRes = '1' + snafuRes;
            currentValue += powerOfFive;
        }
        else if(modulo == 2){
            snafuRes = '2' + snafuRes;
            currentValue += powerOfFive * 2;
        }
        else if(modulo == 3){
            snafuRes = '=' + snafuRes;
            currentValue -= powerOfFive * 2;
        }
        else if(modulo == 4){
            snafuRes = '-' + snafuRes;
            currentValue -= powerOfFive;
        }
        powerOfFive = nextPowerOfFive;
        nextPowerOfFive *= 5;
    }
    std::cout << snafuRes << "\n";
    return 0;
}