#include <string>
#include <iostream>

int main(){
    int res{0};
    for(int i = 128393; i < 643281; i++){
        std::string candidate{std::to_string(i)};
        bool duplicate{false};
        for(int j = 1; j <= candidate.length() - 1; j++){
            if(candidate[j] < candidate[j - 1]){
                break;
            }
            else if(candidate[j] == candidate[j - 1]){
                duplicate = true;
            }
            if(j == candidate.length() - 1 && duplicate == true){
                res++;
            }
        }
    }
    std::cout << res << "\n";
    return res;
}