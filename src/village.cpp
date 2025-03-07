#include "../include/village.h"
#include "../include/road.h"

extern vector<Village> villageList; // 村庄列表
extern vector<Road> roadList; // 道路列表
extern int graph[405][405]; // 村庄间道路矩阵
extern unordered_map<string, int> id2cnt; // 村庄ID到编号的映射

void addVillage() {
    cout << "请输入你要添加的村庄的数量" << endl;
    string id, name, brief;
    int x, y, n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "请依次输入:村庄的编号，名称，简介，横纵坐标" << endl;
        cin >> id >> name >> brief >> x >> y;
        id2cnt[id] = villageList.size(); // 村庄ID到存储下标的映射
        villageList.push_back(Village(id, name, brief, x, y));
        cout << "添加成功！" << endl;
    }
}

// 删除村庄的信息，及与村庄相关的道路
void deleteVillage() {
    cout << "请输入你要删除的村庄的数量" << endl;
    int n;
    cin >> n;
    string id;
    for (int i = 0; i < n; i++) {
        cout << "请输入你要删除的村庄的编号" << endl;
        cin >> id;
        int cnt = id2cnt[id], villages = villageList.size();
        for (int i = 0; i < villages; i++) {
            // 如果存在与其它村庄的道路，则删除
            if (graph[cnt][i]) {
                int roadCnt = graph[cnt][i] - 1;
                roadList.erase(roadList.begin() + roadCnt); // 删除道路信息
                graph[cnt][i] = graph[i][cnt] = 0; // 村庄间道路矩阵置0
            }
            if (i > cnt) {
                id2cnt[villageList[i].id]--; // 更新下标映射
            }
        }
        villageList.erase(villageList.begin() + cnt); // 删除村庄信息
        id2cnt.erase(id); // 删除村庄ID到编号的映射
        cout << "删除成功！" << endl;
    }
}
// 修改村庄信息
void modifyVillage() {
    cout << "请输入你要修改的村庄的数量" << endl;
    int n;
    cin >> n;
    string id, name, brief;
    int x, y;
    for (int i = 0; i < n; i++) {
        cout << "请输入你要修改的村庄的编号" << endl;
        cin >> id;
        int cnt = id2cnt[id];
        cout << villageList[cnt].id << " " << villageList[cnt].name << endl;
        cout << villageList[cnt].brief <<endl;
        cout << villageList[cnt].x << " " << villageList[cnt].y << endl;
        id2cnt.erase(id); // 删除村庄ID到下标的映射
        cout << "这是当前信息，请依次输入修改后的:村庄的编号，名称，简介，横纵坐标" << endl;
        cin >> id >> name >> brief >> x >> y;
        villageList[cnt].id = id;
        villageList[cnt].name = name;
        villageList[cnt].brief = brief;
        villageList[cnt].x = x;
        villageList[cnt].y = y;
        id2cnt[id] = cnt; // 更新村庄ID到下标的映射
        cout << "村庄信息修改成功！,这是修改后的信息" << endl;
        cout << villageList[cnt].id << " " << villageList[cnt].name << endl;
        cout << villageList[cnt].brief <<endl;
        cout << villageList[cnt].x << " " << villageList[cnt].y << endl;
    }
}