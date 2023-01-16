#include "dialog.h"
#include "ui_dialog.h"
#include <QCoreApplication>
#include <QVector>
#include <QMap>
#include <QPair>
#include <QSet>
#include <QHash>
#include "maze.h"


#define MAZE_SIZE 15
struct Point
{
    double x;
    double y;
};



Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QPen linepen(Qt::red);

    painter.setPen(linepen);
    //painter.drawLine(10,10,100,100);

    maze m,im ;
    m.createMaze(MAZE_SIZE);
    im.createInnerMaze(MAZE_SIZE);
    m.updateMaze(MAZE_SIZE);
    im.updateInnerMaze(MAZE_SIZE);

    QSet<edge> t = im.runMST();

    QSet<edge>::iterator itr = t.begin();

    //QVector<QPointF> pointList;
    while( itr != t.end())
    {
        edge e = *itr;
        int s = e._startVertex;
        int end = e._endVertex;

        QVector<node>& nodes = im.getNodes();

        node startnode = nodes[s];
        node endNode =  nodes[end];

        Point p1, q1;

       p1.x = startnode.getX()*50.0 + 10.5;
       p1.y = startnode.getY()*50.0 + 10.5;

       q1.x =endNode.getX()*50.0 + 10.5;
       q1.y =endNode.getY()*50.0 + 10.5;
       painter.drawLine(p1.x,p1.y,q1.x,q1.y);

        itr++;

    }

    QPen linepenBlack(Qt::black);
    painter.setPen(linepenBlack);

    QVector<node>& outerNodes = m.getNodes();
    QSet< edge > outerEdge = m.getMazeEdge(MAZE_SIZE);



    QSet<edge>::iterator itr2 = t.begin();
    while( itr2 != t.end())
    {
        edge e = *itr2;
        int s = e._startVertex;
        int end = e._endVertex;

        QVector<node>& nodes = im.getNodes();

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
       else if(ydelta == -11)
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


    for(const edge& oEdge : outerEdge)
    {
        int node1Idx = oEdge._startVertex;
        int node2Idx = oEdge._endVertex;

        node n1 = outerNodes[node1Idx];
        node n2 = outerNodes[node2Idx];

        Point p1, q1;
        p1.x = n1.getX();
        p1.y = n1.getY();

        q1.x = n2.getX();
        q1.y = n2.getY();

        //               qDebug() <<"("<<p1.x<<","<<p1.y<<") "<<"("<<q1.x<<","<<q1.y<<")";
        //               qDebug() <<"("<<p2.x<<","<<p2.y<<") "<<"("<<q2.x<<","<<q2.y<<")";
        painter.drawLine(10+(p1.x)*50,10+(p1.y)*50,10+(q1.x)*50,10+(q1.y)*50);
    }


}

void Dialog::on_pushButton_clicked()
{
    update();
}
