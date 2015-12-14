#include "graph.h"

Graph::Graph(int size) {
    int i;
    if (size < 2) n = 2;
    else n = size;
    nodes = new Node[n];
    for (i = 0; i < n; ++i)
    {
        nodes[i].host = n;
        //nodes[i] -- node corresponding to i^th shape in vector_of_shapes
    }
//    for (i = 0; i < n; ++i)
//        for (j = 0; j < n; ++j)
//            nodes[i][j] = QVector< Nodes>();
}



Graph::~Graph() {
//    for (int i = 0; i < n; ++i)
//    delete [] nodes[i];
    delete [] nodes;
}

void Graph::addEdge(Node A, Node B, Constrain C) {
    A.constr.append(C);
    A.successors.append(C.obj1);

    B.constr.append(C);
    A.successors.append(C.obj2);
}

bool Graph::isConnected(Node A, Node B) {
    bool res = false;
    for ( int i = 0; i <= B.constr.length(); ++i )
    {
        if ( B.constr.at(i).obj1 == A.host || B.constr.at(i).obj2 == A.host )
        {
            res = true;
            break;
        }

    }
    for ( int i = 0; i <= B.constr.length() && res; ++i )
    {
        if ( A.constr.at(i).obj1 == B.host || A.constr.at(i).obj2 == B.host )
        {
            break;
        }

    }

    return res;
}

void Graph::DFS(geom_index x, geom_index required)
{
    QStack<Node> stack;
    bool *visited = new bool[n+1];
    geom_index i;

    for ( i = 0; i <= n ; ++i )
    {
        visited[i] = false;
    }
    stack.push(nodes[x]);
    visited[x] = true;
    if( x == required )
        return;

    while( !stack.isEmpty() )
    {
        geom_index k = stack.pop().host;
        if ( k == required )
            break;

        for( i = n ; i >= 0 ; --i)
            if ( isConnected(nodes[k], nodes[i]) && !visited[i])
            {
                stack.push(nodes[i]);
                visited[i] == true;
            }
    }

    delete [] visited;
}
