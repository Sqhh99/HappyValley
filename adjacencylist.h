#pragma once
#include <vector>
#include <iostream>
#include <limits>
#include <queue>
#include <stack>
#include <QDebug>

//  无穷
const int INF = std::numeric_limits<int>::max();

class AdjacencyList {
public:
    // 边
    struct Edge {
        int destination;
        int weight;
        Edge(int dest, int w) : destination(dest), weight(w) {}
    };
    // 顶点
    struct Vertex {
        std::vector<Edge> edges;
    };
    std::vector<Vertex> adjacencyList_;

    std::vector<std::string> str_;
public:
    AdjacencyList(const std::vector<std::vector<int>>& adjacency_matrix, std::vector<std::string> str);

private:
    std::vector<Vertex> buildAdjacencyList(const std::vector<std::vector<int>>& adjacency_matrix);

};
