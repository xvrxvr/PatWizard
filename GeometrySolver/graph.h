#ifndef GRAPH_H
#define GRAPH_H
#include "gr_object.h"
#include <QStack>
#include <QList>
#include <list>

struct Node{
    geom_index host;
    uint32_t dindex;
    QVector< geom_index > successors;
    QVector< Constrain > constr;
    enum Options {
        Checkok = 0x1
    } flag;
};

struct Edge{
    geom_index v1, v2;
};


class Graph {
    private:
        int n;
        Node *nodes;
        QVector<Edge> edges;
    public:
        Graph(int size = 2);
        ~Graph();
        bool isConnected(Node, Node);//Is there in Node_1 Node_2?
        void addEdge(geom_index A, geom_index B, Constrain C);
        void DFS(geom_index , geom_index);
        //Depth first numbering
        void DFN(int root);
        list< list< geom_index> > cycleSearch();
        list< list< geom_index> > DFSCycle(geom_index u, geom_index endV, QVector<Edge>, int *color, int unavailible, list<geom_index> cycle);
};


#endif // GRAPH_H
