#ifndef VILLAGE_H
#define VILLAGE_H

#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;


struct Village {
    string id; // 村庄ID
    string name;// 村庄名称
    int x, y; // 村庄坐标
    string brief;// 村庄简介
    Village(string id, string name, string brief, int x, int y) {
        this->id = id;
        this->name = name;
        this->brief = brief;
        this->x = x;
        this->y = y;
    }
};
 // 添加村庄
void addVillage();
// 删除村庄的信息，及与村庄相关的道路
void deleteVillage();
// 修改村庄信息
void modifyVillage();


#endif