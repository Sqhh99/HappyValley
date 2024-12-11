#pragma once
#include <string_view>
#include <vector>
#include <istream>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include <limits>
#include <QDebug>


class AdjacencyMatrix
{
private:
    std::string str;
    //  无穷
    const int INF = std::numeric_limits<int>::max();

    // 顶点名称映射到索引的哈希表
    std::unordered_map<std::string, int> vertexIndex;

    // 顶点名称
    std::vector<std::string> vertices;

    std::vector<std::vector<int>> IadjacencyMatrix;
public:
    AdjacencyMatrix(std::string _str) : str(_str) {};

    //  floyd算法
    std::tuple<std::vector<std::vector<int>>, std::vector<std::vector<int>>> getfloydWeightMatrix();

    //  得到顶点名称映射到索引的哈希表
    std::tuple <std::unordered_map<std::string, int>, std::vector<std::string>> getNameIndexMap();
    //  得到邻接矩阵
    std::vector<std::vector<int>> getAdjacencyMatrix();

};

