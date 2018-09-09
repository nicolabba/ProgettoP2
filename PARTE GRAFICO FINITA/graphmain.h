#ifndef GRAPHMAIN_H
#define GRAPHMAIN_H

#include <QWidget>
#include "grafico.h"
#include "../qcustomplot/qcustomplot.h"
#include <QLineEdit>
#include <QTableView>


class GraphMain : public QWidget
{
    Q_OBJECT
public:
    explicit GraphMain(QWidget *parent = nullptr);
    ~GraphMain();

private slots:
   void qtbaddClick();
   void qpointClick(QPointF);
   void customMenuRequested(QPoint);
   void btModifica();
   void btElimina();

private:
    Grafico *g;
    QCustomPlot* chart;
    QLineEdit *lineX;
    QLineEdit *lineY;
    QTableView *twTopData;
    QTableView *twPoints;

    void refreshGraph();
    void refreshTopTable();
    void resizeEvent(QResizeEvent* = 0);
};

#endif // GRAPHMAIN_H
