#include <iostream>
#include "../include/file.h"
#include "../include/road.h"
#include "../include/village.h"
#include "../include/graph.h"
using namespace std;

vector<Village> villageList; // ��ׯ�б�
vector<Road> roadList; // ��·�б�
int graph[405][405]; // ��ׯ���·����
unordered_map<string, int> id2cnt; // ��ׯID����ŵ�ӳ��

int menu() {
    cout << "������ѡ���ţ�" << endl;
    cout << "1.----��Ӵ�ׯ����Ϣ----"<<endl;
    cout << "2.----ɾ����ׯ����Ϣ----"<<endl;
    cout << "3.----�޸Ĵ�ׯ����Ϣ----"<<endl;
    cout << "4.----��ӵ�·����Ϣ----"<<endl;
    cout << "5.----ɾ����·����Ϣ----"<<endl;
    cout << "6.----�޸ĵ�·����Ϣ----"<<endl;
    cout << "7.----���ɴ��ͨ����----"<<endl;
    cout << "8.----��ѯ��������ׯ�����·��----"<<endl;
    cout << "9.----��ѯ�������д�ׯ�����·��----"<<endl;
    cout << "10.---��ѯ�������д�ׯ���ص��������·��----"<<endl;
    cout << "11.-----�˳�����----"<<endl;
    int select;
    cin >> select;
    return select;
}

int main() {
    cout << "��ӭʹ�ô�ׯ���·����ϵͳ������" << endl;
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
            cout << "����������������룡" << endl;
            break;
        }
    }
}