#include "../include/village.h"
#include "../include/road.h"

extern vector<Village> villageList; // ��ׯ�б�
extern vector<Road> roadList; // ��·�б�
extern int graph[405][405]; // ��ׯ���·����
extern unordered_map<string, int> id2cnt; // ��ׯID����ŵ�ӳ��

void addVillage() {
    cout << "��������Ҫ��ӵĴ�ׯ������" << endl;
    string id, name, brief;
    int x, y, n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "����������:��ׯ�ı�ţ����ƣ���飬��������" << endl;
        cin >> id >> name >> brief >> x >> y;
        id2cnt[id] = villageList.size(); // ��ׯID���洢�±��ӳ��
        villageList.push_back(Village(id, name, brief, x, y));
        cout << "��ӳɹ���" << endl;
    }
}

// ɾ����ׯ����Ϣ�������ׯ��صĵ�·
void deleteVillage() {
    cout << "��������Ҫɾ���Ĵ�ׯ������" << endl;
    int n;
    cin >> n;
    string id;
    for (int i = 0; i < n; i++) {
        cout << "��������Ҫɾ���Ĵ�ׯ�ı��" << endl;
        cin >> id;
        int cnt = id2cnt[id], villages = villageList.size();
        for (int i = 0; i < villages; i++) {
            // ���������������ׯ�ĵ�·����ɾ��
            if (graph[cnt][i]) {
                int roadCnt = graph[cnt][i] - 1;
                roadList.erase(roadList.begin() + roadCnt); // ɾ����·��Ϣ
                graph[cnt][i] = graph[i][cnt] = 0; // ��ׯ���·������0
            }
            if (i > cnt) {
                id2cnt[villageList[i].id]--; // �����±�ӳ��
            }
        }
        villageList.erase(villageList.begin() + cnt); // ɾ����ׯ��Ϣ
        id2cnt.erase(id); // ɾ����ׯID����ŵ�ӳ��
        cout << "ɾ���ɹ���" << endl;
    }
}
// �޸Ĵ�ׯ��Ϣ
void modifyVillage() {
    cout << "��������Ҫ�޸ĵĴ�ׯ������" << endl;
    int n;
    cin >> n;
    string id, name, brief;
    int x, y;
    for (int i = 0; i < n; i++) {
        cout << "��������Ҫ�޸ĵĴ�ׯ�ı��" << endl;
        cin >> id;
        int cnt = id2cnt[id];
        cout << villageList[cnt].id << " " << villageList[cnt].name << endl;
        cout << villageList[cnt].brief <<endl;
        cout << villageList[cnt].x << " " << villageList[cnt].y << endl;
        id2cnt.erase(id); // ɾ����ׯID���±��ӳ��
        cout << "���ǵ�ǰ��Ϣ�������������޸ĺ��:��ׯ�ı�ţ����ƣ���飬��������" << endl;
        cin >> id >> name >> brief >> x >> y;
        villageList[cnt].id = id;
        villageList[cnt].name = name;
        villageList[cnt].brief = brief;
        villageList[cnt].x = x;
        villageList[cnt].y = y;
        id2cnt[id] = cnt; // ���´�ׯID���±��ӳ��
        cout << "��ׯ��Ϣ�޸ĳɹ���,�����޸ĺ����Ϣ" << endl;
        cout << villageList[cnt].id << " " << villageList[cnt].name << endl;
        cout << villageList[cnt].brief <<endl;
        cout << villageList[cnt].x << " " << villageList[cnt].y << endl;
    }
}