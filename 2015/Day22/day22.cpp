#include <iostream>
#include <limits>

int res{std::numeric_limits<int>::max()};

void battleSimulator(int remainingLife, int playerMana, int playerArmor, int bossPoints, int poisonLength, int shieldDuration, int recharge, int manaUsed){
    if(poisonLength > 0){
        bossPoints -= 3;
        poisonLength--;
    }
    if(recharge > 0){
        playerMana += 101;
        recharge--;
    }
    if(shieldDuration > 0){
        playerArmor = 7;
        shieldDuration--;
    }
    if(bossPoints <= 0){
        if(manaUsed < res){
            res = manaUsed;
        }
        return;
    }
    if(manaUsed >= res){
        return;
    }
    remainingLife -= 9 - playerArmor;           // le boss attaque
    if(remainingLife <= 0){
        return;
    }
    if(poisonLength > 0){
        bossPoints -= 3;
        poisonLength--;
    }
    if(recharge > 0){
        playerMana += 101;
        recharge--;
    }
    if(shieldDuration > 0){
        playerArmor = 7;
        shieldDuration--;
    }
    if(bossPoints <= 0){
        if(manaUsed < res){
            res = manaUsed;
        }
        return;
    }
    if(playerMana >= 53){
        battleSimulator(remainingLife, playerMana - 53, 0, bossPoints - 4, poisonLength, shieldDuration, recharge, manaUsed + 53);
    }
    if(playerMana >= 73){
        battleSimulator(remainingLife >= 48 ? 50 : remainingLife + 2, playerMana - 73, 0, bossPoints - 2, poisonLength, shieldDuration, recharge, manaUsed + 73);
    }
    if(playerMana >= 113 && shieldDuration == 0){
        battleSimulator(remainingLife, playerMana - 113, 0, bossPoints, poisonLength, shieldDuration + 6, recharge, manaUsed + 113);
    }
    if(playerMana >= 173 && poisonLength == 0){
        battleSimulator(remainingLife, playerMana - 173, 0, bossPoints, poisonLength + 6, shieldDuration, recharge, manaUsed + 173);
    }
    if(playerMana >= 229 && recharge == 0){
        battleSimulator(remainingLife, playerMana - 229, 0, bossPoints, poisonLength, shieldDuration, recharge + 5, manaUsed + 229);
    }
}

int main(){
    battleSimulator(50, 447, 0, 47, 0, 0, 0, 53);       // si on commence par magic missile
    battleSimulator(50, 427, 0, 49, 0, 0, 0, 73);       // si on commence par drain
    battleSimulator(50, 387, 0, 51, 0, 6, 0, 113);      // si on commence par shield
    battleSimulator(50, 327, 0, 51, 6, 0, 0, 173);      // si on commence par poison
    battleSimulator(50, 271, 0, 51, 0, 0, 5, 229);      // si on commence par recharge
    std::cout << res << "\n";
    return 0;
}