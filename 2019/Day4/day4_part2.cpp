#include <string>
#include <iostream>

int main(){
    int res{0};
    for(int i = 128393; i < 643281; i++){
        std::string candidate{std::to_string(i)};
        bool duplicate{false};
        int identical{0};
        for(int j = 1; j <= candidate.length() - 1; j++){
            if(candidate[j] < candidate[j - 1]){
                break;
            }
            else if(candidate[j] == candidate[j - 1]){
                identical++;
            }
            else if(candidate[j] != candidate[j - 1]){
                if(identical == 1){
                    duplicate = true;
                }
                else identical = 0;
            }
            if(j == candidate.length() - 1 && (duplicate == true || identical == 1)){   // si on a trouvé deux éléments identiques ou que les deux derniers le sont
                res++;
            }
        }
    }
    std::cout << res << "\n";
    return res;
}