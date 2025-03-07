#include "../include/file.h"

extern vector<Village> villageList; // 村庄列表
extern vector<Road> roadList; // 道路列表
extern int graph[405][405]; // 村庄间道路矩阵
extern unordered_map<string, int> id2cnt; // 村庄ID到编号的映射

void restore() {
    cout << "恢复数据中..." << endl;
    ifstream inFile("data.txt"); // 路径应该从Makefile所在目录开始
    if (inFile.is_open()) {
        //数据恢复
        string id, name, brief, start, end;
        int x, y, length, n;
        inFile >> n;
        for (int i = 0; i < n; i++) {
            inFile >> id >> name >> brief >> x >> y;
            id2cnt[id] = i; // 恢复id到存储下标的映射
            villageList.push_back(Village(id, name, brief, x, y)); // 放入村庄列表
        }
        inFile >> n;
        for (int i = 0; i < n; i++) {
            inFile >> start >> end >> length;
            int startCnt = id2cnt[start], endCnt = id2cnt[end];
            graph[startCnt][endCnt] = graph[endCnt][startCnt] = i+1; // 村庄间道路矩阵置1
            roadList.push_back(Road(start, end, length)); // 放入道路列表
        }
        inFile.close();   
        cout << "数据恢复成功！"<<endl;
    } else {
        cerr << "数据文件不存在"<<endl;
    }
}

void save() {
    cout << "数据保存中..." << endl;
    ofstream outFile("data.txt");
    if (outFile.is_open()) {
        //数据保存
        // 保存村庄信息
        int n = villageList.size();
        //cout << "村庄数量：" << n << endl;
        outFile << n << endl;
        for (int i = 0; i < n; i++) {
            //cout << villageList[i].id << " " << villageList[i].name << " " << villageList[i].brief << " " << villageList[i].x << " " << villageList[i].y << endl;
            outFile << villageList[i].id << " " << villageList[i].name << " " << villageList[i].brief << " " << villageList[i].x << " " << villageList[i].y << endl;
        }
        // // 保存村庄ID到存储下标的映射
        // for (auto it = id2cnt.begin(); it != id2cnt.end(); it++) {
        //     outFile << it->first << " " << it->second << endl;
        // }
        // 保存道路信息
        n = roadList.size();
        outFile << n << endl;
        for (int i = 0; i < n; i++) {
            outFile << roadList[i].start << " " << roadList[i].end << " " << roadList[i].length << endl;
        }
        outFile.close();
        cout << "数据保存成功！"<<endl;
    } else {
        cerr << "数据文件打开失败"<<endl;
    }
}