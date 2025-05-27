#include <fstream>
#include <string>
#include <iostream>
#include <vector>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{0};
    while(getline(file, s)){
        std::vector<int> values;
        std::string temp;
        for(int i = 0; i <= s.length() - 1; i++){
            if(s[i] != 32){
                temp.push_back(s[i]);
            }
            else{
                values.push_back(stoi(temp));
                temp.clear();
            }
        }
        values.push_back(stoi(temp));
        int ind{0};
        std::cout << "new line" << "\n";
        while(true){
            bool differences{false};              //booléen et pas int car il y a des valeurs négatives
            for(int j = values.size() - 1; j >= 1 + ind; j--){
                int diff{values[j] - values[j - 1]};   // nbre2 - nbre1; pas de valeur absolue
                if(diff != 0){
                    differences = true;
                }
                values[j] = diff;
                std::cout << "diff " << diff << "\n";
            }
            if(differences == false){
                break;
            }
            ind++;
        }
        int firstElem{0};
        for(int k = values.size() - 1; k >= 0; k--){
            firstElem = values[k] - firstElem;
            std::cout << "k " << values[k] << "\n";
            std::cout << "firsElem" << firstElem << "\n";
        }
        res += firstElem;
    }
    std::cout << res << "\n";
    return res;
}