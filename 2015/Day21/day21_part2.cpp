#include <iostream>
#include <array>
#include <cmath>

int main(){
    int playerHitPoints{100};
    int playerDamage{0};
    int playerArmor{0};
    int bossHitPoints{100};
    int bossDamage{8};
    int bossArmor{2};
    std::array<std::array<int, 2>, 5> weapons{{{8, 4}, {10, 5}, {25, 6}, {40, 7}, {74, 8}}};
    std::array<std::array<int, 2>, 6> armors{{{0, 0}, {13, 1}, {31, 2}, {53, 3}, {75, 4}, {102, 5}}};
    std::array<std::array<int, 3>, 7> rings{{{0, 0, 0}, {25, 1, 0}, {50, 2, 0}, {100, 3, 0}, {20, 0, 1}, {40, 0, 2}, {80, 0, 3}}};
    int res{0};
    int goldSpent{0};
    for(int i = 0; i <= weapons.size() - 1; i++){
        playerDamage += weapons[i][1];
        goldSpent += weapons[i][0];
        for(int j = 0; j <= armors.size() - 1; j++){
            playerArmor += armors[j][1];
            goldSpent += armors[j][0];
            int damageBoss{playerDamage - bossArmor > 0 ? playerDamage - bossArmor : 1};
            int damagePlayer{bossDamage - playerArmor > 0 ? bossDamage - playerArmor : 1};
            if(std::ceil(bossHitPoints / damageBoss) > std::ceil(playerHitPoints / damagePlayer)){ // dans le cas où on ne prend pas d'anneaux
                if(goldSpent > res){
                    res = goldSpent;
                }
            }
            for(int k = 0; k <= rings.size() - 2; k++){
                playerDamage += rings[k][1];
                playerArmor += rings[k][2];
                goldSpent += rings[k][0];
                for(int m = k + 1; m <= rings.size() - 1; m++){
                    playerDamage += rings[m][1];
                    playerArmor += rings[m][2];
                    goldSpent += rings[m][0];
                    int damageToBoss{playerDamage - bossArmor > 0 ? playerDamage - bossArmor : 1};
                    int damageToPlayer{bossDamage - playerArmor > 0 ? bossDamage - playerArmor : 1};
                    if(std::ceil(bossHitPoints / damageToBoss) > std::ceil(playerHitPoints / damageToPlayer)){ // s'il plus de coups pour tuer le boss que de coups nécessaires au boss pour tuer le joueur
                        if(goldSpent > res){
                            res = goldSpent;
                        }
                    }
                    playerDamage -= rings[m][1];
                    playerArmor -= rings[m][2];
                    goldSpent -= rings[m][0];
                }
                playerDamage -= rings[k][1];
                playerArmor -= rings[k][2];
                goldSpent -= rings[k][0];
            }
            playerArmor -= armors[j][1];
            goldSpent -= armors[j][0];
        }
        playerDamage -= weapons[i][1];
        goldSpent -= weapons[i][0];
    }
    std::cout << res << "\n";
    return 0;
}