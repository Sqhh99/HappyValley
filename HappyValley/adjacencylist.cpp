#include "AdjacencyList.h"

//  构造函数
AdjacencyList::AdjacencyList(const std::vector<std::vector<int>>& adjacency_matrix, std::vector<std::string> str)
    : adjacencyList_(buildAdjacencyList(adjacency_matrix)),str_(str) {}

//  创建邻接表
std::vector<AdjacencyList::Vertex> AdjacencyList::buildAdjacencyList(const std::vector<std::vector<int>>& adjacency_matrix)
{
    int numVertices = adjacency_matrix.size();
    std::vector<Vertex> adjacencyList(numVertices);

    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            // 排除主对角线上的元素和无穷大值
            if (i != j && adjacency_matrix[i][j] != INF) {
                adjacencyList[i].edges.emplace_back(j, adjacency_matrix[i][j]);
            }
        }
    }
    return adjacencyList;
}


