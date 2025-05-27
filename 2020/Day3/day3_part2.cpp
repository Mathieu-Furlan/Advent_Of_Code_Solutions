#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream file("input");
    std::string s;
    long res{0};
    int col{0};
    int res2{0};
    int col2{0};
    int res3{0};
    int col3{0};
    int res4{0};
    int col4{0};
    int res5{0};
    int col5{0};
    int line{0};
    while(getline(file, s)){
        if(s[col] == '#'){
            res++;
        }
        if(s[col2] == '#'){
            res2++;
        }
        if(s[col3] == '#'){
            res3++;
        }
        if(s[col4] == '#'){
            res4++;
        }
        if(line % 2 == 0 && s[col5] == '#'){
            res5++;
        }
        col = (col + 3) % s.length();
        col2 = (col2 + 1) % s.length();
        col3 = (col3 + 5) % s.length();
        col4 = (col4 + 7) % s.length();
        if(line % 2 == 0){
            col5 = (col5 + 1) % s.length();
        }
        line++;
    }
    std::cout << res * res2 * res3 * res4 * res5 << "\n";
    return 0;
}