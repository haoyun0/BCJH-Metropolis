#include <iostream>
#include <string>
#include "Chef.hpp"
#include "Recipe.hpp"
#include <map>
#include "Calculator.hpp"
#include <vector>
#include "SARunner.hpp"
#include "functions.hpp"
#include "globalConfig.hpp"
#include "interface.hpp"
#include <stdio.h>
#include <fstream>
#include <time.h>
#include "exception.hpp"
#include <future>
#include <vector>
bool Chef::coinBuffOn = true;
void initChefRecipePairs(CList &, RList &);
struct Result {
    int score;
    int seed;
    CList *chefList;
    RList recipeList;
    States *state;
};
Result run(const CList &, RList &, int, bool, int);
void calculator(CList &, RList &);
void condition_handle(States &);
void add_halo(States &);
void parseArgs(int argc, char *argv[], bool &silent, int &log, bool &calculate,
               bool &mp, int &seed);
int main(int argc, char *argv[]) {
    bool silent = false;
    int log = 0; // 0x0: 无输出 0x1: 正常输出 0x10: 详细输出
    int seed = (int)time(NULL);
    bool calculate = false;
    bool mp = true;
    try {
        MainActivity();
        mp = MP;
    } catch(const char *s) {
        std::cout << s << std::endl; 
        exit(1);
    }
    parseArgs(argc, argv, silent, log, calculate, mp, seed);

    CList chefList;
    RList recipeList;
    try {
        std::cout << "正在读取文件..." << std::endl;
        loadChef(chefList);
        loadRecipe(recipeList);
        std::cout << "读取文件结束。" << std::endl;
    } catch (FileNotExistException &e) {
        std::cout << "json文件缺失。如果在网页端，请确认已经上传了文件；如果在"
                     "本地，请确认已经下载了文件。\n";
        exit(1);
    } catch (Json::RuntimeError &e) {
        std::cout << "json文件格式不正确。如果文件内容是手动复制的，确认文件已"
                     "经复制完整。\n";
        exit(1);
    } catch (Json::LogicError &e) {
        std::cout << "json文件格式不正确。请确认文件来自白菜菊花而非图鉴网。\n";
        exit(1);
    } 

    for (auto chef = chefList.begin(); chef != chefList.end(); chef++) {
        chef->loadRecipeCapable(recipeList);
    }
    // Count time used
    clock_t start, end;
    start = clock();

    if (!calculate) {
        Result result;

        int num_threads = std::thread::hardware_concurrency();
        if (!mp) {
            num_threads = 1;
        }
        seed *= num_threads;
        if (num_threads > 1) {
            std::cout << "启用" << num_threads
                    << "线程，建议期间不要离开窗口，否则可能影响速度。"
                    << std::endl;
        }

        std::vector<std::future<Result>> futures;

        for (int i = 0; i < num_threads; i++) {

            futures.push_back(
                std::async(std::launch::async, run, std::ref(chefList),
                           std::ref(recipeList), 0, silent, seed++));
            silent = true;
        }
        std::cout << "分数：";
        int max_score = 0;
        for (auto &future : futures) {
            Result tmp = future.get();
            if (tmp.score > max_score) {
                result = tmp;
                max_score = result.score;

            } else {
                delete tmp.chefList;
                delete tmp.state;
            }
            std::cout << tmp.score << " ";
        }
        std::cout << "\n最佳结果：" << std::endl;

        log += 0x1;
        std::cout << "随机种子：" << result.seed << std::endl;
        int score = e0::sumPrice(*result.state, result.chefList,
                                 &result.recipeList, log, true);
        std::cout << "**************\n总分: " << result.score
                  << "\n***************" << std::endl;
        if (!silent) {
            SARunner saRunnerPrint(
                result.chefList, &result.recipeList, ITER_RECIPE, T_MAX_RECIPE,
                0, e::getTotalPrice, r::randomRecipe, f::t_dist_fast);
            saRunnerPrint.run(result.state, false, silent, "../out/recipe");
        }
        delete result.chefList;
        delete result.state;
    } else {
        calculator(chefList, recipeList);
    }
    end = clock();
    std::cout << "用时：" << (double)(end - start) / CLOCKS_PER_SEC << "秒"
              << std::endl;
    system("pause");
}
Result run(const CList &chefList, RList &recipeList, int log, bool silent,
           int seed) {
    CList *chefListPtr = new CList(chefList);
    *chefListPtr = chefList;
    srand(seed);
    SARunner saRunner(chefListPtr, &recipeList, ITER_CHEF, T_MAX_CHEF,
                      0, e::getTotalPrice, r::randomChef,
                      f::t_dist_fast);
    // std::cout << log << std::endl;
    States *s = new States;
    *s = saRunner.run(NULL, true, silent);
    *s = perfectChef(*s, chefListPtr);
    condition_handle(*s);
    add_halo(*s);
    int score = e0::sumPrice(*s, chefListPtr, &recipeList, log, false);
    return Result{score, seed, chefListPtr, recipeList, s};
}
void parseArgs(int argc, char *argv[], bool &silent, int &log, bool &calculate,
               bool &mp, int &seed) {
    int seed_orig = seed;
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "-s") {
            silent = true;
        } else if (arg == "-v") {
            log += 0x10;
        } else if (arg == "-c") {
            calculate = true;
        } else if (arg == "-h") {
            std::cout << "-s: 无进度条" << std::endl;
            std::cout << "-v: 输出详细信息" << std::endl;
            std::cout << "-c: 从文件中读取配置，计算分数" << std::endl;
        } else if (arg == "--no-mp") {
            mp = false;
        } else if (arg == "--seed") {
            seed = atoi(argv[++i]);
        } else {
            std::cout << "未知参数：" << arg << std::endl;
            exit(1);
        }
        // set seed
    }
    if (seed_orig != seed) {
        if (mp) {
            mp = false;
            std::cout << "Seed set to " << seed << ", mp disabled" << std::endl;
        } else {
            std::cout << "Seed set to " << seed << std::endl;
        }
    }

    if (mp) {
        silent = true;
    }
}
void calculator(CList &chefList, RList &recipeList) {
    std::ifstream f;
    f.open("../in/out.txt");
    States s;
    for (int i = 0; i < NUM_CHEFS; i++) {
        int c, t;
        f >> c >> t;
        if (t == NO_TOOL) {
            t = 0;
        }
        s.chef[i] = &chefList[c * 6 + t];
        s.chef[i]->print();
    }
    for (int i = 0; i < NUM_CHEFS * DISH_PER_CHEF; i++) {
        int r;
        f >> r;
        s.recipe[i] = &recipeList[r];
    }
    f.close();
    int score = e0::sumPrice(s, &chefList, &recipeList, false, true);
    SARunner saRunner(&chefList, &recipeList, ITER_CHEF, T_MAX_CHEF, 0);
    saRunner.print(s, true);
    std::cout << "\n\nScore: " << score << std::endl;
}
//跟多个菜有关的技能，年糕，汤圆
void condition_handle(States &s) {
    for (int i = 0; i < NUM_CHEFS; i++) 
        if (s.chef[i]->skill.conditionalSkill.enable) {
            //暂时只考虑已有厨师
            ConditionalSkill *c = &s.chef[i]->skill.conditionalSkill;
            if (c->conditionType == "PerRank") {
                //每制作一种x级料理
                int tot = 0;
                for (int j = i * DISH_PER_CHEF; j < (i + 1) * DISH_PER_CHEF; j++)
                    if (s.chef[i]->skill.ability / s.recipe[j]->cookAbility >= c->conditionValue)
                        tot += c->value;
                if (c->type == "BasicPrice") {
                    s.chef[i]->skill.abilityBuff.basic += tot;
                } else
                if (c->type == "UseKnife")
                {
                    s.chef[i]->skill.halo.enable_buff = true;
                    s.chef[i]->skill.halo.buff.knife += tot;
                }
                
            } else
            if (c->conditionType == "SameSkill") {
                int j = i * DISH_PER_CHEF;
                int cnt = 0;
                if (s.recipe[j]->cookAbility.bake > 0 &&
                    s.recipe[j + 1]->cookAbility.bake > 0 &&
                    s.recipe[j + 2]->cookAbility.bake > 0)
                    cnt ++;
                if (s.recipe[j]->cookAbility.stirfry > 0 &&
                    s.recipe[j + 1]->cookAbility.stirfry > 0 &&
                    s.recipe[j + 2]->cookAbility.stirfry > 0)
                    cnt ++;
                if (s.recipe[j]->cookAbility.steam > 0 &&
                    s.recipe[j + 1]->cookAbility.steam > 0 &&
                    s.recipe[j + 2]->cookAbility.steam > 0)
                    cnt ++;
                if (s.recipe[j]->cookAbility.boil > 0 &&
                    s.recipe[j + 1]->cookAbility.boil > 0 &&
                    s.recipe[j + 2]->cookAbility.boil > 0)
                    cnt ++;
                if (s.recipe[j]->cookAbility.knife > 0 &&
                    s.recipe[j + 1]->cookAbility.knife > 0 &&
                    s.recipe[j + 2]->cookAbility.knife > 0)
                    cnt ++;
                if (s.recipe[j]->cookAbility.fry > 0 &&
                    s.recipe[j + 1]->cookAbility.fry > 0 &&
                    s.recipe[j + 2]->cookAbility.fry > 0)
                    cnt ++;
                if (cnt > 0) {
                    if (c->type == "UseFry") {
                        s.chef[i]->skill.halo.enable_buff = true;
                        s.chef[i]->skill.halo.buff.fry = cnt * c->value;
                    }else
                    if (c->type == "BasicPrice"){
                        s.chef[i]->skill.halo.enable_buff = true;
                        s.chef[i]->skill.halo.buff.basic = cnt * c->value;
                    }
                }
            }
        }
    
}
//光环处理，及乘法相关技法处理
void add_halo(States &s) {
    for (int g = 0; g < NUM_GUESTS; g++) {
        for (int i = g * CHEFS_PER_GUEST; i < CHEFS_PER_GUEST * (g + 1); i++) {
            if (s.chef[i]->skill.halo.enable_skill) {
                if (MODE == 1) {//宴会模式，光环只对后面的角色生效
                    for (int k = i; k < CHEFS_PER_GUEST * (g + 1); k++) {
                        s.chef[k]->skill.ability.add(s.chef[i]->skill.halo.skill);
                    }
                } else {
                    for (int k = g * 3; k < CHEFS_PER_GUEST * (g + 1); k++) {
                        s.chef[k]->skill.ability.add(s.chef[i]->skill.halo.skill);
                    }
                }
            }
            if (s.chef[i]->skill.halo.enable_buff) {
                if (MODE == 1) {//宴会模式，光环只对后面的角色生效
                    for (int k = i; k < CHEFS_PER_GUEST * (g + 1); k++) {
                        s.chef[k]->skill.abilityBuff.add(s.chef[i]->skill.halo.buff);
                    }
                } else {
                    for (int k = g * 3; k < CHEFS_PER_GUEST * (g + 1); k++) {
                        s.chef[k]->skill.abilityBuff.add(s.chef[i]->skill.halo.buff);
                    }
                }
            }
            if ((i + 1) % CHEFS_PER_GUEST && s.chef[i]->skill.halo.enable_skillNext) {
                s.chef[i + 1]->skill.ability.add(s.chef[i]->skill.halo.skillNext);
            }
            if ((i + 1) % CHEFS_PER_GUEST && s.chef[i]->skill.halo.enable_buffNext) {
                s.chef[i + 1]->skill.abilityBuff.add(s.chef[i]->skill.halo.buffNext);
            }
        }
    }
    //所有技法先加后乘
    for (int i = 0; i < NUM_CHEFS; i++) {
        s.chef[i]->skill.ability.handle_percent();
    }
}