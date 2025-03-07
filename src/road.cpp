#include "../include/road.h"

extern vector<Village> villageList; // ��ׯ�б�
extern vector<Road> roadList; // ��·�б�
extern int graph[405][405]; // ��ׯ���·����
extern unordered_map<string, int> id2cnt; // ��ׯID����ŵ�ӳ��

int getLen(int start, int end) {
    int x1 = villageList[start].x, y1 = villageList[start].y;
    int x2 = villageList[end].x, y2 = villageList[end].y;
    return round(sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2)));
}

// ��ӵ�·
void addRoad() {
    cout << "��������Ҫ��ӵĵ�·������" << endl;
    string start, end;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "��������Ҫ��ӵĵ�·������ׯ��ź��յ��ׯ���" << endl;
        cin >> start >> end;
        int startCnt = id2cnt[start], endCnt = id2cnt[end];
        int len = getLen(startCnt, endCnt);
        roadList.push_back(Road(start, end, len));
        graph[startCnt][endCnt] = graph[endCnt][startCnt] = roadList.size(); // ��ׯ���·�������
        cout << "��ӳɹ���" << endl;
    }
}

// ɾ����·
void deleteRoad() {
    cout << "��������Ҫɾ���ĵ�·������" << endl;
    int n;
    cin >> n;
    string start, end;
    for (int i = 0; i < n; i++) {
        cout << "��������Ҫɾ���ĵ�·������ׯ��ź��յ��ׯ���" << endl;
        cin >> start >> end;
        int startCnt = id2cnt[start], endCnt = id2cnt[end];
        int roadCnt = graph[startCnt][endCnt] - 1;
        roadList.erase(roadList.begin() + roadCnt); // ɾ����·��Ϣ
        graph[startCnt][endCnt] = graph[endCnt][startCnt] = 0; // ��ׯ���·������0
        cout << "ɾ���ɹ���" << endl;
    }
}

// �޸ĵ�·
void modifyRoad() {
    cout << "��������Ҫ�޸ĵĵ�·������" << endl;
    int n;
    cin >> n;
    string start, end;
    //int len;
    for (int i = 0; i < n; i++) {
        cout << "��������Ҫ�޸ĵĵ�·������ׯ��ź��յ��ׯ���" << endl;
        cin >> start >> end;
        int startCnt = id2cnt[start], endCnt = id2cnt[end];
        int roadCnt = graph[startCnt][endCnt] - 1;
        //cout << roadList[roadCnt].start << " " << roadList[roadCnt].end << endl;
        graph[startCnt][endCnt] = graph[endCnt][startCnt] = 0; // ��ׯ���·������0
        cout << "�����������޸ĺ��:��·������ׯ��ţ��յ��ׯ���" << endl;
        cin >> start >> end;
        roadList[roadCnt].start = start;
        roadList[roadCnt].end = end;
        startCnt = id2cnt[start], endCnt = id2cnt[end];
        roadList[roadCnt].length = getLen(startCnt, endCnt);
        graph[startCnt][endCnt] = graph[endCnt][startCnt] = roadCnt + 1; // ��ׯ���·�������
    }
}
