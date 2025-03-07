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
    int n = villageList.size();
    for (int i = 0; i < n; i++) {
        int start = id2cnt[roadList[i].start], end = id2cnt[roadList[i].end]; // ��ȡ��ׯ�±�
        int faStart = find(start, fa), faEnd = find(end, fa); // �ҵ�������ׯ���ڵļ��ϱ��
        // �������һ������
        if (faStart != faEnd) {
            fa[faStart] = faEnd; // �ϲ���������
            cnt++; // ���¹ؼ��ߵ�����
        }
    }
    if (cnt < n - 1) return false;
    return true;
}

// �жϴ�ׯ�Ƿ���ͨ��������һ���ܳ�����С�Ĵ��ͨ����
// 1. �Ƚ����е�·���벢�鼯��, ���ж����е�·�Ƿ�֤���ͨ
// 2. ������С����������е�·�������·���ߵĴ�ׯ����ͬһ��������
void connectAndFind() {
    cout << "�����ж��Ƿ���ͨ..."<<endl;
    int n = villageList.size();
    vector<int> fa(n);
    for (int i = 0; i < n; i++) fa[i] = i;
    int cnt = 0;
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
                //cout << "������" << i << endl;
                pre[i] = cnt; // ��¼ǰ��
                dist[i] = dis + roadList[graph[cnt][i] - 1].length; // ���¾���
                printPath(start, i, pre, dist[i]); // ��ӡ·��
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

// ���պϻ�·�����·��
// 1. ��ʹ��floyd�㷨������д�ׯ������·�ߣ�����ת������ȫͼ����Ϊ�����߻�ͷ·
// 2. ����̰�Ĳ��ԣ�ÿ��ѡ����루��������Ѿ������˻�ͷ·�����뵱ǰ���ڴ�ׯ����Ĵ�ׯ��ֱ�����������д�ׯ
// 3. ��������Ӱ���������б���ÿ����ׯ�����Ŀ���
void findShortestPath2() {
    int n = villageList.size();
    vector<int> fa(n);
    for (int i = 0; i < n; i++) fa[i] = i;
    int cnt = 0;
    if (!isConnected(cnt, fa)) {
        cout << "��ǰ��ׯ����ͨ���޷�����·��" << endl;
        return;
    }
    vector<vector<int>> dist(n, vector<int>(n, INT_MAX));
    for (auto& x: roadList) {
        int start = id2cnt[x.start], end = id2cnt[x.end];
        dist[start][end] = dist[end][start] = x.length; // �������о���
    }
    floyd(dist);
}