#ifndef GRAPH_H
#define GRAPH_H
#include "gr_object.h"
#include <QStack>

struct Node{
    geom_index host;
    QVector< geom_index > successors;
    QVector< Constrain > constr;
    enum Options {
        Checkok = 0x1
    } flag;
};

class Graph {
    private:
        int n;
        Node *nodes;
    public:
        Graph(int size = 2);
        ~Graph();
        bool isConnected(Node, Node);//Is there in Node_1 Node_2?
        void addEdge(Node A, Node B, Constrain C);
        void DFS(geom_index , geom_index);
};


#endif // GRAPH_H
