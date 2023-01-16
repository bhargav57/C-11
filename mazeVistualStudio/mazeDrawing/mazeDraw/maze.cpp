#include "maze.h"

/* Constructor */
maze::maze()
{

}
/* it adds node to the maze */
void maze::addNode(node node)
{
    _nodes.push_back(node);
}
/* it gets the node form the maze */
QVector<node>& maze::getNodes()
{
    return _nodes;
}

/* it create size X size grid , if size is 5 then it create an oute maze with
  Vid
  = 0      1        2        3        4
  (0,0)  (1,0)                      (4,0)
  *--------*--------*--------*--------*
  |        |        |        |        |
  |  5     |  6     |  7     |  8     |
  | (1,0)  |        |        |        |
  *--------*--------*--------*--------*
  |        |        |        |        |
  |        |        |        |        |
  |        |        |        |        |
  *--------*--------*--------*--------*
  |        |        |        |        |
  |        |        |        |        |
  |        |        |        |        |
  *--------*--------*--------*--------*
  |        |        |        |        |
  |        |        |        |        |
  |        |        |        |        |
  *--------*--------*--------*--------*
  *                                   vid = 24
  *                                   (4,4)


*/
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
/* insert edge to vector*/
void maze::insertEdgeToVector(int startIdx, int EndIdx, int weight,QVector< edge >&  edgeVec)
{
    edge weightedEdge(startIdx,EndIdx,weight);
    edgeVec.push_back(weightedEdge);
}

/* update maze individual node with connected edges and its weight, like current vertex has how many neighbour nodes
and their edges along with its weight*/
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
                insertEdgeToVector(idx,vidx,1,edgeVec);
            }

            if(right >= 0 && right <=length)
            {
                vidx = nodeId + 1;
                insertEdgeToVector(idx,vidx,1,edgeVec);
            }

            if(top >= 0 && top <=length)
            {
                vidx = nodeId - size;
                insertEdgeToVector(idx,vidx,1,edgeVec);
            }

            if(bottom >= 0 && bottom <=length)
            {
                vidx = nodeId + size;
                insertEdgeToVector(idx,vidx,1,edgeVec);
            }
            n.addWeightedEdged(edgeVec);
        }
    }
}
/* get the vertex based on the x, y cordinate */
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

/*gets the maze edge from the maze*/
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

/*To avoid duplicate weight of the same edge, the code search if the weight was already assigned and then use the same
weight, for example, edge 0,1 has weight 5 when the code calculates the neighbors of the vertex 0 then while
discovering the neighbors of the vertex 1 assign the same weight to edge 1,0.*/
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
/* get the weight*/
int maze::getWeight()
{
    return qrand()%100;
}


void maze::updateInnerMaze(const int size)
{
    QVector<node>& nodes = getNodes();
    float length = size -1;
    int offset   = size -1;
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
                insertEdgeToVector(idx,vidx,w,edgeVec);
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
                insertEdgeToVector(idx,vidx,w,edgeVec);
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
                insertEdgeToVector(idx,vidx,w,edgeVec);
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
                insertEdgeToVector(idx,vidx,w,edgeVec);
            }
            n.addWeightedEdged(edgeVec);
        }
    }
}
/* it  creates an inner grid with (size-1)X(size-1)

  vid= 0      1        2        3        4
  (0,0)  (1,0)                      (4,0)
  *--------*--------*--------*--------*    (inner maze id)
  |        |        |        |        |     Vid=0         1        2       3
  |  *-----|---*----|---*----|---*    |     (0.5,0.5) (1.5,0.5) (2.5,0.5)(3.5,0.5)
  |  |     |   |    |   |    |   |    |
  *--------*--------*--------*--------*      =4
  |  |     |   |    |   |    |   |    |     (0.5,1.5)
  |  *-----|---*----|---*----|---*    |
  |  |     |   |    |   |    |   |    |
  *--------*--------*--------*--------*
  |  |     |   |    |   |    |   |    |
  |  *-----|---*----|---*----|---*    |
  |  |     |   |    |   |    |   |    |
  *--------*--------*--------*--------*
  |  |     |   |    |   |    |   |    |
  |  *-----|---*----|---*----|---*    |                                   15
  |        |        |        |        |                                 (3.5,3.5)
  *--------*--------*--------*--------*
  *                                   vid = 24
  *                                   (4,4)


*/

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
/*remove an edge formt he set*/
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
/*checks that if there is an any edge between node/vertex i and j, if yes then returns true otherwise false.*/
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
/* run the minimum spannig tree algorithm for on the inner maze, and get the set if the edge which form the
minimum spanning tree */
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

/* now the code has minimum spanning tree for the inner maze in form of edge set inside variable t
outeredge represents the outer grid , this function removes the crossing edge of the MST and outergrid.*/
void maze::removeCrossingEdge(QSet<edge> t,QSet< edge >& outerEdge,maze m)
{
QSet<edge>::iterator itr2 = t.begin();
while( itr2 != t.end())
{
    edge e = *itr2;
    int s = e._startVertex;
    int end = e._endVertex;

    QVector<node>& nodes = getNodes();

    node startnode = nodes[s];
    node endNode =  nodes[end];

    Point p2, q2;

   p2.x =startnode.getX();
   p2.y =startnode.getY();

   q2.x =endNode.getX();
   q2.y =endNode.getY();


   float xdelta = 0, ydelta = 0;

   xdelta = q2.x - p2.x;
   ydelta = q2.y - p2.y;

   if (xdelta == 1)
   {
       int x = p2.x + 0.5;
       int y1 = p2.y - 0.5;
       int y2 = p2.y+0.5;
       int sv = m.getVertexBasedOnXY(x,y1);
       int ev = m.getVertexBasedOnXY(x,y2);
       m.RemoveEdgeFromList(sv,ev,outerEdge);
   }
   else if(xdelta == -1)
   {
       int x = q2.x + 0.5;
       int y1 = q2.y - 0.5;
       int y2 = q2.y+0.5;
       int sv = m.getVertexBasedOnXY(x,y1);
       int ev = m.getVertexBasedOnXY(x,y2);
       m.RemoveEdgeFromList(sv,ev,outerEdge);
   }
   else if(ydelta == 1)
   {
       int y = p2.y + 0.5;
       int x1 = p2.x - 0.5;
       int x2 = p2.x+0.5;
       int sv = m.getVertexBasedOnXY(x1,y);
       int ev = m.getVertexBasedOnXY(x2,y);
       m.RemoveEdgeFromList(sv,ev,outerEdge);
   }
   else if(ydelta == -1)
   {
       int y = q2.y + 0.5;
       int x1 = q2.x - 0.5;
       int x2 = q2.x+0.5;
       int sv = m.getVertexBasedOnXY(x1,y);
       int ev = m.getVertexBasedOnXY(x2,y);
       m.RemoveEdgeFromList(sv,ev,outerEdge);
   }

    itr2++;
}

}
