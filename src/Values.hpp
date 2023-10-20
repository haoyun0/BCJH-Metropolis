#ifndef VALUE_HPP
#define VALUE_HPP
#include <iostream>
#include "include/json/json.h"
#include <string>
#include <math.h>
struct DishBuff {
    int dishNum;
    int dishBuff = 0;
};
class MaterialCategoryBuff {
  public:
    int vegetable;
    int meat;
    int fish;
    int creation;
    MaterialCategoryBuff() : vegetable(0), meat(0), fish(0), creation(0) {}
    void add(const MaterialCategoryBuff &m) {
        this->vegetable += m.vegetable;
        this->meat += m.meat;
        this->fish += m.fish;
        this->creation += m.creation;
    }
    void print() {
        std::cout << "MaterialCategoryBuff: Vegetable: " << this->vegetable
                  << "; Meat: " << this->meat << "; Fish: " << this->fish
                  << "; Creation: " << this->creation << std::endl;
    }
};
class FlavorBuff {
  public:
    int sweet;
    int salty;
    int sour;
    int bitter;
    int spicy;
    int tasty;
    FlavorBuff() : sweet(0), salty(0), sour(0), bitter(0), spicy(0), tasty(0) {}
    void add(const FlavorBuff &f) {
        this->sweet += f.sweet;
        this->salty += f.salty;
        this->sour += f.sour;
        this->bitter += f.bitter;
        this->spicy += f.spicy;
        this->tasty += f.tasty;
    }
    void print() {
        std::cout << "FlavorBuff: Sweet: " << this->sweet
                  << "; Salty: " << this->salty << "; Sour: " << this->sour
                  << "; Bitter: " << this->bitter << "; Spicy: " << this->spicy
                  << "; Tasty: " << this->tasty << std::endl;
    }
};
class RarityBuff {
    int rarityBuff[5] = {0, 0, 0, 0, 0};
  public:
    /*几火就是几，不用减一*/
    int &operator[](int i) { return rarityBuff[i - 1]; }
    void add(const RarityBuff &r) { for (int i = 0; i < 5; i++) this->rarityBuff[i] += r.rarityBuff[i]; }
    void print() {
        std::cout << "RarityBuff: ";
        for (int i = 0; i < 5; i++) {
            std::cout << rarityBuff[i] << "% ";
        }
        std::cout << std::endl;
    }
};
class Ability {
  public:
    int stirfry;
    int bake;
    int boil;
    int steam;
    int fry;
    int knife;
    Ability() : stirfry(0), bake(0), boil(0), steam(0), fry(0), knife(0) {}
    Ability(int stirfry, int bake, int boil, int steam, int fry, int knife)
        : stirfry(stirfry), bake(bake), boil(boil), steam(steam), fry(fry),
          knife(knife) {}
    void multiply(double a) {
        this->stirfry = int(this->stirfry * a);
        this->bake = int(this->bake * a);
        this->boil = int(this->boil * a);
        this->steam = int(this->steam * a);
        this->fry = int(this->fry * a);
        this->knife = int(this->knife * a);
    }
    void add(const Ability &a) {
        this->stirfry += a.stirfry;
        this->bake += a.bake;
        this->boil += a.boil;
        this->steam += a.steam;
        this->fry += a.fry;
        this->knife += a.knife;
    }
    void add(int a) {
        this->stirfry += a;
        this->bake += a;
        this->boil += a;
        this->steam += a;
        this->fry += a;
        this->knife += a;
    }
    void print(std::string title, std::string end = "\n",
               bool percent = false) {
        auto perstr = percent ? "%" : "";
        std::cout
            << title
            << (this->stirfry
                    ? "炒" + std::to_string(this->stirfry) + perstr + " "
                    : "")
            << (this->bake ? "烤" + std::to_string(this->bake) + perstr + " "
                           : "")
            << (this->boil ? "煮" + std::to_string(this->boil) + perstr + " "
                           : "")
            << (this->steam ? "蒸" + std::to_string(this->steam) + perstr + " "
                            : "")
            << (this->fry ? "炸" + std::to_string(this->fry) + perstr + " "
                          : "")
            << (this->knife ? "切" + std::to_string(this->knife) + perstr + " "
                            : "");
        if (!(this->stirfry || this->bake || this->boil || this->steam ||
              this->fry || this->knife))
            std::cout << "无";
        std::cout << end;
    }
};

class AbilityBuff : public Ability {
  public:
    int basic = 0;
    AbilityBuff() {}
    AbilityBuff(int stirfry, int bake, int boil, int steam, int fry, int knife)
        : Ability(stirfry, bake, boil, steam, fry, knife) {}
    void print() {
        this->Ability::print("AbilityBuff: ", "", true);
        std::cout << " Basic: " << this->basic << std::endl;
    }
    void add(const AbilityBuff &a) {
        this->Ability::add(a);
        this->basic += a.basic;
    }
    void add(const Ability &a) { this->Ability::add(a); }
    void add(int a){ this->Ability::add(a); }
};
class CookAbility : public Ability { 
  public:
    Ability percent = Ability();
    CookAbility(int stirfry, int bake, int boil, int steam, int fry, int knife)
        : Ability(stirfry, bake, boil, steam, fry, knife) {}
    CookAbility() : Ability() {}
    CookAbility(Json::Value &v);
    int operator/(const Ability &a);
    void print() {
        this->Ability::print("CookAbility: ");
        this->percent.print("CookAbilityPercent: ");
    }
    void add(const CookAbility &a) {
        this->Ability::add(a);
        this->percent.add(a.percent);
    }
    void add(const Ability &a) { this->Ability::add(a); }
    void add(int a) { this->Ability::add(a); }
    int operator*(const AbilityBuff &a);
    void handle_percent() {
        if (this->percent.stirfry)
            this->stirfry = int(ceil(this->stirfry * (this->percent.stirfry + 100) / 100.0));
        if (this->percent.bake)
            this->bake = int(ceil(this->bake * (this->percent.bake + 100) / 100.0));
        if (this->percent.boil)
            this->boil = int(ceil(this->boil * (this->percent.boil + 100) / 100.0));
        if (this->percent.steam)
            this->steam = int(ceil(this->steam * (this->percent.steam + 100) / 100.0));
        if (this->percent.fry)
            this->fry = int(ceil(this->fry * (this->percent.fry + 100) / 100.0));
        if (this->percent.knife)
            this->knife = int(ceil(this->knife * (this->percent.knife + 100) / 100.0));
    }
};
class StrangeBuff {
  public:
    DishBuff ExcessCookbookNum;
    DishBuff FewerCookbookNum;
    DishBuff Rank;

    StrangeBuff() {
        this->ExcessCookbookNum.dishNum = -1;
        this->FewerCookbookNum.dishNum = -1;
        this->Rank.dishNum = -1;
    }
    void add(const StrangeBuff &s) {
        if (~s.ExcessCookbookNum.dishNum) {
            if (~this->ExcessCookbookNum.dishNum) {
                //不许不else,很难想象不else会发生什么
                this->ExcessCookbookNum.dishBuff += s.ExcessCookbookNum.dishBuff;
            } else {
                this->ExcessCookbookNum.dishNum = s.ExcessCookbookNum.dishNum;
                this->ExcessCookbookNum.dishBuff = s.ExcessCookbookNum.dishBuff;
            }
        } 
        if (~s.FewerCookbookNum.dishNum) {
            if (~this->FewerCookbookNum.dishNum) {
                //不许不else,很难想象不else会发生什么
                this->FewerCookbookNum.dishBuff += s.FewerCookbookNum.dishBuff;
            } else {
                this->FewerCookbookNum.dishNum = s.FewerCookbookNum.dishNum;
                this->FewerCookbookNum.dishBuff = s.FewerCookbookNum.dishBuff;
            }
        }
        if (~s.Rank.dishNum) {
            if (~this->Rank.dishNum) {
                //不许不else,很难想象不else会发生什么
                this->Rank.dishBuff += s.Rank.dishBuff;
            } else {
                this->Rank.dishNum = s.Rank.dishNum;
                this->Rank.dishBuff = s.Rank.dishBuff;
            }
        }
    }
    void print() {
        if (~this->ExcessCookbookNum.dishNum)
            std::cout << "ExcessCookbookNum: " << this->ExcessCookbookNum.dishNum 
                    << "(" << this->ExcessCookbookNum.dishBuff << ")" << std::endl;
        if (~this->FewerCookbookNum.dishNum)
            std::cout << "FewerCookbookNum: " << this->FewerCookbookNum.dishNum 
                    << "(" << this->FewerCookbookNum.dishBuff << ")" << std::endl;
        if (~this->Rank.dishNum)
            std::cout << "Rank: " << this->Rank.dishNum 
                    << "(" << this->Rank.dishBuff << ")" << std::endl;
    }
};
class Halo{
  public:
    bool enable_skill;
    Ability skill;
    bool enable_skillNext;
    Ability skillNext;
    bool enable_buff;
    AbilityBuff buff;
    bool enable_buffNext;
    AbilityBuff buffNext;
    Halo() {
        this->enable_skill = false;
        this->skill = Ability();
        this->enable_skillNext = false;
        this->skillNext = Ability();
        this->enable_buff = false;
        this->buff = AbilityBuff();
        this->enable_buffNext = false;
        this->buffNext = AbilityBuff();
    }
    void print() {
        if (this->enable_skill)
            this->skill.print("SkillHalo: ");
        if (this->enable_skillNext)
            this->skillNext.print("SkillHaloNext: ");
        if (this->enable_buff) {
            std::cout << "BuffHalo: ";
            this->buff.print();            
        }
        if (this->enable_buffNext) {
            std::cout << "BuffHaloNext: ";
            this->buffNext.print();            
        }
    }
    void add(const Halo &a) {
        if (a.enable_skill) {
            this->enable_skill = true;
            this->skill.add(a.skill);
        }
        if (a.enable_skillNext) {
            this->enable_skillNext = true;
            this->skillNext.add(a.skillNext);
        }
        if (a.enable_buff) {
            this->enable_buff = true;
            this->buff.add(a.buff);
        }
        if (a.enable_buffNext) {
            this->enable_buffNext = true;
            this->buffNext.add(a.buffNext);
        }
    }
};
class ConditionalSkill {
  public:
    bool enable = false;
    std::string type;
    int value = 0;
    std::string condition;
    std::string conditionType;
    int conditionValue;
    void add(const ConditionalSkill &a) {
        if (a.enable) {
            this->enable = true;
            this->type = a.type;
            this->value = a.value;
            this->condition = a.condition;
            this->type = a.type;
            this->conditionValue = a.conditionValue;
        }
    }
    void print() {
        if (this->enable) std::cout << "Has conditonal skill" << std::endl;
    }
};
class Skill {
  private:
  public:
    static std::map<int, Skill> skillList;
    CookAbility ability;
    AbilityBuff abilityBuff;
    FlavorBuff flavorBuff;
    RarityBuff rarityBuff;
    MaterialCategoryBuff materialBuff;
    StrangeBuff strangeBuff;
    ConditionalSkill conditionalSkill;
    Halo halo;
    int coinBuff;
    Skill(CookAbility ability, AbilityBuff abilityBuff, FlavorBuff flavorBuff, RarityBuff rarityBuff, 
          MaterialCategoryBuff materialBuff, StrangeBuff strangeBuff,int coinBuff)
        : ability(ability), abilityBuff(abilityBuff), flavorBuff(flavorBuff), rarityBuff(rarityBuff),
          materialBuff(materialBuff), strangeBuff(strangeBuff), coinBuff(coinBuff){}
    Skill() {
        this->ability = CookAbility();
        this->abilityBuff = AbilityBuff();
        this->flavorBuff = FlavorBuff();
        this->rarityBuff = RarityBuff();
        this->materialBuff = MaterialCategoryBuff();
        this->strangeBuff = StrangeBuff();
        this->conditionalSkill = ConditionalSkill();
        this->halo = Halo();
        this->coinBuff = 0;
    }
    Skill getSkill(int id) { return skillList[id]; }
    static void loadJson(Json::Value &v);
    void add(const Skill &s) {
        this->ability.add(s.ability);
        this->abilityBuff.add(s.abilityBuff);
        this->flavorBuff.add(s.flavorBuff);
        this->rarityBuff.add(s.rarityBuff);
        this->materialBuff.add(s.materialBuff);
        this->strangeBuff.add(s.strangeBuff);
        this->conditionalSkill.add(s.conditionalSkill);
        this->halo.add(s.halo);
        this->coinBuff += s.coinBuff;
    }
    void print() {
        this->ability.print();
        this->abilityBuff.print();
        this->flavorBuff.print();
        this->rarityBuff.print();
        this->materialBuff.print();
        this->strangeBuff.print();
        this->halo.print();
        std::cout << "CoinBuff: " << this->coinBuff << std::endl;
        this->conditionalSkill.print();
    }
};
enum ToolEnum {
    NO_TOOL = -2,
    NOT_EQUIPPED = -1,
    STIRFRY,
    BAKE,
    BOIL,
    STEAM,
    FRY,
    KNIFE
};
enum FlavorEnum { UNIDENTIFIED = -1, SWEET, SALTY, SOUR, BITTER, SPICY, TASTY };
enum ToolFileType {
    NO_FILE__NO_TOOL,
    EMPTY_FILE__NOT_EQUIPPED,
    CUSTOMIZE_TOOL
};
#endif