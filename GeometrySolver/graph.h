#ifndef GRAPH_H
#define GRAPH_H
#include "gr_object.h"
#include <QStack>

struct Node{
    geom_index host;
    uint32_t dindex;
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
        void addEdge(geom_index A, geom_index B, Constrain C);
        void DFS(geom_index , geom_index);
        //Depth first numbering
        void DFN(int root);
};


#endif // GRAPH_H
