#ifndef MAZE_H
#define MAZE_H

#include <QVector>
#include <QMap>
#include <QPair>
#include <QSet>
#include <QHash>

/*Maze is represent as agraph structure, so vertex is point in terms of x,y cordination along with
vertex it , two vertexes connected with an edde wich has some weight associated with it */
struct Point
{
    double x;
    double y;
};

/* two vertexes connected with an edde wich has some weight associated with it */
struct edge{
    int _startVertex;
    int _endVertex;
    int _weight;
    edge(int s,int e,int w = -1):_startVertex(s),_endVertex(e),_weight(w)
    {

    }
    edge()
    {

    }
    bool operator==(const edge &other) const
    {
        return ((_startVertex == other._startVertex)&&
                (_endVertex == other._endVertex));
    }


};

inline uint qHash(const edge &e, uint seed = 0) {
    Q_UNUSED(seed)
    return ::qHash(e._startVertex);
}

/* vertexes of the graph are represented as a node */
class node
{
    float _x,_y; //(x,y)
    int   _v;    //vertex id
    QVector< edge >  _wEdge; // weighted edges
public:
    node()
    {

    }
    node(float i,float j):_x(i),_y(j)
    {

    }
    node(int id):_v(id)
    {

    }
    int getVertexID()
    {
        return _v;
    }
    void addVertexID(int vid)
    {
        _v = vid;
    }
    void addWeightedEdged(QVector< edge > we)
    {
        _wEdge = we;
    }
    int getNodeId() const
    {
        return _v;
    }
    float getX()
    {
        return _x;
    }
    float getY()
    {
        return _y;
    }
    QVector< edge > getWeightedEdge()
    {
        return _wEdge;
    }

    bool operator==(const node &other) const
    {
        return ((_v == other._v) &&
                (_x == other._x) &&
                (_y == other._y));
    }
};

inline uint qHash(const node &n, uint seed = 0) {
    Q_UNUSED(seed)
    return ::qHash(n.getNodeId());
}


/* Gropu of nodes make graph which is actually a maze representation */
class maze
{
    QVector<node> _nodes;
public:
    maze();

    void addNode(node node);

    QVector<node>& getNodes();

    void createMaze(int size);

    void updateMaze(const int size);

    int getWeightOfExistingEdge(QVector<node> nodes, int currentNodeID, int nodeId);

    int getWeight();

    void updateInnerMaze(const int size);

    void createInnerMaze(int size);

    QSet<edge> runMST();

    bool isthereanyEdge(node nodei, node nodej,int &edgeWeight,edge &e);

    QSet<edge> getMazeEdge(const int size);

    void RemoveEdgeFromList(int s,int end,QSet<edge>& e);

    int getVertexBasedOnXY(int x,int y);

    void removeCrossingEdge(QSet<edge> t, QSet< edge >& outerEdge, maze m);

    void insertEdgeToVector(int startIdx, int EndIdx, int weight, QVector<edge> &edgeVec);
};

#endif // MAZE_H