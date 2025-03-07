#include <iostream>
#include "../include/file.h"
#include "../include/road.h"
#include "../include/village.h"
#include "../include/graph.h"
using namespace std;

vector<Village> villageList; // 村庄列表
vector<Road> roadList; // 道路列表
int graph[405][405]; // 村庄间道路矩阵
unordered_map<string, int> id2cnt; // 村庄ID到编号的映射

int menu() {
    cout << "请输入选择标号：" << endl;
    cout << "1.----添加村庄的信息----"<<endl;
    cout << "2.----删除村庄的信息----"<<endl;
    cout << "3.----修改村庄的信息----"<<endl;
    cout << "4.----添加道路的信息----"<<endl;
    cout << "5.----删除道路的信息----"<<endl;
    cout << "6.----修改道路的信息----"<<endl;
    cout << "7.----生成村村通方案----"<<endl;
    cout << "8.----查询到其它村庄的最短路线----"<<endl;
    cout << "9.----查询经过所有村庄的最短路线----"<<endl;
    cout << "10.---查询经过所有村庄并回到起点的最短路线----"<<endl;
    cout << "11.-----退出程序----"<<endl;
    int select;
    cin >> select;
    return select;
}

int main() {
    cout << "欢迎使用村庄间道路管理系统！！！" << endl;
    restore();
    while (true) {
        int select = menu();
        switch (select) {
        case 1:
            addVillage();
            break;
        case 2:
            deleteVillage();
            break;
        case 3:
            modifyVillage();
            break;
        case 4:
            addRoad();
            break;
        case 5:
            deleteRoad();
            break;
        case 6:
            modifyRoad();
            break;
        case 7:
            connectAndFind();
            break;
        case 8:
            findShortestPath();
            break;
        case 9:
            break;
        case 10:
            break;
        case 11:
            save();
            return 0;
        default:
            cout << "输入错误，请重新输入！" << endl;
            break;
        }
    }
}