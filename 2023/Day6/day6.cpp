#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    int res{1};
    int lines{0};
    int time[4] = {0};
    int distance[4] = {0};
    while(getline(file, s)){
        if(lines == 0){
            std::string temp;
            int index{0};
            for(int i = 0; i <= s.length() - 1; i++){
                if(s[i] <= 57 && s[i] >= 48){
                    temp.push_back(s[i]);
                }
                else if(temp.length() > 0){
                    time[index] = (stoi(temp));
                    index++;
                    temp.clear();
                }
            }
            time[index] = (stoi(temp));
            lines++;
        }
        else{
            std::string temp;
            int index{0};
            for(int i = 0; i <= s.length() - 1; i++){
                if(s[i] <= 57 && s[i] >= 48){
                    temp.push_back(s[i]);
                }
                else if(temp.length() > 0){
                    distance[index] = (stoi(temp));
                    index++;
                    temp.clear();
                }
            }
            distance[index] = (stoi(temp));
        }
    }
    for(int k = 0; k <= std::size(time) - 1; k++){
        std::cout << "time: " << time[k] << "\n";
        int records{0};
        for(int j = 1; j < time[k]; j++){
            int pos{(time[k] - j) * j};
            if(pos > distance[k]){
                records++;
            }
        }
        std::cout << records << "\n";
        res *= records; 
    }
    std::cout << res << "\n";
    return res;
}