#include "../include/graph.h"

extern vector<Village> villageList; // 村庄列表
extern vector<Road> roadList; // 道路列表
extern int graph[405][405]; // 村庄间道路矩阵
extern unordered_map<string, int> id2cnt; // 村庄ID到编号的映射

// 并查集查找父节点函数
int find(int x, vector<int>& fa) {
    if (fa[x] != x) fa[x] = find(fa[x], fa);
    return fa[x];
}
// 村村通算法
void kruskal(vector<Road>& ans, priority_queue<Road>& pq, vector<int>& fa,int cnt) {
    int limit = villageList.size() - 1;
    //cout << cnt << " " << limit << endl;
    // 因为一定在pq空之前完成选择，所以无需判断pq是否为空
    while (cnt < limit) {
        //cout << "正在选择边";
        Road top = pq.top();
        //cout << top.start << "-----" << top.end << ":" << top.length << endl;
        pq.pop();
        int start = id2cnt[top.start], end = id2cnt[top.end];
        int faStart = find(start, fa), faEnd = find(end, fa);
        // 如果边的两端的村庄不在同一个集合中，则选择该边
        if (faStart != faEnd) {
            //cout << "选择边了";
            ans.push_back(top);
            cnt++;
            fa[faStart] = faEnd; // 合并两个集合
        }
    }
}

// 判断当前村庄是否联通
bool isConnected(int& cnt, vector<int>& fa) {
    int n = roadList.size();
    //cout <<"22222" << endl;
    for (int i = 0; i < n; i++) {
        int start = id2cnt[roadList[i].start], end = id2cnt[roadList[i].end]; // 获取村庄下标
        //cout << start << " " << end << endl;
        int faStart = find(start, fa), faEnd = find(end, fa); // 找到两个村庄所在的集合编号
        // 如果不在一个集合
        if (faStart != faEnd) {
            fa[faStart] = faEnd; // 合并两个集合
            cnt++; // 更新关键边的数量
        }
    }
    if (cnt < fa.size()) return false;
    return true;
}

// 判断村庄是否连通，并给出一个总长度最小的村村通方案
// 1. 先将已有道路加入并查集中, 并判断已有道路是否保证村村通
// 2. 遍历从小到大遍历所有道路，如果道路两边的村庄不在同一个集合中
void connectAndFind() {
    cout << "正在判断是否联通..."<<endl;
    int n = villageList.size();
    vector<int> fa(n);
    for (int i = 0; i < n; i++) fa[i] = i;
    int cnt = 0;
    cout << "111111" << endl;
    if (isConnected(cnt, fa)) {
        cout << "当前村庄已联通，无需生成村村通方案" << endl;
        return;
    } else {
        cout << "当前村庄不联通，正在生成总长度最小的村村通方案" << endl;
    }
    // 开始生成村村通方案
    priority_queue<Road> pq; // 小根堆，按照道路长度排序
    // 1. 获取待选取的边
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] || find(i, fa) == find(j, fa)) continue; // 如果边存在，或者边两端的村庄已经在一个集合，则跳过
            int len = getLen(i, j);
            //cout << "有边加入" << endl;
            //cout << villageList[i].id << "-----" << villageList[j].id << ":" << len << endl;
            pq.push(Road(villageList[i].id, villageList[j].id, len)); // 放入待选取的边
        }
    }
    // 2. 村村通方案生成
    vector<Road> ans;
    kruskal(ans, pq, fa, cnt);
    //3. 输出生成的村村通方案
    cout << "村村通方案生成成功！这是需要新增的道路："<<endl;
    for (auto& road: ans) {
        cout << road.start << "-----" << road.end << ":" << road.length << endl;
    }
    cout << "请问是否添加这些道路：y/n" << endl;
    char select;
    cin >> select;
    if (select == 'y') {
        for (auto& road: ans) {
            roadList.push_back(road);
            int start = id2cnt[road.start], end = id2cnt[road.end];
            graph[start][end] = graph[end][start] = roadList.size(); // 村庄间道路矩阵更新
        }
        cout << "添加成功，现在村村畅通！"<<endl;
    }
}
// 打印路径
void printPath(int start, int end, vector<int>& pre, int dist) {
    stack<string> path;
    while (end != start) {
        path.push(villageList[end].id);
        end = pre[end];
    }
    cout << villageList[start].id;
    while (!path.empty()) {
        cout << "---->" << path.top();
        path.pop();
    }
    cout << ":" <<  dist << endl;
}

void dijkstra(int start) {
    int villages = villageList.size();
    vector<int> pre(villages, -1), dist(villages, INT_MAX);
    priority_queue<Node> pq;
    dist[start] = 0;
    pq.push({start, 0});
    while (!pq.empty()) {
        Node top = pq.top();
        pq.pop();
        int cnt = top.cnt, dis = top.dist;
        for (int i = 0; i < villages; i++) {
            if (graph[cnt][i] && dist[i] > dis + roadList[graph[cnt][i] - 1].length) {
                //cout << "更新了" << i << endl;
                pre[i] = cnt; // 记录前驱
                dist[i] = dis + roadList[graph[cnt][i] - 1].length; // 更新距离
                printPath(start, i, pre, dist[i]); // 打印路径
                pq.push({i, dist[i]}); // 放入优先队列
            }
        }
    }
}

void findShortestPath() {
    cout << "输入你要查询的村庄数量"<<endl;
    int n;
    cin >> n;
    string start;
    for (int i = 0; i < n; i++) {
        cout << "请输入你要查询的起点村庄编号"<<endl;
        cin >> start;
        int startCnt = id2cnt[start];
        cout << "正在查询到其它村庄的最短路线"<<endl;
        dijkstra(startCnt);
        cout << "查询完毕！"<< endl;
    }
}

void floyd(vector<vector<int>>& dist) {
    int n = villageList.size();
    for (int bridge = 0; bridge < n; bridge++) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (dist[i][j] > dist[i][bridge] + dist[bridge][j]) {
                    dist[j][i] = dist[i][j] = dist[i][bridge] + dist[bridge][j]; // 更新最短路线
                }
            }
        }
    }
}

// 不闭合回路的最短路径
// 1. 先使用floyd算法求出所有村庄间的最短路线，将其转换成完全图，因为允许走回头路
// 2. 采用贪心策略，每次选择距离（这个距离已经包含了回头路）距离当前所在村庄最近的村庄，直到遍历完所有村庄
// 3. 由于起点会影响结果，所有遍历每个村庄当起点的可能
void findShortestPath2() {
    int n = villageList.size();
    vector<int> fa(n);
    for (int i = 0; i < n; i++) fa[i] = i;
    int cnt = 0;
    if (!isConnected(cnt, fa)) {
        cout << "当前村庄不联通，无法生成路线" << endl;
        return;
    }
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    for (auto& x: roadList) {
        int start = id2cnt[x.start], end = id2cnt[x.end];
        dist[start][end] = dist[end][start] = x.length; // 放入已有距离
    }
    floyd(dist);
}