#include "widget.h"
#include "ui_widget.h"
#include <QMessageBox>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowTitle("欢乐谷导游系统");
}

void Widget::closeEvent(QCloseEvent* )
{
    emit testSignal();
}

Widget::~Widget()
{
    delete ui;
}

//  邻接矩阵
void Widget::on_pushButton_clicked()
{
    if (IvertexIndex.empty() && IvertexNames.empty())
    {
        QMessageBox::warning(this, "文件", "请先读取文件!!!");
        return;
    }
    ui->textBrowser->clear();
    ui->textBrowser->append("邻接矩阵为：\n");

    QTextCursor cursor(ui->textBrowser->document());
    cursor.movePosition(QTextCursor::End);

    for (const auto& i : IadjacencyMatrix)
    {
        for (const auto& j : i)
        {
            if (j == INF)
                cursor.insertText("INF\t");
            else
                cursor.insertText(QString::number(j) + "\t");
        }
        cursor.insertText("\n");
    }
}
//  权值矩阵
void Widget::on_pushButton_2_clicked()
{
    if (IvertexIndex.empty() && IvertexNames.empty())
    {
        QMessageBox::warning(this, "文件", "请先读取文件!!!");
        return;
    }
    ui->textBrowser->clear();
    ui->textBrowser->append("权值矩阵为：\n");

    QTextCursor cursor(ui->textBrowser->document());
    cursor.movePosition(QTextCursor::End);

    for (const auto& i : distanceMatrix)
    {
        for (const auto& j : i)
        {
            if (j == INF)
                cursor.insertText("INF\t");
            else
                cursor.insertText(QString::number(j) + "\t");
        }
        cursor.insertText("\n");
    }

}

//  邻接表
void Widget::on_pushButton_3_clicked()
{
    if (IvertexIndex.empty() && IvertexNames.empty())
    {
        QMessageBox::warning(this, "文件", "请先读取文件!!!");
        return;
    }
    ui->textBrowser->clear();
    ui->textBrowser->append("邻接表为：\n");

    QTextCursor cursor(ui->textBrowser->document());
    cursor.movePosition(QTextCursor::End);

    for (size_t i = 0; i < IadjacencyList.size(); ++i)
    {
        cursor.insertText("顶点 ");
        cursor.insertText(QString::fromStdString(IvertexNames[i]));
        cursor.insertText(": ");
        for (const auto& edge : IadjacencyList[i].edges) {
            cursor.insertText("(");
            cursor.insertText(QString::fromStdString(IvertexNames[edge.destination]));
            cursor.insertText(", ");
            cursor.insertText(QString::number(edge.weight));
            cursor.insertText(") ");
        }
        cursor.insertText("\n");
    }

}
// 深度优先搜索输出所有路径
void Widget::printPathsDFS(int current, int end, std::vector<bool>& visited, std::vector<int>& path) const {
    visited[current] = true;
    path.push_back(current);

    QTextCursor cursor(ui->textBrowser_2->document());
    cursor.movePosition(QTextCursor::End);

    if (current == end) {
        // 打印当前路径
        for (int vertex : path) {
            if (IvertexNames[vertex] != IvertexNames[end])
            {
                cursor.insertText(QString::fromStdString(IvertexNames[vertex]));
                cursor.insertText("->");
            }
            else cursor.insertText(QString::fromStdString(IvertexNames[vertex]));
        }
        cursor.insertText("\n");
    }
    else {
        // 当与当前顶点相邻的所有顶点重复
        for (const auto& edge : IadjacencyList[current].edges) {
            if (!visited[edge.destination]) {
                printPathsDFS(edge.destination, end, visited, path);
            }
        }
    }
    visited[current] = false;
    path.pop_back();
}
//  所有路径
void Widget::on_pushButton_6_clicked()
{
    if (IvertexIndex.empty() && IvertexNames.empty())
    {
        QMessageBox::warning(this, "文件", "请先读取文件!!!");
        return;
    }
    std::string begin = ui->comboBox->currentText().toStdString();
    std::string end = ui->comboBox_2->currentText().toStdString();

    std::vector<bool> visited(IadjacencyList.size(), false);
    std::vector<int> path;

    ui->textBrowser_2->clear();

    QTextCursor cursor(ui->textBrowser_2->document());
    cursor.movePosition(QTextCursor::End);

    cursor.insertText("从 ");
    cursor.insertText(QString::fromStdString(begin));
    cursor.insertText("->");
    cursor.insertText(QString::fromStdString(end));
    cursor.insertText(" 的所有路径为:\n");

    printPathsDFS(IvertexIndex[begin], IvertexIndex[end], visited, path);
}

// Dijkstra算法
void Widget::dijkstra(int start) const {
    int numVertices = IadjacencyList.size();
    QTextCursor cursor(ui->textBrowser_2->document());
    cursor.movePosition(QTextCursor::End);

    // 初始化距离数组和前一个顶点数组
    std::vector<int> distance(numVertices, std::numeric_limits<int>::max());
    std::vector<int> previous(numVertices, -1);

    // 使用优先队列来实现最小优先级队列，存储顶点和距离的pair
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    // 将起点插入队列，距离设置为0
    pq.push(std::make_pair(0, start));
    distance[start] = 0;

    while (!pq.empty()) {
        int current = pq.top().second;
        pq.pop();

        for (const auto& edge : IadjacencyList[current].edges) {
            int newDistance = distance[current] + edge.weight;

            // 如果找到更短的路径，更新距离数组和前一个顶点数组，将顶点加入队列
            if (newDistance < distance[edge.destination]) {
                distance[edge.destination] = newDistance;
                previous[edge.destination] = current;
                pq.push(std::make_pair(newDistance, edge.destination));
            }
        }
    }

    // 输出结果
    cursor.insertText("从");
    cursor.insertText(QString::fromStdString(IvertexNames[start]));
    cursor.insertText(" 到其他顶点的路径：");
    cursor.insertText("\n");
    for (int i = 0; i < numVertices; ++i) {
        if (i != start) {
            cursor.insertText("到地点：");
            cursor.insertText(QString::fromStdString(IvertexNames[i]));
            cursor.insertText(" 的距离为 ");
            cursor.insertText(QString::number(distance[i]));
            cursor.insertText(", 路径为: ");
            printPath(start, i, previous);
            cursor.insertText("\n");
        }
    }
}

//  递归打印路径
void Widget::printPath(int start, int end, const std::vector<int>& previous) const {
    std::stack<int> pathStack;
    int current = end;
    QTextCursor cursor(ui->textBrowser_2->document());
    cursor.movePosition(QTextCursor::End);

    while (current != start) {
        pathStack.push(current);
        current = previous[current];
    }

    cursor.insertText(QString::fromStdString(IvertexNames[start]));
    cursor.insertText(" ");
    while (!pathStack.empty()) {
        cursor.insertText("-> ");
        cursor.insertText(QString::fromStdString(IvertexNames[pathStack.top()]));
        cursor.insertText(" ");
        pathStack.pop();
    }
}

//  最短路径算法
void Widget::on_pushButton_7_clicked()
{
    if (IvertexIndex.empty() || IvertexNames.empty())
    {
        QMessageBox::warning(this, "文件", "请先读取文件!!!");
        return;
    }
    ui->textBrowser_2->clear();
    std::string begin = ui->comboBox->currentText().toStdString();
    dijkstra(IvertexIndex[begin]);
}

//  最小生成树
std::vector<std::pair<int, int>> Widget::primMST(int startVertex) {
    int numVertices = IadjacencyMatrix.size();
    std::vector<int> key(numVertices, INF);
    std::vector<int> parent(numVertices, -1);
    std::vector<bool> inMST(numVertices, false);

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    // 从指定的起始顶点开始
    pq.push({0, startVertex});
    key[startVertex] = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        inMST[u] = true;

        for (int v = 0; v < numVertices; ++v) {
            if (IadjacencyMatrix[u][v] && !inMST[v] && IadjacencyMatrix[u][v] < key[v]) {
                parent[v] = u;
                key[v] = IadjacencyMatrix[u][v];
                pq.push({key[v], v});
            }
        }
    }

    // 构建并返回MST，表示为边的顶点对
    std::vector<std::pair<int, int>> mstEdges;
    for (int i = 0; i < numVertices; ++i) {
        if (i != startVertex) {
            mstEdges.emplace_back(parent[i], i);
        }
    }
    return mstEdges;
}

//  最小生成树按钮
void Widget::on_pushButton_5_clicked()
{
    if (IvertexIndex.empty() || IvertexNames.empty())
    {
        QMessageBox::warning(this, "文件", "请先读取文件!!!");
        return;
    }
    std::string begin = ui->comboBox->currentText().toStdString();
    // 执行Prim算法得到最小生成树
    std::vector<std::pair<int, int>> mstEdges = primMST(IvertexIndex[begin]);

    ui->textBrowser_2->clear();
    QTextCursor cursor(ui->textBrowser_2->document());
    cursor.movePosition(QTextCursor::End);
    // 输出最小生成树的信息
    cursor.insertText("最小生成树:");
    cursor.insertText("\n");
    int totalWeight = 0;
    for (const auto& edge : mstEdges) {
        int u = edge.first;
        int v = edge.second;
        int weight = IadjacencyMatrix[u][v];

        cursor.insertText("边: ");
        cursor.insertText(QString::fromStdString(IvertexNames[u]));
        cursor.insertText(" - ");
        cursor.insertText(QString::fromStdString(IvertexNames[v]));
        cursor.insertText(" 权值: ");
        cursor.insertText(QString::number(weight));
        cursor.insertText("\n");
        totalWeight += weight;
    }
    cursor.insertText("总长: ");
    cursor.insertText(QString::number(totalWeight));
    cursor.insertText("\n");
}

//  文件读取
void Widget::on_pushButton_8_clicked()
{
    str = QFileDialog::getOpenFileName(this, "选择文件", QDir::homePath(), "文本文档 (*.txt)").toStdString();

    AdjacencyMatrix adjM(str);
    auto [vertexIndex, vertexNames] = adjM.getNameIndexMap();

    IvertexIndex = vertexIndex;
    IvertexNames = vertexNames;
    if (!IvertexIndex.empty() && !IvertexNames.empty())
    {
        IadjacencyMatrix = adjM.getAdjacencyMatrix();

        auto [temp1,temp2] = adjM.getfloydWeightMatrix();
        distanceMatrix = temp1;

        AdjacencyList adjL(IadjacencyMatrix, vertexNames);

        IadjacencyList = adjL.adjacencyList_;

        //  添加数据
        ui->comboBox->clear();
        ui->comboBox_2->clear();
        for (const auto& i : vertexNames)
        {
            ui->comboBox->addItem(QString::fromStdString(i));
            ui->comboBox_2->addItem(QString::fromStdString(i));
        }
    }
}

//  景点介绍
void Widget::on_pushButton_4_clicked()
{
    ui->textBrowser->clear();
    QTextCursor cursor(ui->textBrowser->document());
    cursor.movePosition(QTextCursor::End);

    cursor.insertText("景点介绍：\n");

    cursor.insertText(
"        欢乐谷大门：欢乐谷入口，各种演出、餐饮，游客服务中心也在这\n\
        甜品王国：主要面向儿童，有热门饼干警长IP\n\
        欢乐时光：以马戏团和嘉年华为背景的主题乐园\n\
        极速世界：最富有速度刺激的园区\n\
        羽落天堂：水杉湿地生态园区\n\
        渔光岛：有东湖塔，是远眺东湖的制高点\n\
        飓风湾：以美洲海滩为主题的乐园，水上项目聚集地\n\
        欢乐江城：荆楚文化背景主题乐园\n");
}

//  起点到终点最短路径
void Widget::on_pushButton_9_clicked()
{
    if (IvertexIndex.empty() || IvertexNames.empty())
    {
        QMessageBox::warning(this, "文件", "请先读取文件!!!");
        return;
    }
    ui->textBrowser_2->clear();
    QTextCursor cursor(ui->textBrowser_2->document());
    cursor.movePosition(QTextCursor::End);

    int numVertices = IadjacencyList.size();

    std::string begin = ui->comboBox->currentText().toStdString();
    std::string end = ui->comboBox_2->currentText().toStdString();

    // 初始化距离数组和前一个顶点数组
    std::vector<int> distance(numVertices, std::numeric_limits<int>::max());
    std::vector<int> previous(numVertices, -1);

    int start = IvertexIndex[begin];
    int i = IvertexIndex[end];

    // 使用优先队列来实现最小优先级队列，存储顶点和距离的pair
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;

    // 将起点插入队列，距离设置为0
    pq.push(std::make_pair(0, start));
    distance[start] = 0;

    while (!pq.empty()) {
        int current = pq.top().second;
        pq.pop();

        for (const auto& edge : IadjacencyList[current].edges) {
            int newDistance = distance[current] + edge.weight;

            // 如果找到更短的路径，更新距离数组和前一个顶点数组，将顶点加入队列
            if (newDistance < distance[edge.destination]) {
                distance[edge.destination] = newDistance;
                previous[edge.destination] = current;
                pq.push(std::make_pair(newDistance, edge.destination));
            }
        }
    }
    cursor.insertText("从" + QString::fromStdString(IvertexNames[start]) + "->");
    cursor.insertText(QString::fromStdString(IvertexNames[i]) + " 的距离为：");
    cursor.insertText(QString::number(distance[i]) + "\n路径为: ");
    printPath(start, i, previous);
    cursor.insertText("\n");
}

