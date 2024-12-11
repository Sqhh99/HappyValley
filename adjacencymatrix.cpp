#include "AdjacencyMatrix.h"

//  floyd算法
std::tuple<std::vector<std::vector<int>>, std::vector<std::vector<int>>> AdjacencyMatrix::getfloydWeightMatrix()
{
    int numVertices = IadjacencyMatrix.size();
    std::vector<std::vector<int>> distanceMatrix(IadjacencyMatrix);

    std::vector<std::vector<int>> next(numVertices, std::vector<int>(numVertices, -1));

    for (int k = 0; k < numVertices; ++k) {
        for (int i = 0; i < numVertices; ++i) {
            for (int j = 0; j < numVertices; ++j) {
                if (distanceMatrix[i][k] != INF && distanceMatrix[k][j] != INF &&
                    distanceMatrix[i][k] + distanceMatrix[k][j] < distanceMatrix[i][j]) {
                    distanceMatrix[i][j] = distanceMatrix[i][k] + distanceMatrix[k][j];
                    next[i][j] = k;
                }
            }
        }
    }
    return std::make_tuple(distanceMatrix, next);
}

std::tuple <std::unordered_map<std::string, int>,std::vector<std::string>>  AdjacencyMatrix::getNameIndexMap()
{
    std::ifstream inputFile(str);
    if (!inputFile.is_open())
        qDebug() << "文件打开失败";

    // 读取文件并构建顶点和索引的映射
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string source, target;
        int weight;

        if (iss >> source >> target >> weight) {
            if (vertexIndex.find(source) == vertexIndex.end()) {
                vertexIndex[source] = vertices.size();
                vertices.push_back(source);
            }

            if (vertexIndex.find(target) == vertexIndex.end()) {
                vertexIndex[target] = vertices.size();
                vertices.push_back(target);
            }
        }
    }
    //  将文件名写入
    std::ofstream outputFile("NameIndexFileMap.txt");
    for (const auto &i : vertices) outputFile << i << " ";

    return std::make_tuple(vertexIndex, vertices);
}

std::vector<std::vector<int>> AdjacencyMatrix::getAdjacencyMatrix()
{
    std::ifstream inputFile(str);
    std::string line;

    // 初始化邻接矩阵
    std::vector<std::vector<int>> adjacencyMatrix(vertices.size(), std::vector<int>(vertices.size(), 0));
    // 重新定位文件指针到文件开头
    inputFile.clear();
    inputFile.seekg(0, std::ios::beg);
    // 读取文件并填充邻接矩阵
    while (std::getline(inputFile, line)) {
        std::istringstream iss(line);
        std::string source, target;
        int weight;

        if (iss >> source >> target >> weight) {
            int sourceIndex = vertexIndex[source];
            int targetIndex = vertexIndex[target];

            // 更新两个方向的邻接矩阵
            adjacencyMatrix[sourceIndex][targetIndex] = weight;
            adjacencyMatrix[targetIndex][sourceIndex] = weight;
        }
    }

    for (auto& i : adjacencyMatrix)
        for (auto& j : i) if (j == 0) j = INF;

    size_t diagonalLength = std::min(adjacencyMatrix.size(), adjacencyMatrix[0].size());

    // 将主对角线上的元素设置为0
    for (size_t i = 0; i < diagonalLength; ++i) adjacencyMatrix[i][i] = 0;

    inputFile.close();
    IadjacencyMatrix = adjacencyMatrix;
    return adjacencyMatrix;
}
