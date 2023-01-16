#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include "maze.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    Ui::Dialog *ui;
protected:
    void paintEvent(QPaintEvent *e);

    void updateMaze(maze &m,const int size);

private slots:
    void on_pushButton_clicked();
};
#endif // DIALOG_H
