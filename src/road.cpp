#include "../include/road.h"

extern vector<Village> villageList; // 村庄列表
extern vector<Road> roadList; // 道路列表
extern int graph[405][405]; // 村庄间道路矩阵
extern unordered_map<string, int> id2cnt; // 村庄ID到编号的映射

int getLen(int start, int end) {
    int x1 = villageList[start].x, y1 = villageList[start].y;
    int x2 = villageList[end].x, y2 = villageList[end].y;
    return round(sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
}

// 添加道路
void addRoad() {
    cout << "请输入你要添加的道路的数量" << endl;
    string start, end;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "请输入你要添加的道路的起点村庄编号和终点村庄编号" << endl;
        cin >> start >> end;
        int startCnt = id2cnt[start], endCnt = id2cnt[end];
        int len = getLen(startCnt, endCnt);
        roadList.push_back(Road(start, end, len));
        graph[startCnt][endCnt] = graph[endCnt][startCnt] = roadList.size(); // 村庄间道路矩阵更新
        cout << "添加成功！" << endl;
    }
}

// 删除道路
void deleteRoad() {
    cout << "请输入你要删除的道路的数量" << endl;
    int n;
    cin >> n;
    string start, end;
    for (int i = 0; i < n; i++) {
        cout << "请输入你要删除的道路的起点村庄编号和终点村庄编号" << endl;
        cin >> start >> end;
        int startCnt = id2cnt[start], endCnt = id2cnt[end];
        int roadCnt = graph[startCnt][endCnt] - 1;
        roadList.erase(roadList.begin() + roadCnt); // 删除道路信息
        graph[startCnt][endCnt] = graph[endCnt][startCnt] = 0; // 村庄间道路矩阵置0
        cout << "删除成功！" << endl;
    }
}

// 修改道路
void modifyRoad() {
    cout << "请输入你要修改的道路的数量" << endl;
    int n;
    cin >> n;
    string start, end;
    //int len;
    for (int i = 0; i < n; i++) {
        cout << "请输入你要修改的道路的起点村庄编号和终点村庄编号" << endl;
        cin >> start >> end;
        int startCnt = id2cnt[start], endCnt = id2cnt[end];
        int roadCnt = graph[startCnt][endCnt] - 1;
        //cout << roadList[roadCnt].start << " " << roadList[roadCnt].end << endl;
        graph[startCnt][endCnt] = graph[endCnt][startCnt] = 0; // 村庄间道路矩阵置0
        cout << "请依次输入修改后的:道路的起点村庄编号，终点村庄编号" << endl;
        cin >> start >> end;
        roadList[roadCnt].start = start;
        roadList[roadCnt].end = end;
        startCnt = id2cnt[start], endCnt = id2cnt[end];
        roadList[roadCnt].length = getLen(startCnt, endCnt);
        graph[startCnt][endCnt] = graph[endCnt][startCnt] = roadCnt + 1; // 村庄间道路矩阵更新
    }
}
