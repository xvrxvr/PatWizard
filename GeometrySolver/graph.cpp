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

void Graph::addEdge(geom_index A, geom_index B, Constrain C) {
    if (C.obj1 == B){
        nodes[A].successors.append(C.obj1);
        nodes[B].successors.append(C.obj2);
    }
    else {
        nodes[A].successors.append(C.obj2);
        nodes[B].successors.append(C.obj1);
    }
    nodes[B].constr.append(C);
    nodes[A].constr.append(C);
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
                visited[i] = true;
            }
    }

    delete [] visited;
}

void Graph::DFN(int root)
{
    geom_index i = 0, curr_num = 0;
    QStack<Node> stack;

    for ( i = 0 ; i <= n ; ++i )
    {
        nodes[i].dindex = 0;
    }

    stack.push(nodes[root]);
    nodes[root].dindex = curr_num++;


    while ( !stack.isEmpty() ) {
        geom_index k = stack.pop().host;
        nodes[k].dindex = curr_num++;

        for( i = 0 ; i < nodes[k].successors.length() ; ++i )
        {
            geom_index next = nodes[k].successors.at(i);
            if(nodes[next].dindex == 0)
            {
                stack.push(nodes[next]);
//                nodes[next].dindex == curr_num++;
            }
        }
    }

}
