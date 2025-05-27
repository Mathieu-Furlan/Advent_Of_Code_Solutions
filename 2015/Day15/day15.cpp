#include <iostream>
#include <array>

struct ingredient{
    int capacity;
    int durability;
    int flavor;
    int texture;
} Sprinkles, PeanutButter, Frosting, Sugar;

int main(){
    int res{0};
    Sprinkles.capacity = 5;
    Sprinkles.durability = -1;
    Sprinkles.flavor = 0;
    Sprinkles.texture = 0;
    PeanutButter.capacity = -1;
    PeanutButter.durability = 3;
    PeanutButter.flavor = 0;
    PeanutButter.texture = 0;
    Frosting.capacity = 0;
    Frosting.durability = -1;
    Frosting.flavor = 4;
    Frosting.texture = 0;
    Sugar.capacity = -1;
    Sugar.durability = 0;
    Sugar.flavor = 0;
    Sugar.texture = 2;
    for(int i = 1; i <= 100; i++){         // chaque boucle s'arrête à 100 moins les ingrédients utilisés dans les autres boucles
        for(int j = 1; j <= 100 - i; j++){
            for(int k = 1; k <= 100 - i - j; k++){
                for(int m = 1; m <= 100 - i - j - k; m++){
                    int currCapacity{i * Sprinkles.capacity + j * PeanutButter.capacity + k * Frosting.capacity + m * Sugar.capacity};
                    if(currCapacity < 0){
                        continue;
                    }
                    int currDurability{i * Sprinkles.durability + j * PeanutButter.durability + k * Frosting.durability + m * Sugar.durability};
                    if(currDurability < 0){
                        continue;
                    }
                    int currFlavor{i * Sprinkles.flavor + j * PeanutButter.flavor + k * Frosting.flavor + m * Sugar.flavor};
                    if(currFlavor < 0){
                        continue;
                    }
                    int currTexture{i * Sprinkles.texture + j * PeanutButter.texture + k * Frosting.texture + m * Sugar.texture};
                    if(currTexture < 0){
                        continue;
                    }
                    int tempRes{currCapacity * currDurability * currFlavor * currTexture};
                    if(tempRes > res){
                        res = tempRes;
                    }
                }
            }
        }
    }
    std::cout << res << "\n";
    return res;
}