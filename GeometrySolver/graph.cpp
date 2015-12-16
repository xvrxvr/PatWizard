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

    edges.append({A, B});
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

list< list< geom_index> > Graph::cycleSearch()
{
    int *color = new int[n];

    for(int i = 0 ; i < n ; ++i)
    {
        for(int k = 0; k < n; ++k)
        {
            color[k] = 1;
        }

        list< geom_index >  cycle;


        cycle.push_back((unsigned int)i);
        return DFSCycle(i, i, edges, color, -1 , cycle);
    }
}

list< list<geom_index> >Graph::DFSCycle(geom_index u, geom_index endV, QVector<Edge> edges, int *color, int unavailible, list<geom_index> cycle)
{
    list<list <geom_index> > res;
    if (u != endV)
    {
        color[u] = 2;
    }
    else if( cycle.size() >= 2 )
    {
        res.push_back(cycle);
        return res;
    }
    for( int w = 0 ; w < edges.length() ; ++w)
    {
        if ( w == unavailible )
        {
            continue;
        }
        if ( color[edges.at(w).v2] == 1 && edges.at(w).v1 == u )
        {
            list<geom_index> cycleNEW(cycle);
            cycleNEW.push_back(edges.at(w).v2);
            DFSCycle(edges.at(w).v2, endV, edges, color, w, cycleNEW);
            color[edges.at(w).v2] = 1;
        }
        else if ( color[edges.at(w).v1] == 1 && edges.at(w).v1 == u )
        {
            list<geom_index> cycleNEW(cycle);
            cycleNEW.push_back(edges.at(w).v1);
            DFSCycle(edges.at(w).v1, endV, edges, color, w, cycleNEW);
            color[edges.at(w).v1] = 1;
        }
    }
}
bool compare(list<geom_index> list1, list<geom_index> list2){
    return(list1.size() > list2.size());
}


void Tree::BuildTreeCycle(list<list <geom_index> > allCycles){
    allCycles.sort(compare);
    list<Tree*> tree_elem;
    list<Tree*>::iterator itr = tree_elem.begin();
    list<list<geom_index> >::iterator itr_cyc = allCycles.end();
    tree_elem.push_back(this);
    for(int i = 0; i < allCycles.size(); i++)
    {
        advance(itr,1);
        for(int j = tree_elem.size() - 1 ; j >= 0; j++)
        {
            advance(itr_cyc,-1);
            if((*itr)->IsContain(*itr_cyc))
                (*itr)->AddVertex(*itr_cyc);
        }

    }



}
void Tree::AddVertex(list<geom_index> temp){
    Tree* newLeaf = new Tree(temp);
    sons.append(newLeaf);
    newLeaf->parent = this;
}

bool Tree::IsContain(list<geom_index> temp){
    int res = 0;
    list<geom_index>::iterator iter_cycle = cycle.begin();
    list<geom_index>::iterator iter_temp = temp.begin();
    if(cycle.size() >= temp.size())
        return false;
    for(int i = 0; i < cycle.size(); advance(iter_cycle,1), i++)
    {
        for(int j; j < temp.size() - 1; advance(iter_temp,1), j++)
        {
            if (*iter_cycle == *iter_temp)
                res += 1;
        }

    }
    if (res == temp.size())
        return true;
}

Tree::Tree(list<geom_index> top_cycle) {
//    for (int i = 0; i < n; ++i)
//    delete [] nodes[i];
    cycle = top_cycle;
    parent = NULL;
}

Tree::~Tree() {
    for (int i = 0; i < sons.length(); ++i)
    {
        sons.at(i)->~Tree();
        delete sons.at(i);
    }
}












