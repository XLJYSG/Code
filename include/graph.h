#ifndef GRAPH_H
#define GRAPH_H

#include <queue>
#include <stack>
#include <vector>
#include <string>
#include "road.h"
using namespace std;

struct Node {
    int cnt, dist;
    Node(int cnt, int dist) {
        this->cnt = cnt;
        this->dist = dist;
    }
    bool operator<(const Node& t) const {
        return this->dist > t.dist;
    }
};

// 并查集查找父节点函数
int find(int x, vector<int>& fa);
// 村村通算法
void kruskal(vector<Road>& ans, priority_queue<Road>& pq, vector<int>& fa,int cnt);
// 判断当前村庄是否联通
bool isConnected(int& cnt, vector<int>& fa);
void connectAndFind();
// 打印路径
void printPath(int start, int end, vector<int>& pre, int dist);
void dijkstra(int start);
void findShortestPath();
void floyd(vector<vector<int>>& dist);
void findShortestPath2();

#endif