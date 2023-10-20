#include<iostream>
#include<fstream>
#include<windows.h>
#include "globalConfig.hpp"
#include "include/simpleini/SimpleIni.h"
#include "include/json/json.h"
#include "utils/json.hpp"
#include "interface.hpp"

using std::stoi;
using std::cout;
using std::endl;
using std::cin;

CSimpleIniA ini;// 加载ini文件

bool GUIDE;
bool BCJH;
bool MP;

int NUM_GUESTS;
int NUM_CHEFS;
int guestList[MAX_GUESTS];

int ITER_CHEF;
int ITER_RECIPE;
int TARGET_SCORE_APPROXIMATE;
bool AVOID_CHEF_1;
bool AVOID_CHEF_2;
bool AVOID_CHEF_3;
bool AVOID_CHEF_4;
bool AVOID_CHEF_5;
int T_MAX_CHEF;
int T_MAX_RECIPE;

void readINI();
void Lincece();
void interact();
void examine_iter();
void concat(char*, const char*);

void MainActivity() {
    readINI();
    Lincece();
    if (GUIDE) interact();
    if (NUM_GUESTS < 1 || NUM_GUESTS > 11)
        throw "NUM_GUEST Error";
    NUM_CHEFS = NUM_GUESTS * CHEFS_PER_GUEST;
    examine_iter();
    return;
}

void interact(){
    if (BCJH){
        char op[100];
        cout << "白菜菊花云端数据id(使用本地数据请直接回车): ";
        char id[10]={0};
        cin.getline(id, 9);
        if (id[0] < '0' || id[0] > '9') {
            cout << "你选择使用本地数据" << endl;
            return;
        }

        char command[64] = "cd ../data&&bcjhDownload.exe ";
        concat(command, id);
        
        int status = system(command);
        // cout << endl << "ret " << status % 256 << endl << "ret " << status / 256 << endl;
        if (status == 1)
            throw "找不到bcjhDownload.exe，请确认data文件下有这个下载程序且没有被杀毒软件杀掉";

        Json::Value tmpData;
        std::ifstream tmpDataF("../data/tmp.txt", std::ifstream::binary);
        tmpDataF >> tmpData;
        tmpDataF.close();
        // cout << "临时数据下载成功" << endl;
        if (tmpData["result"].asBool())
            cout << "数据下载成功" << endl;
        else
            cout << "数据不存在或已过期" << endl;

        Json::Reader reader;
        Json::Value data;
        if (!reader.parse(tmpData["data"].asCString(), data)) return;

        Json::FastWriter writerinfo;
        std::string userdata = writerinfo.write(data);
        std::ofstream userDataF("../data/userData.txt");
        userDataF << userdata;
        userDataF.close();
        system("del \"../data/tmp.txt\"");
    }
}

void Lincece() {
    cout << "风云宴全自动计算器，桌面版" << endl;
    cout << "\t桌面版作者:威严扫地机" << endl;
    cout << "\t原项目核心算法作者:ajdx" << endl;
    cout << "\t特别致谢:萤火" << endl;
    cout << "桌面版交流群：二群：241168853" << endl;
    cout << endl;
}

void examine_iter() {
    if (MP) return;
    if (ITER_CHEF < 5000 || ITER_RECIPE < 10000) {
        cout << "检测到迭代次数过少!!!" << endl;
        cout << "请阅读目录下的说明文档更改迭代数!!!" << endl;
        cout << "否则跑分效果极差，不要说你用过我的计算器!!!" << endl;
        MessageBoxA(GetForegroundWindow(),
        "检测到迭代次数过少!!!\n"
        "请阅读目录下的说明文档更改迭代数!!!\n"
        "否则跑分效果极差，不要说你用过我的计算器",
        "警告", 1);
    }
}

void concat(char* s, const char* t) {
    int i = 0;
    while (s[i]) i++;
    int j = 0;
    while (t[j]) {
        s[i + j] = t[j];
        j++;
    }
    s[i + j] = 0;
}

inline bool stobool(const char* s){
    if (s[0] == 'T' or s[0] == 't') return true;
    return false;
}

void stoarray(const char*s, int* a){
    int cnt = 0, k = 0;
    bool flag = false;
    for (int i = 0; s[i]; i++)
        if ('0' <= s[i] && s[i] <= '9'){
            if (!flag){
                flag = true;
                k = 0;
            }
            k = k * 10 + int(s[i]) - 48;
        }else{
            if (flag){
                a[cnt] = k;
                cnt++;
                flag = false;
            }
        }
    if (flag) a[cnt] = k;
    return;
}

void readINI(){
    SI_Error rc;
    rc = ini.LoadFile("../data/config.ini");	// 另一种方式：SI_Error LoadFile(FILE * a_fpFile);
    if (rc < 0)  cout << "加载 config.ini 文件失败！" << endl;

    ini.SetUnicode(false);
    ini.SetMultiKey(false);

    //[tools]
    GUIDE = stobool(ini.GetValue("tools", "GUIDE", "true"));
    BCJH = stobool(ini.GetValue("tools", "BCJH", "true"));
    MP = stobool(ini.GetValue("tools", "MP", "false"));

    //[guestConfig]
    NUM_GUESTS = stoi(ini.GetValue("guestConfig", "NUM_GUESTS", "1"));
    stoarray(ini.GetValue("guestConfig", "guestList", "1"), guestList);

    //[calculator]
    ITER_CHEF = stoi(ini.GetValue("calculator", "ITER_CHEF", "10000"));
    ITER_RECIPE = stoi(ini.GetValue("calculator", "ITER_RECIPE", "10000"));
    TARGET_SCORE_APPROXIMATE = stoi(ini.GetValue("calculator", "TARGET_SCORE_APPROXIMATE", "2000000"));

    AVOID_CHEF_1 = stobool(ini.GetValue("calculator", "AVOID_CHEF_1", "true"));
    AVOID_CHEF_2 = stobool(ini.GetValue("calculator", "AVOID_CHEF_2", "true"));
    AVOID_CHEF_3 = stobool(ini.GetValue("calculator", "AVOID_CHEF_3", "true"));
    AVOID_CHEF_4 = stobool(ini.GetValue("calculator", "AVOID_CHEF_4", "false"));
    AVOID_CHEF_5 = stobool(ini.GetValue("calculator", "AVOID_CHEF_5", "false"));

    T_MAX_CHEF = stoi(ini.GetValue("calculator", "T_MAX_CHEF", "50"));
    T_MAX_CHEF = TARGET_SCORE_APPROXIMATE / T_MAX_CHEF;
    T_MAX_RECIPE = stoi(ini.GetValue("calculator", "T_MAX_RECIPE", "50"));
    T_MAX_RECIPE = TARGET_SCORE_APPROXIMATE / T_MAX_RECIPE;
}