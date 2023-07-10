#include "Calculator.hpp"
#include "Chef.hpp"
#include <cmath>

int strangebuff_handle(Chef &chef, Recipe &recipe, DishBuff &rb);

BanquetInfo getPrice(Chef *chef, Recipe *recipe, BanquetRule r, bool verbose) {
    // std::cout << chef.name << " " << recipe.name << std::endl;
    int grade = chef->skill.ability / recipe->cookAbility;
    // std::cout << grade << std::endl;
    int gradebuff = 0;
    switch (grade) {
    case 0: {
        if (verbose)
            std::cout << "Grade 0" << std::endl;
        {
            BanquetInfo b = {0, 999}; //不能做的不要出现在结果中
            return b;
        }
    }
    case 1:
        gradebuff = 0;
        break;
    case 2:
        gradebuff = 10;
        break;
    case 3:
        gradebuff = 30;
        break;
    case 4:
        gradebuff = 50;
        break;
    default:
        gradebuff = 100;
    }
    gradebuff += chef->skill.rarityBuff[recipe->rarity];
    auto rb = recipe->rarityBuff[recipe->rarity - 1];
    r.lenientRule.merge(r.strictRule); // vscode报错不认友元，但是编译没问题
    BanquetLenientRule rule = r.lenientRule;
    int intentionAddBuff = rule.addRule.buff;
    int intentionBaseBuff = rule.baseRule.buff + chef->skill.abilityBuff.basic;
    int skillBuff = recipe->flavor * chef->skill.flavorBuff +
                    recipe->cookAbility * chef->skill.abilityBuff +
                    recipe->materialCategories * chef->skill.materialBuff +
                    rb.dishBuff + (chef->coinBuffOn ? chef->skill.coinBuff : 0);
    //strange buff handle start
    int strangeBuff = strangebuff_handle(*chef, *recipe, rb);
    skillBuff += strangeBuff;
    //strange buff handle end
    int buff = gradebuff + skillBuff + intentionAddBuff;
    int singlePrice = (int)std::ceil((recipe->price + rule.baseRule.directAdd) *
                                     (1.0 + intentionBaseBuff / 100.0) *
                                     (1.0 + buff / 100.0));
    // std::cout << singlePrice << std::endl;
    int totalPrice = singlePrice * rb.dishNum;
    if (verbose) {
        // chef->print();
        recipe->print();
        std::cout << "等级: " << grade << "，加成" << gradebuff << "%"
                  << std::endl;
        std::cout << "Skill: " << skillBuff << "% ( = 味道"
                  << recipe->flavor * chef->skill.flavorBuff << " + 技法"
                  << recipe->cookAbility * chef->skill.abilityBuff << " + 食材"
                  << recipe->materialCategories * chef->skill.materialBuff
                  << " + 修炼" << rb.dishBuff << " + 金币"
                  << (chef->coinBuffOn ? chef->skill.coinBuff : 0)
                  << " + 其它" << strangeBuff << ")"
                  << std::endl;
        std::cout << "Intention: (基础+" << rule.baseRule.directAdd << "，+"
                  << intentionBaseBuff << "%；售价+" << intentionAddBuff
                  << "%) " << std::endl;
        std::cout << "售价总计Buff: " << buff << "%" << std::endl;
        std::cout << "╰--> 总价: " << totalPrice << std::endl;
    }
    int full;
    if (rule.addRule.fullAdd) {
        full = recipe->rarity + rule.addRule.full;
    } else {
        full = rule.addRule.full;
    }
    BanquetInfo b = {totalPrice, full};
    return b;
}

int strangebuff_handle(Chef &chef, Recipe &recipe, DishBuff &rb) {
    int strangeBuff = 0;
    if (~chef.skill.strangeBuff.ExcessCookbookNum.dishNum) {
        if (rb.dishNum >= chef.skill.strangeBuff.ExcessCookbookNum.dishNum)
            strangeBuff += chef.skill.strangeBuff.ExcessCookbookNum.dishBuff;
    }
    if (~chef.skill.strangeBuff.Rank.dishNum) {
        if (chef.skill.ability / recipe.cookAbility >= chef.skill.strangeBuff.Rank.dishNum)
            strangeBuff += chef.skill.strangeBuff.Rank.dishBuff;
    }
    return strangeBuff;
}