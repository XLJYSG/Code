#include "../include/file.h"

extern vector<Village> villageList; // ��ׯ�б�
extern vector<Road> roadList; // ��·�б�
extern int graph[405][405]; // ��ׯ���·����
extern unordered_map<string, int> id2cnt; // ��ׯID����ŵ�ӳ��

void restore() {
    cout << "�ָ�������..." << endl;
    ifstream inFile("data.txt"); // ·��Ӧ�ô�Makefile����Ŀ¼��ʼ
    if (inFile.is_open()) {
        //���ݻָ�
        string id, name, brief, start, end;
        int x, y, length, n;
        inFile >> n;
        for (int i = 0; i < n; i++) {
            inFile >> id >> name >> brief >> x >> y;
            id2cnt[id] = i; // �ָ�id���洢�±��ӳ��
            villageList.push_back(Village(id, name, brief, x, y)); // �����ׯ�б�
        }
        inFile >> n;
        for (int i = 0; i < n; i++) {
            inFile >> start >> end >> length;
            int startCnt = id2cnt[start], endCnt = id2cnt[end];
            graph[startCnt][endCnt] = graph[endCnt][startCnt] = i+1; // ��ׯ���·������1
            roadList.push_back(Road(start, end, length)); // �����·�б�
        }
        inFile.close();   
        cout << "���ݻָ��ɹ���"<<endl;
    } else {
        cerr << "�����ļ�������"<<endl;
    }
}

void save() {
    cout << "���ݱ�����..." << endl;
    ofstream outFile("data.txt");
    if (outFile.is_open()) {
        //���ݱ���
        // �����ׯ��Ϣ
        int n = villageList.size();
        //cout << "��ׯ������" << n << endl;
        outFile << n << endl;
        for (int i = 0; i < n; i++) {
            //cout << villageList[i].id << " " << villageList[i].name << " " << villageList[i].brief << " " << villageList[i].x << " " << villageList[i].y << endl;
            outFile << villageList[i].id << " " << villageList[i].name << " " << villageList[i].brief << " " << villageList[i].x << " " << villageList[i].y << endl;
        }
        // // �����ׯID���洢�±��ӳ��
        // for (auto it = id2cnt.begin(); it != id2cnt.end(); it++) {
        //     outFile << it->first << " " << it->second << endl;
        // }
        // �����·��Ϣ
        n = roadList.size();
        outFile << n << endl;
        for (int i = 0; i < n; i++) {
            outFile << roadList[i].start << " " << roadList[i].end << " " << roadList[i].length << endl;
        }
        outFile.close();
        cout << "���ݱ���ɹ���"<<endl;
    } else {
        cerr << "�����ļ���ʧ��"<<endl;
    }
}