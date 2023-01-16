#include "maze.h"

maze::maze()
{

}
void maze::addNode(node node)
{
    _nodes.push_back(node);
}
QVector<node>& maze::getNodes()
{
    return _nodes;
}

void maze::createMaze(int size)
{
    int length = size -1;
    for(int y =0; y<= length; ++y )
    {
        for(int x=0; x<= length; ++x)
        {
            node n(x,y);
            int idx = y*size + x;
            n.addVertexID(idx);
            addNode(n);
        }
    }
}

void maze::updateMaze(const int size)
{
    QVector<node>& nodes = getNodes();
    int length = size -1;


    for(int y =0; y<= length; ++y )
    {
        for(int x=0; x<= length; ++x)
        {
            int idx = y*size + x;
            int left = x-1;
            int top  = y-1;
            int right = x+1;
            int bottom = y+1;


            QVector< int > adjVetex;
            QVector< edge > edgeVec;
            node& n = nodes[idx];
            int nodeId = n.getNodeId();
            int vidx = -1;

            if(left >= 0 && left <=length)
            {
                vidx = nodeId -1;
                adjVetex.push_back(vidx);
                edge weightedEdge(idx,vidx,1);
                edgeVec.push_back(weightedEdge);
            }

            if(right >= 0 && right <=length)
            {
                vidx = nodeId + 1;
                adjVetex.push_back(vidx);
                edge weightedEdge(idx,vidx,1);
                edgeVec.push_back(weightedEdge);
            }

            if(top >= 0 && top <=length)
            {
                vidx = nodeId - size;
                adjVetex.push_back(vidx);
                edge weightedEdge(idx,vidx,1);
                edgeVec.push_back(weightedEdge);
            }

            if(bottom >= 0 && bottom <=length)
            {
                vidx = nodeId + size;
                adjVetex.push_back(vidx);
                edge weightedEdge(idx,vidx,1);
                edgeVec.push_back(weightedEdge);
            }

            n.addEdged(adjVetex);
            n.addWeightedEdged(edgeVec);
        }
    }
}
int maze::getVertexBasedOnXY(int x,int y)
{
    int vertexId = -1;
    QVector<node>::iterator itr = _nodes.begin();

    while( itr != _nodes.end())
    {
        node n = *itr;

        if(n.getX() == x && n.getY() ==y)
        {
            vertexId = n.getVertexID();
            break;
        }
        itr++;
    }
    return vertexId;
}

QSet< edge > maze::getMazeEdge(const int size)
{
    QVector<node>& nodes = getNodes();
    int length = size -1;

    QSet< edge > edgeVec;
    for(int y =0; y< size; ++y )
    {
        int prev =0;

        for(int x=0; x< length ; ++x)
        {
            int idx = y*size + x;
            int idxv = x*size + y;

            edge weightedEdge(idx,idx+1,1);
            edgeVec.insert(weightedEdge);

            if( x ==0 )
            prev = idxv;

            if(x >0)
            {
                edge vEdge(idxv,prev,1);
                edgeVec.insert(vEdge);
                prev = idxv;
            }
        }

        edge vEdge(prev+size,prev,1);
        edgeVec.insert(vEdge);
    }
    return edgeVec;
}

int maze::getWeightOfExistingEdge(QVector<node> nodes, int currentNodeID, int nodeId)
{
    int retWeight = -1;
    node n = nodes[nodeId];

    QVector< edge >  wedges = n.getWeightedEdge();

    QVector< edge > ::iterator itr = wedges.begin();
    while(itr != wedges.end())
    {
        edge edge = *itr;

        if(edge._endVertex == currentNodeID &&
                edge._startVertex ==  nodeId  )
        {
            retWeight = edge._weight;
            break;
        }
        itr++;
    }
    return retWeight;
}
int maze::getWeight()
{
    return qrand()%100;
}
void maze::updateInnerMaze(const int size)
{
    QVector<node>& nodes = getNodes();
    float length = size -1;
    int offset = size -1;
    for(int y =0; y< length; ++y )
    {
        for(int x=0; x< length; ++x)
        {
            int idx = y*(size-1) + x;
            node& n = nodes[idx];
            float x1 = n.getX();
            float y1 = n.getY();
            float left = x1-1;
            float top  = y1-1;
            float right = x1+1;
            float bottom = y1+1;


            QVector< int > adjVetex;
            QVector< edge > edgeVec;
            int w = -1;

            int nodeId = n.getNodeId();
            int vidx = -1;

            if(left >= 0.5 && left <= (length - 0.5))
            {
                vidx = nodeId -1;
                adjVetex.push_back(vidx);

                w = getWeightOfExistingEdge(nodes, idx, vidx);
                if(w == -1)
                {
                    w = getWeight();
                }
                edge weightedEdge(idx,vidx,w);
                edgeVec.push_back(weightedEdge);
            }

            if(right >= 0.5 && right <= (length - 0.5))
            {
                vidx = nodeId + 1;
                adjVetex.push_back(vidx);
                w = getWeightOfExistingEdge(nodes, idx, vidx);
                if(w == -1)
                {
                    w = getWeight();
                }
                edge weightedEdge(idx,vidx,w);
                edgeVec.push_back(weightedEdge);
            }

            if(top >= 0.5 && top <=(length - 0.5))
            {
                vidx = nodeId - offset;
                adjVetex.push_back(vidx);
                w = getWeightOfExistingEdge(nodes, idx, vidx);
                if(w == -1)
                {
                    w = getWeight();
                }
                edge weightedEdge(idx,vidx,w);
                edgeVec.push_back(weightedEdge);
            }

            if(bottom >= 0.5 && bottom <=(length - 0.5))
            {
                vidx = nodeId + offset;
                adjVetex.push_back(vidx);
                w = getWeightOfExistingEdge(nodes, idx, vidx);
                if(w == -1)
                {
                    w = getWeight();
                }
                edge weightedEdge(idx,vidx,w);
                edgeVec.push_back(weightedEdge);
            }

            n.addEdged(adjVetex);
            n.addWeightedEdged(edgeVec);
        }
    }
}


void maze::createInnerMaze(int size)
{
    int length = size -2;
    for(int y =0; y<= length; ++y )
    {
        for(int x=0; x<= length; ++x)
        {
            float x1 = x + 0.5;
            float y1 = y + 0.5;
            node n(x1,y1);
            int idx = y*(size-1) + x;
            n.addVertexID(idx);
            addNode(n);
        }
    }
}

void maze::RemoveEdgeFromList(int sv,int ev,QSet<edge>& e)
{
    QSet< edge >::iterator itr = e.begin();
    while(itr != e.end())
    {
        edge  edge = *itr;

        //struct edge edgeRemoved(edge._endVertex,edge._startVertex);
        if( (edge._endVertex == ev &&
             edge._startVertex ==  sv) ||
             ((edge._endVertex == sv &&
               edge._startVertex ==  ev)  ))
        {
           struct edge edgeRemoved =  edge;
           e.remove(edgeRemoved);
           break;
        }
        itr++;
    }
}

bool maze::isthereanyEdge(node nodei, node nodej, int &edgeWeight,edge &e)
{
     QVector< edge > wedges = nodei.getWeightedEdge();

     edgeWeight = 99999;

     QVector< edge >::iterator itr = wedges.begin();
     while(itr != wedges.end())
     {
         edge  minedge = *itr;


         if( (minedge._endVertex == nodei.getVertexID() &&
              minedge._startVertex ==  nodej.getVertexID()) ||
              ((minedge._endVertex == nodej.getVertexID() &&
                minedge._startVertex ==  nodei.getVertexID())  ))
         {
             edgeWeight = minedge._weight;
             e = minedge;
             return true;
         }

         itr++;
     }
     return false;
}
QSet<edge> maze::runMST()
{

    maze MST;
    QSet<node> s1,s2;
    QSet<edge> t,e;
    int random = 15;
    QVector<node>& nodes = getNodes();
    int node_size= nodes.size();
    node initNode = nodes.at(random);
    s1.insert(initNode);
    QVector<bool> visited(node_size,0);
    visited[random] = true;

    int no_edge =0;
    while(no_edge < node_size-1 )
    {
        int min = 999999;

        for(int i=0; i<node_size; ++i )
        {
            if(visited[i])
            {
                for(int j=0; j<node_size; ++j )
                {
                    node nodei = nodes[i];
                    node nodej = nodes[j];
                    int weight = 99999;
                    struct edge edgeMin(0,0);
                    if(!visited[j] && isthereanyEdge(nodei,nodej,weight,edgeMin))
                    {
                        if(min > weight)
                        {
                            min = weight;
                            s1.insert(nodej);
                            t.insert(edgeMin);
                            visited[j] = true;
                            no_edge++;
                        }
                    }
                }
            }
        }
    }

    return t;
}
