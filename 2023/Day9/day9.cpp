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
        int ind{1};
        std::cout << "new line" << "\n";
        while(true){
            bool differences{false};              //booléen et pas int car il y a des valeurs négatives
            for(int j = 1; j <= values.size() - ind; j++){
                int diff{values[j] - values[j - 1]};   // nbre2 - nbre1; pas de valeur absolue
                if(diff != 0){
                    differences = true;
                }
                values[j - 1] = diff;
                std::cout << diff << "\n";
            }
            if(differences == false){
                break;
            }
            ind++;
        }
        int sumLine{0};
        for(int k = 0; k <= values.size() - 1; k++){
            sumLine += values[k];
            std::cout << "last val" << values[k] << "\n";
        }
        res += sumLine;
    }
    std::cout << res << "\n";
    return res;
}