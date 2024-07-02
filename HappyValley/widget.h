#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QDebug>
#include "adjacencylist.h"
#include "adjacencymatrix.h"
#include <QTextStream>
#include<QMessageBox>
#include <QFileDialog>
#include <QCloseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    std::string str;

    //  邻接矩阵
    std::vector<std::vector<int>> IadjacencyMatrix;

    //  权值矩阵
    std::vector<std::vector<int>> distanceMatrix;

    //  邻接表
    std::vector<AdjacencyList::Vertex> IadjacencyList;

    std::vector<std::string> IvertexNames;

    std::unordered_map<std::string, int> IvertexIndex;

    void printPathsDFS(int current, int end, std::vector<bool>& visited, std::vector<int>& path) const;

    void dijkstra(int start) const;

    void printPath(int start, int end, const std::vector<int>& previous) const;

    std::vector<std::pair<int, int>> primMST(int startVertex);

    void closeEvent(QCloseEvent*);

signals:
    void testSignal(); //  定义信号

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_9_clicked();

private:
    Ui::Widget *ui;
};
#endif // WIDGET_H
