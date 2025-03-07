#ifndef ROAD_H
#define ROAD_H

#include <string>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "village.h"
using namespace std;

struct Road {
    string start, end; // 起点和终点
    int length; // 道路长度
    Road(string start, string end, int length) {
        this->start = start;
        this->end = end;
        this->length = length;
    }
    bool operator<(const Road& t) const {
        return this->length > t.length;
    }
};

// 添加道路
void addRoad();
// 删除道路
void deleteRoad();
// 修改道路
void modifyRoad();
// 计算两村庄间的距离
int getLen(int start, int end);

#endif