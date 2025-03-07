#include "../include/graph.h"

extern vector<Village> villageList; // ��ׯ�б�
extern vector<Road> roadList; // ��·�б�
extern int graph[405][405]; // ��ׯ���·����
extern unordered_map<string, int> id2cnt; // ��ׯID����ŵ�ӳ��

// ���鼯���Ҹ��ڵ㺯��
int find(int x, vector<int>& fa) {
    if (fa[x] != x) fa[x] = find(fa[x], fa);
    return fa[x];
}
// ���ͨ�㷨
void kruskal(vector<Road>& ans, priority_queue<Road>& pq, vector<int>& fa,int cnt) {
    int limit = villageList.size() - 1;
    //cout << cnt << " " << limit << endl;
    // ��Ϊһ����pq��֮ǰ���ѡ�����������ж�pq�Ƿ�Ϊ��
    while (cnt < limit) {
        //cout << "����ѡ���";
        Road top = pq.top();
        //cout << top.start << "-----" << top.end << ":" << top.length << endl;
        pq.pop();
        int start = id2cnt[top.start], end = id2cnt[top.end];
        int faStart = find(start, fa), faEnd = find(end, fa);
        // ����ߵ����˵Ĵ�ׯ����ͬһ�������У���ѡ��ñ�
        if (faStart != faEnd) {
            //cout << "ѡ�����";
            ans.push_back(top);
            cnt++;
            fa[faStart] = faEnd; // �ϲ���������
        }
    }
}

// �жϵ�ǰ��ׯ�Ƿ���ͨ
bool isConnected(int& cnt, vector<int>& fa) {
    int n = roadList.size();
    //cout <<"22222" << endl;
    for (int i = 0; i < n; i++) {
        int start = id2cnt[roadList[i].start], end = id2cnt[roadList[i].end]; // ��ȡ��ׯ�±�
        //cout << start << " " << end << endl;
        int faStart = find(start, fa), faEnd = find(end, fa); // �ҵ�������ׯ���ڵļ��ϱ��
        // �������һ������
        if (faStart != faEnd) {
            fa[faStart] = faEnd; // �ϲ���������
            cnt++; // ���¹ؼ��ߵ�����
        }
    }
    n = fa.size();
    if (cnt < n - 1) return false;
    return true;
}

// �жϴ�ׯ�Ƿ���ͨ��������һ���ܳ�����С�Ĵ��ͨ����
// 1. �Ƚ����е�·���벢�鼯��, ���ж����е�·�Ƿ�֤���ͨ
// 2. ������С����������е�·�������·���ߵĴ�ׯ����ͬһ��������,��ѡ��ñߣ������벢�鼯��
void connectAndFind() {
    cout << "�����ж��Ƿ���ͨ..."<<endl;
    int n = villageList.size();
    vector<int> fa(n);
    for (int i = 0; i < n; i++) fa[i] = i;
    int cnt = 0;
    //cout << "111111" << endl;
    if (isConnected(cnt, fa)) {
        cout << "��ǰ��ׯ����ͨ���������ɴ��ͨ����" << endl;
        return;
    } else {
        cout << "��ǰ��ׯ����ͨ�����������ܳ�����С�Ĵ��ͨ����" << endl;
    }
    // ��ʼ���ɴ��ͨ����
    priority_queue<Road> pq; // С���ѣ����յ�·��������
    // 1. ��ȡ��ѡȡ�ı�
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (graph[i][j] || find(i, fa) == find(j, fa)) continue; // ����ߴ��ڣ����߱����˵Ĵ�ׯ�Ѿ���һ�����ϣ�������
            int len = getLen(i, j);
            //cout << "�б߼���" << endl;
            //cout << villageList[i].id << "-----" << villageList[j].id << ":" << len << endl;
            pq.push(Road(villageList[i].id, villageList[j].id, len)); // �����ѡȡ�ı�
        }
    }
    // 2. ���ͨ��������
    vector<Road> ans;
    kruskal(ans, pq, fa, cnt);
    //3. ������ɵĴ��ͨ����
    cout << "���ͨ�������ɳɹ���������Ҫ�����ĵ�·��"<<endl;
    for (auto& road: ans) {
        cout << road.start << "-----" << road.end << ":" << road.length << endl;
    }
    cout << "�����Ƿ������Щ��·��y/n" << endl;
    char select;
    cin >> select;
    if (select == 'y') {
        for (auto& road: ans) {
            roadList.push_back(road);
            int start = id2cnt[road.start], end = id2cnt[road.end];
            graph[start][end] = graph[end][start] = roadList.size(); // ��ׯ���·�������
        }
        cout << "��ӳɹ������ڴ�峩ͨ��"<<endl;
    }
}
// ��ӡ·��
void printPath(int start, int end, vector<int>& pre, int dist) {
    stack<string> path; // ����
    // �ָ�·���Ĺ��̾�������pre���飬���յ���ݵ����
    while (end != start) {
        path.push(villageList[end].id);
        end = pre[end];
    }
    cout << villageList[start].id;
    // ��ӡ·��
    while (!path.empty()) {
        cout << "---->" << path.top();
        path.pop();
    }
    cout << ":" <<  dist << endl;
}
// ��Դ���·��
void dijkstra(int start) {
    int villages = villageList.size();
    vector<int> pre(villages, -1), dist(villages, INT_MAX); // ��¼ǰ������¼��̾���
    priority_queue<Node> pq; // С���ѣ����վ������ľ�������
    dist[start] = 0; // ��¼���㵽���ľ���
    pq.push({start, 0});
    // ÿ�ε���ջ��Ԫ��
    while (!pq.empty()) {
        Node top = pq.top();
        pq.pop();
        int cnt = top.cnt, dis = top.dist;
        if (dis > dist[cnt]) continue; // ��������Ѿ�������ǰ��¼����С���룬������
        // ��ӡ·����һ�������ĵ㶼���ڵ�ǰ��̾��룬��Ϊ�����ڸ����߳�������һ��Ϊ��С����
        if (cnt != start) printPath(start, cnt, pre, dist[cnt]); 
        for (int i = 0; i < villages; i++) {
            // ���������ׯ�����ľ����С������£������
            if (graph[cnt][i] && dist[i] > dis + roadList[graph[cnt][i] - 1].length) {
                //cout << "������" << i << endl;
                pre[i] = cnt; // ��¼ǰ�������ڻָ�·��
                dist[i] = dis + roadList[graph[cnt][i] - 1].length; // ���¾���
                pq.push({i, dist[i]}); // �������ȶ���
            }
        }
    }
}

void findShortestPath() {
    cout << "������Ҫ��ѯ�Ĵ�ׯ����"<<endl;
    int n;
    cin >> n;
    string start;
    for (int i = 0; i < n; i++) {
        cout << "��������Ҫ��ѯ������ׯ���"<<endl;
        cin >> start;
        int startCnt = id2cnt[start];
        cout << "���ڲ�ѯ��������ׯ�����·��"<<endl;
        dijkstra(startCnt);
        cout << "��ѯ��ϣ�"<< endl;
    }
}

void floyd(vector<vector<int>>& dist) {
    int n = villageList.size();
    for (int bridge = 0; bridge < n; bridge++) {
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (dist[i][j] > dist[i][bridge] + dist[bridge][j]) {
                    dist[j][i] = dist[i][j] = dist[i][bridge] + dist[bridge][j]; // �������·��
                }
            }
        }
    }
}
// ��¼·��
void getPath(int start, int end, vector<int>& pre, vector<vector<vector<string>>>& path) {
    stack<string> s;
    int x = end;
    while (x != start) {
        s.push(villageList[x].id);
        x = pre[x];
    }
    path[start][end].push_back(villageList[start].id);
    while (!s.empty()) {
        path[start][end].push_back(s.top());
        s.pop();
    }
}

// ��ô嵽����������·���뼰·��
void dijkstra1(int start, vector<vector<vector<string>>>& path, vector<vector<int>>& dis) {
    int villages = villageList.size();
    vector<int> pre(villages, -1); // ��¼ǰ������¼��̾���
    priority_queue<Node> pq; // С���ѣ����վ������ľ�������
    dis[start][start] = 0; // ��¼���㵽���ľ���
    pq.push({start, 0});
    // ÿ�ε���ջ��Ԫ��
    while (!pq.empty()) {
        Node top = pq.top();
        pq.pop();
        int cnt = top.cnt, dist = top.dist;
        if (dist > dis[start][cnt]) continue; // ��������Ѿ�������ǰ��¼����С���룬������
        // ��ӡ·����һ�������ĵ㶼���ڵ�ǰ��̾��룬��Ϊ�����ڸ����߳�������һ��Ϊ��С����
        if (cnt != start) getPath(start, cnt, pre, path); 
        for (int i = 0; i < villages; i++) {
            // ���������ׯ�����ľ����С������£������
            if (graph[cnt][i] && dis[start][i] > dist + roadList[graph[cnt][i] - 1].length) {
                //cout << "������" << i << endl;
                pre[i] = cnt; // ��¼ǰ�������ڻָ�·��
                dis[start][i] = dist + roadList[graph[cnt][i] - 1].length; // ���¾���
                pq.push({i, dis[start][i]}); // �������ȶ���
            }
        }
    }
}
// ������startΪ������С·��
int greedy(vector<vector<vector<string>>>& path, vector<vector<int>>& dis, int start, vector<string>& ans) {
    int n = villageList.size(), cnt = 0, sumDis = 0;
    vector<bool> vis(n, false);
    vis[start] = true;
    while (cnt < n - 1) {
        int minDis = INT_MAX, minCnt;
        for (int i = 0; i < n; i++) {
            if (vis[i]) continue;
            if (dis[start][i] < minDis) {
                minDis = dis[start][i];
                minCnt = i;
            }
        }
        sumDis += minDis;
        cnt++;
        int n1 = path[start][minCnt].size();
        // ����������Ĵ�ׯ����ֹ����ظ�
        for (int i = 1; i < n1; i++) ans.push_back(path[start][minCnt][i]);
        start = minCnt; // �������
        vis[start] = true; // ����ѷ���
    }
    return sumDis;
}


// ���պϻ�·�����·��
// 1. ����ÿ����ׯʹ��dijkstra�㷨������д�ׯ������·�ߣ�����ת������ȫͼ����Ϊ�����߻�ͷ·
// 2. ����̰�Ĳ��ԣ�ÿ��ѡ����루��������Ѿ������˻�ͷ·�����뵱ǰ���ڴ�ׯ����Ĵ�ׯ��ֱ�����������д�ׯ
// 3. ��������Ӱ���������б���ÿ����ׯ�����Ŀ���
void findShortestPath2(int x) {
    int n = villageList.size();
    vector<int> fa(n);
    for (int i = 0; i < n; i++) fa[i] = i;
    int cnt = 0;
    if (!isConnected(cnt, fa)) {
        cout << "��ǰ��ׯ����ͨ���޷�����·��" << endl;
        return;
    }
    // vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    // for (auto& x: roadList) {
    //     int start = id2cnt[x.start], end = id2cnt[x.end];
    //     dist[start][end] = dist[end][start] = x.length; // �������о���
    // }
    vector<vector<vector<string>>> path(n, vector<vector<string>> (n)); // ��¼���������·��
    vector<vector<int>> dis(n, vector<int>(n, INT_MAX));// ��¼��������̾���
    // ����ÿ����ׯ��Ϊ���
    for (int i = 0; i < n; i++) { 
        dijkstra1(i, path, dis);
    }
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << "dis[i][j]:" << dis[i][j];
    //     }
    // }
    // for (int i = 0; i < n; i++) {
    //     for (int j = 0; j < n; j++) {
    //         cout << "path[i][j]:";
    //         for (auto& x: path[i][j]) cout << x << " ";
    //         cout << endl;
    //     }
    // }
    int minDis = INT_MAX, minCnt, d;
    vector<vector<string>> ans(n);
    for (int i = 0; i < n; i++) {
        d = greedy(path, dis, i, ans[i]);
        int endCnt = id2cnt[ans[i].back()];
        if (x == 1) d += dis[i][endCnt]; // ���ϻ�ͷ·
        if (d < minDis) {
            minDis = d;
            minCnt = i;
        }
    }
    cout << "���·��Ϊ��" << endl;
    cout << villageList[minCnt].id;
    for (auto& x: ans[minCnt]) {
        cout << "---->" << x;
    }
    if (x == 1) cout << "---->" << villageList[minCnt].id; // ���ϻ�ͷ·
    cout << " " << minDis <<endl;
}