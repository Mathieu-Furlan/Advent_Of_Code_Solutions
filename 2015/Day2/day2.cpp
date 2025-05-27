#include <fstream>
#include <string>
#include <iostream>

int main(){
    std::ifstream infile("input");
    std::string s;
    int res{0};
    while(infile >> s){
        std::string lengthBox;
        std::string widthBox;
        std::string heightBox;
        int created{0};
        for(int i = 0; i <= s.length() - 1; i++){
            if(created == 0 && s[i] > 47 && s[i] < 58){
                lengthBox += s[i];
            }
            else if(created == 1 && s[i] > 47 && s[i] < 58){
                widthBox += s[i];
            }
            else if(created == 2 && s[i] > 47 && s[i] < 58){
                heightBox += s[i];
            }
            else if(s[i] == 'x'){
                created++;
            }
        }
        int lengthInt{stoi(lengthBox)};
        int widthInt{stoi(widthBox)};
        int heightInt{stoi(heightBox)};
        int lengthWidth{lengthInt * widthInt};
        int widthHeight{widthInt * heightInt};
        int lengthHeight{lengthInt * heightInt};
        int surface{2 * lengthWidth + 2 * widthHeight + 2 * lengthHeight};
        int minSurface{0};
        if(lengthWidth < widthHeight){
            minSurface = lengthWidth;
        }
        else minSurface = widthHeight;
        if(lengthHeight < minSurface){
            minSurface = lengthHeight;
        }
        std::cout << "surface " << surface << "\n";
        std::cout << "minSurface " << minSurface << "\n";
        surface += minSurface;
        res += surface;
    }
    std::cout << res << "\n";
    return res;
}