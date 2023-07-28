#ifndef RULE_HPP
#define RULE_HPP
#include "Calculator.hpp"
#include "functions.hpp"

//风云宴 蓝采和
int banquetRule0(BanquetStrictRule **, BanquetLenientRule **, States &, int);
//风云宴 吕洞宾
int banquetRule1(BanquetStrictRule **, BanquetLenientRule **, States &, int);
//风云宴 韩湘子
int banquetRule2(BanquetStrictRule **, BanquetLenientRule **, States &, int);
//风云宴 玉贵人
int banquetRule3(BanquetStrictRule **, BanquetLenientRule **, States &, int);
//风云宴 苏妲己
int banquetRule4(BanquetStrictRule **, BanquetLenientRule **, States &, int);
//风云宴 何仙姑
int banquetRule5(BanquetStrictRule **, BanquetLenientRule **, States &, int);
//风云宴 铁拐李
int banquetRule6(BanquetStrictRule **, BanquetLenientRule **, States &, int);
//风云宴 何仙姑2
int banquetRule7(BanquetStrictRule **, BanquetLenientRule **, States &, int);
//风云宴 胡喜媚
int banquetRule8(BanquetStrictRule **, BanquetLenientRule **, States &, int);
//风云宴 韩湘子2
int banquetRule9(BanquetStrictRule **, BanquetLenientRule **, States &, int);
//风云宴 蓝采和2
int banquetRule10(BanquetStrictRule **, BanquetLenientRule **, States &, int);
//风云宴 胡喜媚2
int banquetRule11(BanquetStrictRule **, BanquetLenientRule **, States &, int);
//风云宴 曹国舅
int banquetRule12(BanquetStrictRule **, BanquetLenientRule **, States &, int);
//风云宴 钟离权
int banquetRule13(BanquetStrictRule **, BanquetLenientRule **, States &, int);
//风云宴 打更人
int banquetRule14(BanquetStrictRule **, BanquetLenientRule **, States &, int);
//风云宴 玉贵人2
int banquetRule15(BanquetStrictRule **, BanquetLenientRule **, States &, int);
//风云宴 张果老
int banquetRule16(BanquetStrictRule **, BanquetLenientRule **, States &, int);

/**
 * @brief
 *
 * @param rule
 * @param s
 * @param bestfull
 * @return void
 */
void banquetRule(BanquetRule *const &rule, States &s, int *bestfull) {
    BanquetStrictRule
        *strictRule[NUM_CHEFS *
                    DISH_PER_CHEF]; // 下一阶段的规则，不受意图生效次数的影响
    BanquetLenientRule *lenientRule[NUM_CHEFS * DISH_PER_CHEF];
    for (int i = 0; i < NUM_CHEFS* DISH_PER_CHEF; i++) {
        strictRule[i] = &rule[i].strictRule;
        lenientRule[i] = &rule[i].lenientRule;
    }

    int (*ruleFunc)(BanquetStrictRule **, BanquetLenientRule **, States &, int);
    int (*ruleArray[])(BanquetStrictRule **, BanquetLenientRule **, States &, int) = {
        banquetRule0, banquetRule1, banquetRule2, banquetRule3, banquetRule4,
        banquetRule5, banquetRule6, banquetRule7, banquetRule8, banquetRule9,
        banquetRule10, banquetRule11, banquetRule12, banquetRule13, banquetRule14,
        banquetRule15, banquetRule16
    };

    for (int i = 0; i < NUM_GUESTS; i++) {
        ruleFunc = ruleArray[guestList[i]];
        bestfull[i] = ruleFunc(strictRule, lenientRule, s, i);
        // switch (guestList[i])
        // {
        // case 0:
        //     bestfull[i] = banquetRule0(strictRule, lenientRule, s, i);
        //     break;
        // case 1:
        //     bestfull[i] = banquetRule1(strictRule, lenientRule, s, i);
        //     break;        
        // case 2:
        //     bestfull[i] = banquetRule2(strictRule, lenientRule, s, i);
        //     break;        
        // case 3:
        //     bestfull[i] = banquetRule3(strictRule, lenientRule, s, i);
        //     break;        
        // case 4:
        //     bestfull[i] = banquetRule4(strictRule, lenientRule, s, i);
        //     break;       
        // case 5:
        //     bestfull[i] = banquetRule5(strictRule, lenientRule, s, i);
        //     break;       
        // case 6:
        //     bestfull[i] = banquetRule6(strictRule, lenientRule, s, i);
        //     break;       
        // case 7:
        //     bestfull[i] = banquetRule7(strictRule, lenientRule, s, i);
        //     break;       
        // case 8:
        //     bestfull[i] = banquetRule8(strictRule, lenientRule, s, i);
        //     break;       
        // case 9:
        //     bestfull[i] = banquetRule9(strictRule, lenientRule, s, i);
        //     break;       
        // case 10:
        //     bestfull[i] = banquetRule10(strictRule, lenientRule, s, i);
        //     break;      
        // case 11:
        //     bestfull[i] = banquetRule11(strictRule, lenientRule, s, i);
        //     break;      
        // case 12:
        //     bestfull[i] = banquetRule12(strictRule, lenientRule, s, i);
        //     break;         
        // case 13:
        //     bestfull[i] = banquetRule13(strictRule, lenientRule, s, i);
        //     break;            
        // case 14:
        //     bestfull[i] = banquetRule14(strictRule, lenientRule, s, i);
        //     break;            
        // case 15:
        //     bestfull[i] = banquetRule15(strictRule, lenientRule, s, i);
        //     break;    
        // case 16:
        //     bestfull[i] = banquetRule16(strictRule, lenientRule, s, i);
        //     break;    
        // default:
        //     break;
        // }
    }
    return;
}

//风云宴 蓝采和
int banquetRule0(BanquetStrictRule **strictRule, BanquetLenientRule **lenientRule, States &s, int rank) {
    int d = rank * DISH_PER_CHEF * CHEFS_PER_GUEST;
    // 第1轮
    // 条件：三道切：下阶段炒技法料理基础售价+50%
    if (s.recipe[d + 0]->cookAbility.knife > 0 &&
        s.recipe[d + 1]->cookAbility.knife > 0 &&
        s.recipe[d + 2]->cookAbility.knife > 0) {
        for (int i = d + 3; i < d + 6; i++) {
            if (s.recipe[i]->cookAbility.stirfry > 0) {
                strictRule[i]->baseRule.buff += 50;
            }
        }
    }
    // 条件：三道蒸：下阶段烤技法料理基础售价+50%
    if (s.recipe[d + 0]->cookAbility.steam > 0 &&
        s.recipe[d + 1]->cookAbility.steam > 0 &&
        s.recipe[d + 2]->cookAbility.steam > 0) {
        for (int i = d + 3; i < d + 6 ; i++) {
            if (s.recipe[i]->cookAbility.bake > 0) {
                strictRule[i]->baseRule.buff += 50;
            }
        }
    }
    // 条件：三道煮：下阶段炸技法料理基础售价+50%
    if (s.recipe[d+0]->cookAbility.boil > 0 &&
        s.recipe[d+1]->cookAbility.boil > 0 &&
        s.recipe[d+2]->cookAbility.boil > 0) {
        for (int i = d + 3; i < d + 6; i++) {
            if (s.recipe[i]->cookAbility.fry > 0) {
                strictRule[i]->baseRule.buff += 50;
            }
        }
    }
    // 条件：甜：本道料理售价+100%
    for (int i = d + 0; i < d + 3; i++) {
        if (s.recipe[i]->flavor.sweet) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }


    // 第2轮
    // 条件：传：本道料理基础售价+50%
    for (int i = d + 3; i < d + 6; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 5) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    // 条件：第二道菜：第二道菜饱食度-3
    lenientRule[d + 4]->addRule.full += -3;
    // 条件：优：下道料理意图生效次数+1
    for (int i = d + 3; i < d + 5; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 2) {
            lenientRule[i + 1]->oneMore();
            break;
        }
    }
    // 条件：神：本道料理售价+100%
    for (int i = d + 3; i < d + 6; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 4) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }


    // 第3轮
    // 条件：苦：本道料理饱食度-4
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->flavor.bitter) {
            lenientRule[i]->addRule.full += -4;
            break;
        }
    }
    // 条件：1火：本道料理基础售价+50%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->rarity == 1) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    // 条件：甜：本道料理售价+100%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->flavor.sweet) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }
    // 条件：传：本道料理意图生效+1
    for (int i = d + 6; i < d + 9; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 5) {
            lenientRule[i]->oneMore();
            break;
        }
    }
    return 12;
}

//风云宴 吕洞宾
int banquetRule1(BanquetStrictRule **strictRule, BanquetLenientRule **lenientRule, States &s, int rank) {
    int d = rank * DISH_PER_CHEF * CHEFS_PER_GUEST;
    // 第1轮
    // 条件：三道炸：下阶段烤技法料理售价+100%
    if (s.recipe[d + 0]->cookAbility.fry > 0 &&
        s.recipe[d + 1]->cookAbility.fry > 0 &&
        s.recipe[d + 2]->cookAbility.fry > 0) {
        for (int i = d + 3; i < d + 6; i++) {
            if (s.recipe[i]->cookAbility.bake > 0) {
                strictRule[i]->addRule.buff += 100;
            }
        }
    }
    // 条件：2火：本道料理基础售价+50%
    for (int i = d + 0; i < d + 3; i++) {
        if (s.recipe[i]->rarity == 2) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    // 条件：第三道菜：第三道菜意图生效次数加一
    lenientRule[d+2]->oneMore();
    // 条件：3火：本道料理售价+100%
    for (int i = d+0; i < d+3; i++) {
        if (s.recipe[i]->rarity == 3) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }


    // 第2轮
    // 条件：3火：下道料理为辣时售价+100%
    for (int i = d + 3; i < d + 5; i++) {
        if (s.recipe[i]->rarity == 3) {
            if (s.recipe[i+1]->flavor.spicy){
                lenientRule[i+1]->addRule.buff += 100;
            }            
            break;
        }
    }
    // 条件：辣：下道料理为酸时售价+100%
    for (int i = d + 3; i < d + 5; i++) {
        if (s.recipe[i]->flavor.spicy) {
            if (s.recipe[i+1]->flavor.sour){
                lenientRule[i+1]->addRule.buff += 100;
            }            
            break;
        }
    }
    // 条件：酸：本道料理基础售价+50%
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->flavor.sour) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    // 条件：切：本道料理饱腹感-2
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->cookAbility.knife > 0) {
            lenientRule[i]->addRule.full += -2;
            break;
        }
    }


    // 第3轮
    // 条件：第一道菜：第一道菜饱腹感为2
    lenientRule[d + 6]->addRule.fullAdd = false;
    strictRule[d + 6]->addRule.full = 2;
    // 条件：5火：本道料理售价+100%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->rarity == 5) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }
    // 条件：特：本道料理意图生效次数加一
    for (int i = d + 6; i < d + 9; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 3) {
            lenientRule[i]->oneMore();
            break;
        }
    }
    // 条件：神：本道料理售价-150%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 4) {
            lenientRule[i]->baseRule.buff += -150;
            break;
        }
    }
    return 33;
}

//风云宴 韩湘子
int banquetRule2(BanquetStrictRule **strictRule, BanquetLenientRule **lenientRule, States &s, int rank) {
    int d = rank * DISH_PER_CHEF * CHEFS_PER_GUEST;
    // 第1轮
    // 条件：三道炒：下两阶段切技法料理饱腹感-1
    if (s.recipe[d + 0]->cookAbility.stirfry > 0 &&
        s.recipe[d + 1]->cookAbility.stirfry > 0 &&
        s.recipe[d + 2]->cookAbility.stirfry > 0) {
        for (int i = d + 3; i < d + 9; i++) {
            if (s.recipe[i]->cookAbility.knife > 0) {
                strictRule[i]->addRule.full += -1;
            }
        }
    }
    // 条件：三道蒸：下两阶段烤技法料理饱腹感-1
    if (s.recipe[d + 0]->cookAbility.steam > 0 &&
        s.recipe[d + 1]->cookAbility.steam > 0 &&
        s.recipe[d + 2]->cookAbility.steam > 0) {
        for (int i = d + 3; i < d + 9; i++) {
            if (s.recipe[i]->cookAbility.bake > 0) {
                strictRule[i]->addRule.full += -1;
            }
        }
    }
    // 条件：三道煮：下两阶段炸技法料理饱腹感-1
    if (s.recipe[d + 0]->cookAbility.boil > 0 &&
        s.recipe[d + 1]->cookAbility.boil > 0 &&
        s.recipe[d + 2]->cookAbility.boil > 0) {
        for (int i = d + 3; i < d + 9; i++) {
            if (s.recipe[i]->cookAbility.fry > 0) {
                strictRule[i]->addRule.full += -1;
            }
        }
    }
    // 条件：3火：本道料理售价+100%
    for (int i = d + 0; i < d + 3; i++) {
        if (s.recipe[i]->rarity == 3) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }
    // 第2轮
    // 条件：苦：本道料理售价+100%
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->flavor.bitter) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }
    // 条件：辣：本道料理意图生效次数加一
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->flavor.spicy) {
            lenientRule[i]->oneMore();
            break;
        }
    }
    // 条件：第二道菜：第二道菜基础售价+200
    lenientRule[d + 4]->baseRule.directAdd += 200;
    // 条件：2火：本道料理售价+100%
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->rarity == 2) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }
    // 第3轮
    // 条件：优：本道料理基础售价+50%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 2) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    // 条件：特：本道料理饱腹感+2
    for (int i = d + 6; i < d + 9; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 3) {
            lenientRule[i]->addRule.full += 2;
            break;
        }
    }
    // 条件：神：本道料理饱腹感+3
    for (int i = d + 6; i < d + 9; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 4) {
            lenientRule[i]->addRule.full += 3;
            break;
        }
    }
    // 条件：传：本道料理饱腹感+4
    for (int i = d + 6; i < d + 9; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 5) {
            lenientRule[i]->addRule.full += 4;
            break;
        }
    }
    return 15;
}

//风云宴 玉贵人
int banquetRule3(BanquetStrictRule **strictRule, BanquetLenientRule **lenientRule, States &s, int rank) {
    int d = rank * DISH_PER_CHEF * CHEFS_PER_GUEST;
    // 第1轮
    // 条件：三道炒：下阶段切技法料理售价+100%
    if (s.recipe[d + 0]->cookAbility.stirfry > 0 &&
        s.recipe[d + 1]->cookAbility.stirfry > 0 &&
        s.recipe[d + 2]->cookAbility.stirfry > 0) {
        for (int i = d + 3; i < d + 6; i++) {
            if (s.recipe[i]->cookAbility.knife > 0) {
                strictRule[i]->addRule.buff += 100;
            }
        }
    }
    // 条件：三道烤：下阶段煮技法料理售价+100%
    if (s.recipe[d + 0]->cookAbility.bake > 0 &&
        s.recipe[d + 1]->cookAbility.bake > 0 &&
        s.recipe[d + 2]->cookAbility.bake > 0) {
        for (int i = d + 3; i < d + 6; i++) {
            if (s.recipe[i]->cookAbility.boil > 0) {
                strictRule[i]->addRule.buff += 100;
            }
        }
    }
    // 条件：三道炸：下阶段蒸技法料理售价+100%
    if (s.recipe[d + 0]->cookAbility.fry > 0 &&
        s.recipe[d + 1]->cookAbility.fry > 0 &&
        s.recipe[d + 2]->cookAbility.fry > 0) {
        for (int i = d + 3; i < d + 6; i++) {
            if (s.recipe[i]->cookAbility.steam > 0) {
                strictRule[i]->addRule.buff += 100;
            }
        }
    }
    // 条件：酸味: 本道料理基础售价+50%
    for (int i = d + 0; i < d + 3; i++) {
        if (s.recipe[i]->flavor.sour) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }   


    // 第2轮
    // 条件：五火：本道料理售价+50%
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->rarity == 5) {
            lenientRule[i]->addRule.buff += 50;
            break;
        }
    }
    // 条件：酸味: 饱腹感-4
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->flavor.sour) {
            lenientRule[i]->addRule.full += -4;
            break;
        }
    }
    // 条件：五火：本道料理意图+1
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->rarity == 5) {
            lenientRule[i]->oneMore();
            break;
        }
    }
    // 条件：四火：下道料理意图+1
    for (int i = d + 3; i < d + 5; i++) {
        if (s.recipe[i]->rarity == 4) {
            lenientRule[i + 1]->oneMore();
            break;
        }
    }

    
    // 第3轮
    // 条件：蒸：本道料理售价-150%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->cookAbility.steam > 0) {
            lenientRule[i]->addRule.buff += -150;
            break;
        }
    }
    // 条件：煮：本道料理售价-150%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->cookAbility.boil > 0) {
            lenientRule[i]->addRule.buff += -150;
            break;
        }
    }
    // 条件：切：本道料理饱腹感-3
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->cookAbility.knife > 0) {
            lenientRule[i]->addRule.full += -3;
            break;
        }
    }
    // 条件：一火：本道料理基础售价+50%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->rarity == 1) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    return 19;
}

//风云宴 苏妲己
int banquetRule4(BanquetStrictRule **strictRule, BanquetLenientRule **lenientRule, States &s, int rank) {
    int d = rank * DISH_PER_CHEF * CHEFS_PER_GUEST;
    // 第1轮
    // 条件：三道切：下阶段切技法料理售价+100%
    if (s.recipe[d + 0]->cookAbility.knife > 0 &&
        s.recipe[d + 1]->cookAbility.knife > 0 &&
        s.recipe[d + 2]->cookAbility.knife > 0) {
        for (int i = d + 3; i < d + 6; i++) {
            if (s.recipe[i]->cookAbility.knife > 0) {
                strictRule[i]->addRule.buff += 100;
            }
        }
    }
    // 条件：三道煮：下阶段煮技法料理售价+100%
    if (s.recipe[d + 0]->cookAbility.boil > 0 &&
        s.recipe[d + 1]->cookAbility.boil > 0 &&
        s.recipe[d + 2]->cookAbility.boil > 0) {
        for (int i = d + 3; i < d + 6; i++) {
            if (s.recipe[i]->cookAbility.boil > 0) {
                strictRule[i]->addRule.buff += 100;
            }
        }
    }
    // 条件：三道蒸：下阶段蒸技法料理售价+100%
    if (s.recipe[d + 0]->cookAbility.steam > 0 &&
        s.recipe[d + 1]->cookAbility.steam > 0 &&
        s.recipe[d + 2]->cookAbility.steam > 0) {
        for (int i = d + 3; i < d + 6; i++) {
            if (s.recipe[i]->cookAbility.steam > 0) {
                strictRule[i]->addRule.buff += 100;
            }
        }
    }
    // 条件：苦味料理: 本道料理售价+100%
    for (int i = d + 0; i < d + 3; i++) {
        if (s.recipe[i]->flavor.bitter) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }
    
    // 第2轮
    // 条件：甜味料理: 饱腹感+3
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->flavor.sweet) {
            lenientRule[i]->addRule.full += 3;
            break;
        }
    }
    // 条件：苦味料理：本道料理基础售价+50%
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->flavor.bitter) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    // 条件：第三道菜：第三道菜基础售价+200
    lenientRule[d + 5]->baseRule.directAdd += 200;
    // 条件：五火：本道料理售价-100%
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->rarity == 5) {
            lenientRule[i]->addRule.buff += -100;
            break;
        }
    }
    // 第3轮
    // 条件：苦味料理: 本道料理售价+100%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->flavor.bitter) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }
    // 条件：三火：本道料理饱腹感+2
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->rarity == 3) {
            lenientRule[i]->addRule.full += 2;
            break;
        }
    }
    // 条件：炒：本道料理基础售价+50%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->cookAbility.stirfry > 0) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    // 条件：第二道菜：第二道菜意图生效次数+1
    lenientRule[d + 7]->oneMore();
    return 32;
}

//风云宴 何仙姑
int banquetRule5(BanquetStrictRule **strictRule, BanquetLenientRule **lenientRule, States &s, int rank) {
    int d = rank * DISH_PER_CHEF * CHEFS_PER_GUEST;
    // 第1轮
    // 条件：三道炒：下阶段蒸技法料理售价+100%
    if (s.recipe[d + 0]->cookAbility.stirfry > 0 &&
        s.recipe[d + 1]->cookAbility.stirfry > 0 &&
        s.recipe[d + 2]->cookAbility.stirfry > 0) {
        for (int i = d + 3; i < d + 6; i++) {
            if (s.recipe[i]->cookAbility.steam > 0) {
                strictRule[i]->addRule.buff += 100;
            }
        }
    }
    // 条件：酸: 本道料理饱腹感-2
    for (int i = d + 0; i < d + 3; i++) {
        if (s.recipe[i]->flavor.sour) {
            lenientRule[i]->addRule.full += -2;
            break;
        }
    }
    // 条件：咸: 本道料理售价+100%
    for (int i = d + 0; i < d + 3; i++) {
        if (s.recipe[i]->flavor.salty) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }
    // 条件：鲜: 本道料理基础售价+50%
    for (int i = d + 0; i < d + 3; i++) {
        if (s.recipe[i]->flavor.tasty) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    
    // 第2轮
    // 条件：二火：下道料理为蒸时售价+100%
    for (int i = d + 3; i < d + 5; i++) {
        if (s.recipe[i]->rarity == 2) {
            if (s.recipe[i + 1]->cookAbility.steam) {
                lenientRule[i + 1]->addRule.buff += 100;
            }
            break;
        }
    }
    // 条件：切：下道料理为蒸时基础售价+200
    for (int i = d + 3; i < d + 5; i++) {
        if (s.recipe[i]->cookAbility.knife) {
            if (s.recipe[i + 1]->cookAbility.steam) {
                lenientRule[i + 1]->baseRule.directAdd += 200;
            }
            break;
        }
    }
    // 条件：五火：本道料理饱腹感-2
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->rarity == 5) {
            lenientRule[i + 1]->addRule.full += -2;
            break;
        }
    }
    // 条件：第三道菜：第三道菜售价+100%
    lenientRule[d + 5]->addRule.buff += 100;
    
    // 第3轮
    // 条件：第二道菜：第二道菜意图生效次数+1
    lenientRule[d + 7]->oneMore();
    // 条件：五火：本道料理基础售价+50%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->rarity == 5) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    // 条件：优：下道料理意图生效次数+1
    for (int i = d + 6; i < d + 8; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 2) {
            lenientRule[i + 1]->oneMore();
            break;
        }
    }
    // 条件：神：本道料理饱腹感-5
    for (int i = d + 6; i < d + 9; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 4) {
            lenientRule[i]->addRule.full += -5;
            break;
        }
    }
    return 22;
}

//风云宴 铁拐李
int banquetRule6(BanquetStrictRule **strictRule, BanquetLenientRule **lenientRule, States &s, int rank) {
    int d = rank * DISH_PER_CHEF * CHEFS_PER_GUEST;
    // 第1轮
    // 条件：三道烤：下阶段切技法料理售价+100%
    if (s.recipe[d + 0]->cookAbility.bake > 0 &&
        s.recipe[d + 1]->cookAbility.bake > 0 &&
        s.recipe[d + 2]->cookAbility.bake > 0) {
        for (int i = d + 3; i < d + 6; i++) {
            if (s.recipe[i]->cookAbility.knife > 0) {
                strictRule[i]->addRule.buff += 100;
            }
        }
    }
    // 条件：三道炸：下阶段煮技法料理售价+100%
    if (s.recipe[d + 0]->cookAbility.fry > 0 &&
        s.recipe[d + 1]->cookAbility.fry > 0 &&
        s.recipe[d + 2]->cookAbility.fry > 0) {
        for (int i = d + 3; i < d + 6; i++) {
            if (s.recipe[i]->cookAbility.boil > 0) {
                strictRule[i]->addRule.buff += 100;
            }
        }
    }
    // 条件：咸: 本道料理售价-150%
    for (int i = d + 0; i < d + 3; i++) {
        if (s.recipe[i]->flavor.salty) {
            lenientRule[i]->addRule.buff += -150;
            break;
        }
    }
    // 条件：鲜: 本道料理售价-150%
    for (int i = d + 0; i < d + 3; i++) {
        if (s.recipe[i]->flavor.tasty) {
            lenientRule[i]->addRule.buff += -150;
            break;
        }
    }
    
    // 第2轮
    // 条件：切：下道料理为辣时基础售价+50%
    for (int i = d + 3; i < d + 5; i++) {
        if (s.recipe[i]->cookAbility.knife) {
            if (s.recipe[i + 1]->flavor.spicy) {
                lenientRule[i + 1]->baseRule.buff += 50;
            }
            break;
        }
    }
    // 条件：煮：下道料理为酸时基础售价+200
    for (int i = d + 3; i < d + 5; i++) {
        if (s.recipe[i]->cookAbility.boil) {
            if (s.recipe[i + 1]->flavor.sour) {
                lenientRule[i + 1]->baseRule.directAdd += 200;
            }
            break;
        }
    }
    // 条件：辣：下道料理为煮时售价+100%
    for (int i = d + 3; i < d + 5; i++) {
        if (s.recipe[i]->flavor.spicy) {
            if (s.recipe[i + 1]->cookAbility.boil) {
                lenientRule[i + 1]->addRule.buff += 100;
            }
            break;
        }
    }
    // 条件：酸：本道料理售价+100%
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->flavor.sour) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }
    
    // 第3轮    
    // 条件：鲜：本道料理饱腹感+2
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->flavor.tasty) {
            lenientRule[i]->addRule.full += 2;
            break;
        }
    } 
    // 条件：咸：本道料理饱腹感+2
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->flavor.salty) {
            lenientRule[i]->addRule.full += 2;
            break;
        }
    }
    // 条件：烤：本道料理基础售价+50%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->cookAbility.bake) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    // 条件：炸：本道料理售价+100%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->cookAbility.fry) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }
    return 30;
}

//风云宴 何仙姑2
int banquetRule7(BanquetStrictRule **strictRule, BanquetLenientRule **lenientRule, States &s, int rank) {
    int d = rank * DISH_PER_CHEF * CHEFS_PER_GUEST;
    // 第1轮
    // 条件：三道炒：下两阶段切技法料理售价+50%
    if (s.recipe[d + 0]->cookAbility.stirfry > 0 &&
        s.recipe[d + 1]->cookAbility.stirfry > 0 &&
        s.recipe[d + 2]->cookAbility.stirfry > 0) {
        for (int i = d + 3; i < d + 9; i++) {
            if (s.recipe[i]->cookAbility.knife > 0) {
                strictRule[i]->addRule.buff += 50;
            }
        }
    }
    // 条件：三道切：下阶段切技法料理饱腹感-1
    if (s.recipe[d + 0]->cookAbility.knife > 0 &&
        s.recipe[d + 1]->cookAbility.knife > 0 &&
        s.recipe[d + 2]->cookAbility.knife > 0) {
        for (int i = d + 3; i < d + 6; i++) {
            if (s.recipe[i]->cookAbility.knife > 0) {
                strictRule[i]->addRule.full += -1;
            }
        }
    }
    // 条件：四火: 本道料理售价-100%
    for (int i = d + 0; i < d + 3; i++) {
        if (s.recipe[i]->rarity == 4) {
            lenientRule[i]->addRule.buff += -100;
            break;
        }
    }
    // 条件：五火: 本道料理售价-100%
    for (int i = d + 0; i < d + 3; i++) {
        if (s.recipe[i]->rarity == 5) {
            lenientRule[i]->addRule.buff += -100;
            break;
        }
    }
    
    // 第2轮
    // 条件：五火: 本道料理售价-100%
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->rarity == 5) {
            lenientRule[i]->addRule.buff += -100;
            break;
        }
    }    
    // 条件：神：下道料理意图生效次数+1
    for (int i = d + 3; i < d + 5; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 4) {
            lenientRule[i+1]->oneMore();
            break;
        }
    }
    // 条件：传：本道料理基础售价+50%
    for (int i = d + 3; i < d + 6; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 5) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    // 条件：烤：本道料理基础售价+50%
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->cookAbility.bake > 0) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }

    
    // 第3轮   
    // 条件：五火: 本道料理售价-100%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->rarity == 5) {
            lenientRule[i]->addRule.buff += -100;
            break;
        }
    }   
    // 条件：传：本道料理饱腹感+3
    for (int i = d + 6; i < d + 9; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 5) {
            lenientRule[i]->addRule.full += 3;
            break;
        }
    }
    // 条件：三火: 本道料理饱腹感-3
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->rarity == 3) {
            lenientRule[i]->addRule.full += -3;
            break;
        }
    }   
    // 条件：苦: 本道料理饱腹感-5
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->flavor.bitter) {
            lenientRule[i]->addRule.full += -5;
            break;
        }
    }   
    return 25;
}

//风云宴 胡喜媚
int banquetRule8(BanquetStrictRule **strictRule, BanquetLenientRule **lenientRule, States &s, int rank) {
    int d = rank * DISH_PER_CHEF * CHEFS_PER_GUEST;
    // 第1轮
    // 条件：三火: 下道料理饱腹感-3
    for (int i = d + 0; i < d + 2; i++) {
        if (s.recipe[i]->rarity == 3) {
            lenientRule[i+1]->addRule.full += -3;
            break;
        }
    }
    // 条件：四火: 下道料理饱腹感-2
    for (int i = d + 0; i < d + 2; i++) {
        if (s.recipe[i]->rarity == 4) {
            lenientRule[i+1]->addRule.full += -2;
            break;
        }
    }
    // 条件：五火: 本道料理售价+100%
    for (int i = d + 0; i < d + 3; i++) {
        if (s.recipe[i]->rarity == 5) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }
    // 条件：煮: 下道料理饱腹感-2
    for (int i = d + 0; i < d + 2; i++) {
        if (s.recipe[i]->cookAbility.boil > 0) {
            lenientRule[i+1]->addRule.full += -2;
            break;
        }
    }
    
    // 第2轮 
    // 条件：神：下道料理意图生效次数+1
    for (int i = d + 3; i < d + 5; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 4) {
            lenientRule[i+1]->oneMore();
            break;
        }
    }
    // 条件：四火：本道料理饱腹感-3
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->rarity == 4) {
            lenientRule[i]->addRule.full += -3;
            break;
        }
    }
    // 条件：切：本道料理基础售价+50%
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->cookAbility.knife) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    // 条件：酸：本道料理基础售价+50%
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->flavor.sour) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    
    // 第3轮    
    // 条件：传：本道料理售价+100%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 5) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }
    // 条件：五火：本道料理售价+100%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->rarity == 5) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }
    // 条件：甜：本道料理饱腹感+2
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->flavor.sweet) {
            lenientRule[i]->addRule.full += 2;
            break;
        }
    }
    // 条件：切：本道料理饱腹感+2
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->cookAbility.knife) {
            lenientRule[i]->addRule.full += 2;
            break;
        }
    }
    return 15;
}

//风云宴 韩湘子2
int banquetRule9(BanquetStrictRule **strictRule, BanquetLenientRule **lenientRule, States &s, int rank) {
    int d = rank * DISH_PER_CHEF * CHEFS_PER_GUEST;
    // 第1轮
    // 条件：三道炸：下两阶段煮技法料理饱腹感+1
    if (s.recipe[d + 0]->cookAbility.fry > 0 &&
        s.recipe[d + 1]->cookAbility.fry > 0 &&
        s.recipe[d + 2]->cookAbility.fry > 0) {
        for (int i = d + 3; i < d + 9; i++) {
            if (s.recipe[i]->cookAbility.boil > 0) {
                strictRule[i]->addRule.full += 1;
            }
        }
    }
    // 条件：三道烤：下两阶段蒸技法料理饱腹感+1
    if (s.recipe[d + 0]->cookAbility.bake > 0 &&
        s.recipe[d + 1]->cookAbility.bake > 0 &&
        s.recipe[d + 2]->cookAbility.bake > 0) {
        for (int i = d + 3; i < d + 9; i++) {
            if (s.recipe[i]->cookAbility.steam > 0) {
                strictRule[i]->addRule.full += 1;
            }
        }
    }
    // 条件：5火：本道料理饱腹感+3
    for (int i = d + 0; i < d + 3; i++) {
        if (s.recipe[i]->rarity == 5) {
            lenientRule[i]->addRule.full += 3;
            break;
        }
    }
    // 条件：2火：本道料理饱腹感-2
    for (int i = d + 0; i < d + 3; i++) {
        if (s.recipe[i]->rarity == 2) {
            lenientRule[i]->addRule.full += -2;
            break;
        }
    }
    // 第2轮
    // 条件：2火：本道料理意图生效次数+1
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->rarity == 2) {
            lenientRule[i]->oneMore();
            break;
        }
    }
    // 条件：酸：本道料理售价+100%
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->flavor.sour) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }
    // 条件：切：本道料理基础售价+50%
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->cookAbility.knife > 0) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    // 条件：传：本道料理饱腹感+2
    for (int i = d + 3; i < d + 6; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 5) {
            lenientRule[i]->addRule.full += 2;
            break;
        }
    }
    // 第3轮
    //第3道菜意图生效次数+1
    lenientRule[d + 8]->oneMore();
    // 条件：神：本道料理饱腹感+1
    for (int i = d + 6; i < d + 9; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 4) {
            lenientRule[i]->addRule.full += 1;
            break;
        }
    }
    // 条件：4火：本道料理饱腹感+1
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->rarity == 4) {
            lenientRule[i]->addRule.full += 1;
            break;
        }
    }
    // 条件：1火：本道料理饱腹感-3
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->rarity == 1) {
            lenientRule[i]->addRule.full += -3;
            break;
        }
    }
    return 38;
}

//风云宴 蓝采和2
int banquetRule10(BanquetStrictRule **strictRule, BanquetLenientRule **lenientRule, States &s, int rank) {
    int d = rank * DISH_PER_CHEF * CHEFS_PER_GUEST;
    // 第1轮
    // 条件：三道切：下两阶段切技法料理饱腹感-2
    if (s.recipe[d + 0]->cookAbility.knife > 0 &&
        s.recipe[d + 1]->cookAbility.knife > 0 &&
        s.recipe[d + 2]->cookAbility.knife > 0) {
        for (int i = d + 3; i < d + 9; i++) {
            if (s.recipe[i]->cookAbility.knife > 0) {
                strictRule[i]->addRule.full += -2;
            }
        }
    }
    // 条件：三道蒸：下两阶段炒技法料理饱腹感+1
    if (s.recipe[d + 0]->cookAbility.steam > 0 &&
        s.recipe[d + 1]->cookAbility.steam > 0 &&
        s.recipe[d + 2]->cookAbility.steam > 0) {
        for (int i = d + 3; i < d + 9; i++) {
            if (s.recipe[i]->cookAbility.stirfry > 0) {
                strictRule[i]->addRule.full += 1;
            }
        }
    }
    // 条件：三道烤：下两阶段切技法料理售价+100%
    if (s.recipe[d + 0]->cookAbility.bake > 0 &&
        s.recipe[d + 1]->cookAbility.bake > 0 &&
        s.recipe[d + 2]->cookAbility.bake > 0) {
        for (int i = d + 3; i < d + 9; i++) {
            if (s.recipe[i]->cookAbility.knife > 0) {
                strictRule[i]->addRule.buff += 100;
            }
        }
    }
    // 条件：神：本道料理售价-100%
    for (int i = d + 0; i < d + 3; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 4) {
            lenientRule[i]->addRule.buff += -100;
            break;
        }
    }
    // 第2轮
    // 条件：神：本道料理售价-100%
    for (int i = d + 3; i < d + 6; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 4) {
            lenientRule[i]->addRule.buff += -100;
            break;
        }
    }
    // 条件：1火：下道料理意图生效次数+1
    for (int i = d + 3; i < d + 5; i++) {
        if (s.recipe[i]->rarity == 1) {
            lenientRule[i+1]->oneMore();
            break;
        }
    }
    // 条件：4火：本道料理售价+100%
    for (int i = d + 3; i < d + 6;i++) {
        if (s.recipe[i]->rarity == 4) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }
    // 条件：甜：本道料理基础售价+50%
    for (int i = d + 3; i < d + 6; i++) {
        if (s.recipe[i]->flavor.sweet) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    // 第3轮
    // 条件：神：本道料理售价-100%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.chef[i/3]->skill.ability / s.recipe[i]->cookAbility >= 4) {
            lenientRule[i]->addRule.buff += -100;
            break;
        }
    }
    // 条件：酸：本道料理饱腹感-4
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->flavor.sour) {
            lenientRule[i]->addRule.full += -4;
            break;
        }
    }
    // 条件：苦：本道料理售价+100%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->flavor.bitter) {
            lenientRule[i]->addRule.buff += 100;
            break;
        }
    }
    // 条件：烤：本道料理基础售价+50%
    for (int i = d + 6; i < d + 9; i++) {
        if (s.recipe[i]->cookAbility.bake > 0) {
            lenientRule[i]->baseRule.buff += 50;
            break;
        }
    }
    return 28;
}

//本程序由generateRule.py生成
//风云宴 胡喜媚2
int banquetRule11(BanquetStrictRule **strictRule, BanquetLenientRule **lenientRule, States &s, int rank) {
    int d = rank * DISH_PER_CHEF * CHEFS_PER_GUEST;

	//第1轮
	//条件：三道炸
	//效果：下两阶段煮技法料理饱腹感+1
	if (s.recipe[d + 0]->cookAbility.fry &&
	    s.recipe[d + 1]->cookAbility.fry &&
	    s.recipe[d + 2]->cookAbility.fry) {
		for (int i = d + 3; i < d + 9; i++) {
			if (s.recipe[i]->cookAbility.boil) {
				strictRule[i]->addRule.full += 1;
			}
		}
	}
	//条件：三道烤
	//效果：下两阶段蒸技法料理饱腹感+1
	if (s.recipe[d + 0]->cookAbility.bake &&
	    s.recipe[d + 1]->cookAbility.bake &&
	    s.recipe[d + 2]->cookAbility.bake) {
		for (int i = d + 3; i < d + 9; i++) {
			if (s.recipe[i]->cookAbility.steam) {
				strictRule[i]->addRule.full += 1;
			}
		}
	}
	//条件：三道炒
	//效果：下两阶段切技法料理饱腹感+1
	if (s.recipe[d + 0]->cookAbility.stirfry &&
	    s.recipe[d + 1]->cookAbility.stirfry &&
	    s.recipe[d + 2]->cookAbility.stirfry) {
		for (int i = d + 3; i < d + 9; i++) {
			if (s.recipe[i]->cookAbility.knife) {
				strictRule[i]->addRule.full += 1;
			}
		}
	}
	//条件：辣
	//效果：本道料理售价+100%
	for (int i = d + 0; i < d + 3; i++) {
		if (s.recipe[i]->flavor.spicy) {
			lenientRule[i]->addRule.buff += 100;
			break;
		}
	}

	//第2轮
	//条件：1火
	//效果：本道料理售价+100%
	for (int i = d + 3; i < d + 6; i++) {
		if (s.recipe[i]->rarity == 1) {
			lenientRule[i]->addRule.buff += 100;
			break;
		}
	}
	//条件：1火
	//效果：本道料理饱腹感+5
	for (int i = d + 3; i < d + 6; i++) {
		if (s.recipe[i]->rarity == 1) {
			lenientRule[i]->addRule.full += 5;
			break;
		}
	}
	//条件：第二道菜
	//效果：第二道菜意图生效次数加一
	lenientRule[d + 4]->oneMore();
	//条件：辣
	//效果：本道料理基础售价+200
	for (int i = d + 3; i < d + 6; i++) {
		if (s.recipe[i]->flavor.spicy) {
			lenientRule[i]->baseRule.directAdd += 200;
			break;
		}
	}

	//第3轮
	//条件：烤
	//效果：下道料理为辣时饱腹感+3
	for (int i = d + 6; i < d + 8; i++) {
		if (s.recipe[i]->cookAbility.bake) {
			if (s.recipe[i + 1]->flavor.spicy) {
				lenientRule[i + 1]->addRule.full += 3;
			}
			break;
		}
	}
	//条件：3火
	//效果：本道料理饱腹感+2
	for (int i = d + 6; i < d + 9; i++) {
		if (s.recipe[i]->rarity == 3) {
			lenientRule[i]->addRule.full += 2;
			break;
		}
	}
	//条件：炸
	//效果：本道料理售价+100%
	for (int i = d + 6; i < d + 9; i++) {
		if (s.recipe[i]->cookAbility.fry) {
			lenientRule[i]->addRule.buff += 100;
			break;
		}
	}
	//条件：辣
	//效果：本道料理基础售价+50%
	for (int i = d + 6; i < d + 9; i++) {
		if (s.recipe[i]->flavor.spicy) {
			lenientRule[i]->baseRule.buff += 50;
			break;
		}
	}
	return 44;
}

//本程序由generateRule.py生成
//风云宴 曹国舅
int banquetRule12(BanquetStrictRule **strictRule, BanquetLenientRule **lenientRule, States &s, int rank) {
    int d = rank * DISH_PER_CHEF * CHEFS_PER_GUEST;

	//第1轮
	//条件：三道炒
	//效果：下阶段煮技法料理售价+100%
	if (s.recipe[d + 0]->cookAbility.stirfry &&
	    s.recipe[d + 1]->cookAbility.stirfry &&
	    s.recipe[d + 2]->cookAbility.stirfry) {
		for (int i = d + 3; i < d + 6; i++) {
			if (s.recipe[i]->cookAbility.boil) {
				strictRule[i]->addRule.buff += 100;
			}
		}
	}
	//条件：切
	//效果：本道料理售价+100%
	for (int i = d + 0; i < d + 3; i++) {
		if (s.recipe[i]->cookAbility.knife) {
			lenientRule[i]->addRule.buff += 100;
			break;
		}
	}
	//条件：甜
	//效果：本道料理基础售价+50%
	for (int i = d + 0; i < d + 3; i++) {
		if (s.recipe[i]->flavor.sweet) {
			lenientRule[i]->baseRule.buff += 50;
			break;
		}
	}
	//条件：第二道菜
	//效果：第二道菜意图生效次数加一
	lenientRule[d + 1]->oneMore();

	//第2轮
	//条件：切
	//效果：本道料理基础售价+50%
	for (int i = d + 3; i < d + 6; i++) {
		if (s.recipe[i]->cookAbility.knife) {
			lenientRule[i]->baseRule.buff += 50;
			break;
		}
	}
	//条件：蒸
	//效果：本道料理基础售价+200
	for (int i = d + 3; i < d + 6; i++) {
		if (s.recipe[i]->cookAbility.steam) {
			lenientRule[i]->baseRule.directAdd += 200;
			break;
		}
	}
	//条件：1火
	//效果：本道料理售价+100%
	for (int i = d + 3; i < d + 6; i++) {
		if (s.recipe[i]->rarity == 1) {
			lenientRule[i]->addRule.buff += 100;
			break;
		}
	}
	//条件：4火
	//效果：本道料理意图生效次数加一
	for (int i = d + 3; i < d + 6; i++) {
		if (s.recipe[i]->rarity == 4) {
			lenientRule[i]->oneMore();
			break;
		}
	}

	//第3轮
	//条件：5火
	//效果：本道料理售价+100%
	for (int i = d + 6; i < d + 9; i++) {
		if (s.recipe[i]->rarity == 5) {
			lenientRule[i]->addRule.buff += 100;
			break;
		}
	}
	//条件：2火
	//效果：本道料理饱腹感-4
	for (int i = d + 6; i < d + 9; i++) {
		if (s.recipe[i]->rarity == 2) {
			lenientRule[i]->addRule.full += -4;
			break;
		}
	}
	//条件：第三道菜
	//效果：第三道菜意图生效次数加一
	lenientRule[d + 8]->oneMore();
	//条件：传
	//效果：本道料理基础售价+50%
	for (int i = d + 6; i < d + 9; i++) {
		if (s.chef[i / 3]->skill.ability / s.recipe[i]->cookAbility >= 5) {
			lenientRule[i]->baseRule.buff += 50;
			break;
		}
	}
	return 19;
}

//本程序由generateRule.py生成
//风云宴 钟离权
int banquetRule13(BanquetStrictRule **strictRule, BanquetLenientRule **lenientRule, States &s, int rank) {
    int d = rank * DISH_PER_CHEF * CHEFS_PER_GUEST;

	//第1轮
	//条件：三道烤
	//效果：下阶段煮技法料理售价+100%
	if (s.recipe[d + 0]->cookAbility.bake &&
	    s.recipe[d + 1]->cookAbility.bake &&
	    s.recipe[d + 2]->cookAbility.bake) {
		for (int i = d + 3; i < d + 6; i++) {
			if (s.recipe[i]->cookAbility.boil) {
				strictRule[i]->addRule.buff += 100;
			}
		}
	}
	//条件：三道切
	//效果：下阶段蒸技法料理售价+100%
	if (s.recipe[d + 0]->cookAbility.knife &&
	    s.recipe[d + 1]->cookAbility.knife &&
	    s.recipe[d + 2]->cookAbility.knife) {
		for (int i = d + 3; i < d + 6; i++) {
			if (s.recipe[i]->cookAbility.steam) {
				strictRule[i]->addRule.buff += 100;
			}
		}
	}
	//条件：3火
	//效果：下道料理为辣时售价+100%
	for (int i = d + 0; i < d + 2; i++) {
		if (s.recipe[i]->rarity == 3) {
			if (s.recipe[i + 1]->flavor.spicy) {
				lenientRule[i + 1]->addRule.buff += 100;
			}
			break;
		}
	}
	//条件：神
	//效果：本道料理基础售价+50%
	for (int i = d + 0; i < d + 3; i++) {
		if (s.chef[i / 3]->skill.ability / s.recipe[i]->cookAbility >= 4) {
			lenientRule[i]->baseRule.buff += 50;
			break;
		}
	}

	//第2轮
	//条件：辣
	//效果：本道料理饱腹感+5
	for (int i = d + 3; i < d + 6; i++) {
		if (s.recipe[i]->flavor.spicy) {
			lenientRule[i]->addRule.full += 5;
			break;
		}
	}
	//条件：第三道菜
	//效果：第三道菜意图生效次数加一
	lenientRule[d + 5]->oneMore();
	//条件：2火
	//效果：下道料理为辣时售价+100%
	for (int i = d + 3; i < d + 5; i++) {
		if (s.recipe[i]->rarity == 2) {
			if (s.recipe[i + 1]->flavor.spicy) {
				lenientRule[i + 1]->addRule.buff += 100;
			}
			break;
		}
	}
	//条件：优
	//效果：本道料理基础售价+200
	for (int i = d + 3; i < d + 6; i++) {
		if (s.chef[i / 3]->skill.ability / s.recipe[i]->cookAbility >= 2) {
			lenientRule[i]->baseRule.directAdd += 200;
			break;
		}
	}

	//第3轮
	//条件：4火
	//效果：本道料理意图生效次数加一
	for (int i = d + 6; i < d + 9; i++) {
		if (s.recipe[i]->rarity == 4) {
			lenientRule[i]->oneMore();
			break;
		}
	}
	//条件：特
	//效果：本道料理饱腹感+2
	for (int i = d + 6; i < d + 9; i++) {
		if (s.chef[i / 3]->skill.ability / s.recipe[i]->cookAbility >= 3) {
			lenientRule[i]->addRule.full += 2;
			break;
		}
	}
	//条件：神
	//效果：本道料理基础售价+200
	for (int i = d + 6; i < d + 9; i++) {
		if (s.chef[i / 3]->skill.ability / s.recipe[i]->cookAbility >= 4) {
			lenientRule[i]->baseRule.directAdd += 200;
			break;
		}
	}
	//条件：传
	//效果：本道料理基础售价+50%
	for (int i = d + 6; i < d + 9; i++) {
		if (s.chef[i / 3]->skill.ability / s.recipe[i]->cookAbility >= 5) {
			lenientRule[i]->baseRule.buff += 50;
			break;
		}
	}
	return 40;
}
//本程序由generateRule.py生成
//风云宴 打更人
int banquetRule14(BanquetStrictRule **strictRule, BanquetLenientRule **lenientRule, States &s, int rank) {
    int d = rank * DISH_PER_CHEF * CHEFS_PER_GUEST;

	//第1轮
	//条件：传
	//效果：本道料理意图生效次数加一
	for (int i = d + 0; i < d + 3; i++) {
		if (s.chef[i / 3]->skill.ability / s.recipe[i]->cookAbility >= 5) {
			lenientRule[i]->oneMore();
			break;
		}
	}
	//条件：蒸
	//效果：本道料理售价+100%
	for (int i = d + 0; i < d + 3; i++) {
		if (s.recipe[i]->cookAbility.steam) {
			lenientRule[i]->addRule.buff += 100;
			break;
		}
	}
	//条件：鲜
	//效果：本道料理饱腹感+2
	for (int i = d + 0; i < d + 3; i++) {
		if (s.recipe[i]->flavor.tasty) {
			lenientRule[i]->addRule.full += 2;
			break;
		}
	}
	//条件：三道炒
	//效果：下阶段烤技法料理售价+100%
	if (s.recipe[d + 0]->cookAbility.stirfry &&
	    s.recipe[d + 1]->cookAbility.stirfry &&
	    s.recipe[d + 2]->cookAbility.stirfry) {
		for (int i = d + 3; i < d + 6; i++) {
			if (s.recipe[i]->cookAbility.bake) {
				strictRule[i]->addRule.buff += 100;
			}
		}
	}

	//第2轮
	//条件：酸
	//效果：本道料理基础售价+50%
	for (int i = d + 3; i < d + 6; i++) {
		if (s.recipe[i]->flavor.sour) {
			lenientRule[i]->baseRule.buff += 50;
			break;
		}
	}
	//条件：1火
	//效果：本道料理基础售价+300
	for (int i = d + 3; i < d + 6; i++) {
		if (s.recipe[i]->rarity == 1) {
			lenientRule[i]->baseRule.directAdd += 300;
			break;
		}
	}
	//条件：三道烤
	//效果：下阶段炸技法料理售价+50%
	if (s.recipe[d + 3]->cookAbility.bake &&
	    s.recipe[d + 4]->cookAbility.bake &&
	    s.recipe[d + 5]->cookAbility.bake) {
		for (int i = d + 6; i < d + 9; i++) {
			if (s.recipe[i]->cookAbility.fry) {
				strictRule[i]->addRule.buff += 50;
			}
		}
	}
	//条件：煮
	//效果：本道料理饱腹感+2
	for (int i = d + 3; i < d + 6; i++) {
		if (s.recipe[i]->cookAbility.boil) {
			lenientRule[i]->addRule.full += 2;
			break;
		}
	}

	//第3轮
	//条件：炒
	//效果：本道料理售价-150%
	for (int i = d + 6; i < d + 9; i++) {
		if (s.recipe[i]->cookAbility.stirfry) {
			lenientRule[i]->addRule.buff += -150;
			break;
		}
	}
	//条件：煮
	//效果：本道料理售价-150%
	for (int i = d + 6; i < d + 9; i++) {
		if (s.recipe[i]->cookAbility.boil) {
			lenientRule[i]->addRule.buff += -150;
			break;
		}
	}
	//条件：神
	//效果：本道料理基础售价+200
	for (int i = d + 6; i < d + 9; i++) {
		if (s.chef[i / 3]->skill.ability / s.recipe[i]->cookAbility >= 4) {
			lenientRule[i]->baseRule.directAdd += 200;
			break;
		}
	}
	//条件：4火
	//效果：本道料理售价+100%
	for (int i = d + 6; i < d + 9; i++) {
		if (s.recipe[i]->rarity == 4) {
			lenientRule[i]->addRule.buff += 100;
			break;
		}
	}
	return 20;
}
//本程序由generateRule.py生成
//风云宴 玉贵人2
int banquetRule15(BanquetStrictRule **strictRule, BanquetLenientRule **lenientRule, States &s, int rank) {
    int d = rank * DISH_PER_CHEF * CHEFS_PER_GUEST;

	//第1轮
	//条件：三道切
	//效果：下两阶段煮技法料理饱腹感-2
	if (s.recipe[d + 0]->cookAbility.knife &&
	    s.recipe[d + 1]->cookAbility.knife &&
	    s.recipe[d + 2]->cookAbility.knife) {
		for (int i = d + 3; i < d + 9; i++) {
			if (s.recipe[i]->cookAbility.boil) {
				strictRule[i]->addRule.full += -2;
			}
		}
	}
	//条件：三道炸
	//效果：下两阶段炒技法料理饱腹感-2
	if (s.recipe[d + 0]->cookAbility.fry &&
	    s.recipe[d + 1]->cookAbility.fry &&
	    s.recipe[d + 2]->cookAbility.fry) {
		for (int i = d + 3; i < d + 9; i++) {
			if (s.recipe[i]->cookAbility.stirfry) {
				strictRule[i]->addRule.full += -2;
			}
		}
	}
	//条件：5火
	//效果：本道料理饱腹感-3
	for (int i = d + 0; i < d + 3; i++) {
		if (s.recipe[i]->rarity == 5) {
			lenientRule[i]->addRule.full += -3;
			break;
		}
	}
	//条件：三道蒸
	//效果：下两阶段切技法料理售价+50%
	if (s.recipe[d + 0]->cookAbility.steam &&
	    s.recipe[d + 1]->cookAbility.steam &&
	    s.recipe[d + 2]->cookAbility.steam) {
		for (int i = d + 3; i < d + 9; i++) {
			if (s.recipe[i]->cookAbility.knife) {
				strictRule[i]->addRule.buff += 50;
			}
		}
	}

	//第2轮
	//条件：传
	//效果：本道料理基础售价+50%
	for (int i = d + 3; i < d + 6; i++) {
		if (s.chef[i / 3]->skill.ability / s.recipe[i]->cookAbility >= 5) {
			lenientRule[i]->baseRule.buff += 50;
			break;
		}
	}
	//条件：1火
	//效果：本道料理饱腹感+5
	for (int i = d + 3; i < d + 6; i++) {
		if (s.recipe[i]->rarity == 1) {
			lenientRule[i]->addRule.full += 5;
			break;
		}
	}
	//条件：鲜
	//效果：下道料理为酸时售价+100%
	for (int i = d + 3; i < d + 5; i++) {
		if (s.recipe[i]->flavor.tasty) {
			if (s.recipe[i + 1]->flavor.sour) {
				lenientRule[i + 1]->addRule.buff += 100;
			}
			break;
		}
	}
	//条件：辣
	//效果：下道料理为甜时售价+100%
	for (int i = d + 3; i < d + 5; i++) {
		if (s.recipe[i]->flavor.spicy) {
			if (s.recipe[i + 1]->flavor.sweet) {
				lenientRule[i + 1]->addRule.buff += 100;
			}
			break;
		}
	}

	//第3轮
	//条件：4火
	//效果：本道料理基础售价+50%
	for (int i = d + 6; i < d + 9; i++) {
		if (s.recipe[i]->rarity == 4) {
			lenientRule[i]->baseRule.buff += 50;
			break;
		}
	}
	//条件：3火
	//效果：本道料理基础售价+50%
	for (int i = d + 6; i < d + 9; i++) {
		if (s.recipe[i]->rarity == 3) {
			lenientRule[i]->baseRule.buff += 50;
			break;
		}
	}
	//条件：咸
	//效果：本道料理饱腹感+3
	for (int i = d + 6; i < d + 9; i++) {
		if (s.recipe[i]->flavor.salty) {
			lenientRule[i]->addRule.full += 3;
			break;
		}
	}
	//条件：烤
	//效果：本道料理饱腹感+2
	for (int i = d + 6; i < d + 9; i++) {
		if (s.recipe[i]->cookAbility.bake) {
			lenientRule[i]->addRule.full += 2;
			break;
		}
	}
	return 13;
}

//本程序由generateRule.py生成
//风云宴 张果老
int banquetRule16(BanquetStrictRule **strictRule, BanquetLenientRule **lenientRule, States &s, int rank) {
    int d = rank * DISH_PER_CHEF * CHEFS_PER_GUEST;

	//第1轮
	//条件：烤
	//效果：本道料理售价+100%
	for (int i = d + 0; i < d + 3; i++) {
		if (s.recipe[i]->cookAbility.bake) {
			lenientRule[i]->addRule.buff += 100;
			break;
		}
	}
	//条件：蒸
	//效果：本道料理饱腹感+2
	for (int i = d + 0; i < d + 3; i++) {
		if (s.recipe[i]->cookAbility.steam) {
			lenientRule[i]->addRule.full += 2;
			break;
		}
	}
	//条件：炒
	//效果：本道料理基础售价+200
	for (int i = d + 0; i < d + 3; i++) {
		if (s.recipe[i]->cookAbility.stirfry) {
			lenientRule[i]->baseRule.directAdd += 200;
			break;
		}
	}
	//条件：切
	//效果：本道料理售价+100%
	for (int i = d + 0; i < d + 3; i++) {
		if (s.recipe[i]->cookAbility.knife) {
			lenientRule[i]->addRule.buff += 100;
			break;
		}
	}

	//第2轮
	//条件：第二道菜
	//效果：第二道菜基础售价+50%
	lenientRule[d + 4]->baseRule.buff += 50;
	//条件：1火
	//效果：下道料理意图生效次数加一
	for (int i = d + 3; i < d + 5; i++) {
		if (s.recipe[i]->rarity == 1) {
			lenientRule[i + 1]->oneMore();
			break;
		}
	}
	//条件：切
	//效果：本道料理售价+100%
	for (int i = d + 3; i < d + 6; i++) {
		if (s.recipe[i]->cookAbility.knife) {
			lenientRule[i]->addRule.buff += 100;
			break;
		}
	}
	//条件：炸
	//效果：本道料理意图生效次数加一
	for (int i = d + 3; i < d + 6; i++) {
		if (s.recipe[i]->cookAbility.fry) {
			lenientRule[i]->oneMore();
			break;
		}
	}

	//第3轮
	//条件：苦
	//效果：本道料理饱腹感为8
	for (int i = d + 6; i < d + 9; i++) {
		if (s.recipe[i]->flavor.bitter) {
			lenientRule[i]->addRule.fullAdd = false;
			strictRule[i]->addRule.full = 8;
			break;
		}
	}
	//条件：1火
	//效果：本道料理售价+100%
	for (int i = d + 6; i < d + 9; i++) {
		if (s.recipe[i]->rarity == 1) {
			lenientRule[i]->addRule.buff += 100;
			break;
		}
	}
	//条件：第一道菜
	//效果：第一道菜基础售价+200
	lenientRule[d + 6]->baseRule.directAdd += 200;
	//条件：传
	//效果：本道料理基础售价+200
	for (int i = d + 6; i < d + 9; i++) {
		if (s.chef[i / 3]->skill.ability / s.recipe[i]->cookAbility >= 5) {
			lenientRule[i]->baseRule.directAdd += 200;
			break;
		}
	}
	return 37;
}
#endif