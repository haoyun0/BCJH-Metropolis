#ifndef LOADTOOLEQUIPPED_HPP
#define LOADTOOLEQUIPPED_HPP
#include "src/Chef.hpp"
#include "src/Values.hpp"
#include <fstream>
#include <vector>
#include <exception>
// #include <Windows.h>
using namespace std;
struct ToolInfo {
    string name;
    CookAbility ability;
    AbilityBuff abilityBuff;
    FlavorBuff flavorBuff;
    MaterialCategoryBuff materialBuff;
};
typedef vector<string> ToolInfoRow;
struct ToolInfoBlock {
    vector<ToolInfoRow> info;
    int row;
};
typedef vector<ToolInfoBlock> ToolInfoFile;
typedef vector<ToolInfo> Tools;
ToolInfoBlock *tibptr;

ToolFileType loadToolFile() {

    auto fname = "toolEquipped.csv";
    ifstream toolFile(fname, ios::in);

    if (!toolFile.good()) {
        // print current path
        // char buf[256];

        // ...
        // char buf[MAX_PATH];
        // GetCurrentDirectory(MAX_PATH, buf);
        // cout << "当前路径：" << buf << endl;

        auto fname = "..\\data\\toolEquipped.csv";
        ifstream toolFile(fname, ios::in);
        if (!toolFile.good())
            tibptr = NULL;

        return NO_FILE__NO_TOOL;
    }
    string line;
    ToolInfoFile tif;
    ToolInfoBlock tib;
    tib.row = 2;
    ToolInfoRow tir;

    string word;
    getline(toolFile, line);
    istringstream sin;
    int lineNum = 1;
    while (getline(toolFile, line)) {
        lineNum++;
        sin.clear();
        sin.str(line);
        getline(sin, word, ',');
        if (word == "") {
            tif.push_back(tib);
            tib.info.clear();
            tib.row = lineNum + 1;
            continue;
        }
        tir.push_back(word);
        while (getline(sin, word, ',')) {
            tir.push_back(word);
        }
        tib.info.push_back(tir);
        tir.clear();
    }
    if (tib.info.size() != 0)
        tif.push_back(tib);
    toolFile.close();
    if (tif.size() == 0) {
        tibptr = NULL;
        return EMPTY_FILE__NOT_EQUIPPED;
    }
    if (tif.size() == 1) {
        tibptr = new ToolInfoBlock(tif[0]);
        return CUSTOMIZE_TOOL;
    }
    if (tif.size() > 1) {
        cout << "发现多个配置，请输入希望使用的配置编号。" << endl;
        for (int i = 0; i < tif.size(); i++) {
            cout << i << ": ";
            for (int j = 0; j < tif[i].info.size(); j++) {
                cout << tif[i].info[j][0] << " ";
            }
            cout << endl;
        }
        cout << "请输入0到" << tif.size() - 1 << "之间的整数：";
        int i = -1;
        cin >> i;

        if (!(i >= 0 && i < tif.size())) {
            cout << "输入的不是0到" << tif.size() - 1 << "之间的整数。" << endl;
            exit(1);
        }
        tibptr = new ToolInfoBlock(tif[i]);

        return CUSTOMIZE_TOOL;
    }
}

bool isFloatOrInt(string s) {
    bool hasDot = false;
    if (s.size() == 0)
        return true;
    if (s[0] != '-' && !(s[0] >= '0' && s[0] <= '9'))
        return false;
    for (int i = 1; i < s.size(); i++) {
        if (s[i] == '.') {
            if (hasDot)
                return false;
            else
                hasDot = true;
            continue;
        }
        if (s[i] < '0' || s[i] > '9')
            return false;
    }
    return true;
}
double str2f(string s) {
    if (isFloatOrInt(s))
        return atof(s.c_str());
    else
        throw runtime_error("无法将字符串转换为浮点数。");
}

void loadToolFromFile(Chef *chef, ToolFileType t) {
    if (t == EMPTY_FILE__NOT_EQUIPPED) {
        return;
    }
    if (t == NO_FILE__NO_TOOL) {
        chef->NoTool();
        return;
    }

    auto lineN = tibptr->row - 1;
    auto tools = (*tibptr).info;
    for (int i = 0; i < tools.size(); i++) {
        lineN = lineN + 1;
        auto tool = tools[i];
        if (!(tool[0] == chef->name)) {
            continue;
        }
        chef->NoTool();
        int j = 1;
        auto skill = &chef->skill;
        auto ability = &skill->ability;
        auto abilityBuff = &skill->abilityBuff;
        auto flavorBuff = &skill->flavorBuff;
        auto materialBuff = &skill->materialBuff;
        try {
            ability->add(str2f(tool[j++]));
            if (tool[j][0] == '*') {
                ability->bake *= str2f(tool[j++].substr(1));
            } else {
                ability->bake += str2f(tool[j++]);
            }
            if (tool[j][0] == '*') {
                ability->knife *= str2f(tool[j++].substr(1));
            } else {
                ability->knife += str2f(tool[j++]);
            }
            if (tool[j][0] == '*') {
                ability->stirfry *= str2f(tool[j++].substr(1));
            } else {
                ability->stirfry += str2f(tool[j++]);
            }
            if (tool[j][0] == '*') {
                ability->fry *= str2f(tool[j++].substr(1));
            } else {
                ability->fry += str2f(tool[j++]);
            }
            if (tool[j][0] == '*') {
                ability->steam *= str2f(tool[j++].substr(1));
            } else {
                ability->steam += str2f(tool[j++]);
            }
            if (tool[j][0] == '*') {
                ability->boil *= str2f(tool[j++].substr(1));
            } else {
                ability->boil += str2f(tool[j++]);
            }
            skill->coinBuff += str2f(tool[j++]);
            abilityBuff->bake += str2f(tool[j++]);
            abilityBuff->knife += str2f(tool[j++]);
            abilityBuff->stirfry += str2f(tool[j++]);
            abilityBuff->fry += str2f(tool[j++]);
            abilityBuff->steam += str2f(tool[j++]);
            abilityBuff->boil += str2f(tool[j++]);
            flavorBuff->sweet += str2f(tool[j++]);
            flavorBuff->spicy += str2f(tool[j++]);
            flavorBuff->salty += str2f(tool[j++]);
            flavorBuff->tasty += str2f(tool[j++]);
            flavorBuff->sour += str2f(tool[j++]);
            flavorBuff->bitter += str2f(tool[j++]);
        } catch (...) {
            j -= 1;
            cout << "厨具配置文件第" << lineN << "行第" << j + 1
                 << "列出现无法识别的内容" << tool[j] << "。" << endl;
            exit(0);
        }
    }
}

#endif