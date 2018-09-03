#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qcustomplot.h>
#include <grafico.h>
#include <iostream>
#include <string.h>
#include <punto.h>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChartView>
#include <QScatterSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QValueAxis>

using namespace QtCharts;


MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    g = new Grafico();
    lineX = new QLineEdit();
    lineY = new QLineEdit();
    viewData = new QTableView();
    viewPoints = new QTableView();//x e y list table
    viewPoints->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(viewPoints, SIGNAL(customContextMenuRequested(QPoint)),
             SLOT(customMenuRequested(QPoint)));

    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(QStringList{"X","Y"});
    viewPoints->setModel(model);    
    viewPoints->verticalScrollBar()->setStyleSheet("QScrollBar,QScrollBar::up-arrow,QScrollBar::down-arrow,QScrollBar::add-line,QScrollBar::sub-line{background:#e8e8e8;border:none;} QScrollBar::handle{background:#86ff86;border:none;}");

    //TEXTBOX
    lineX->setValidator(new QDoubleValidator());
    lineY->setValidator(new QDoubleValidator());
    lineX->setPlaceholderText("insert x value here");
    lineY->setPlaceholderText("insert y value here");
    lineX->setStyleSheet("height:30px;border:0px solid gray;selection-background-color: darkgray; background-color: #e6ffcc");
    lineY->setStyleSheet("height:30px;border:0px solid gray;selection-background-color: darkgray; background-color: #e6ffcc");

    //BUTTON
    QPushButton *qtbadd = new QPushButton("+");
    qtbadd->setStyleSheet("height:26px;border:2px solid green;background-color:lightgreen");
    connect(qtbadd,SIGNAL(clicked()),this,SLOT(qtbaddClick()));

    //FIRST FRAME OF MAINLAYOUT
    QFrame *upFrame = new QFrame();
    QHBoxLayout *upLay = new QHBoxLayout();
    upLay->setSpacing(5);
    upLay->addWidget(lineX);
    upLay->addWidget(lineY);
    upLay->addWidget(qtbadd);
    upLay->setStretchFactor(lineX,2);
    upLay->setStretchFactor(lineY,2);
    upLay->setStretchFactor(qtbadd,1);
    upFrame->setLayout(upLay);

    //FRAME FOR DATA(Area,Min,Max, ecc..)
    QFrame *dataFrame = new QFrame();
    QHBoxLayout *dataLay = new QHBoxLayout(dataFrame);
    viewData->setEditTriggers(QAbstractItemView::NoEditTriggers);
    viewData->verticalHeader()->setVisible(false);
    viewData->setSelectionMode(QAbstractItemView::NoSelection);
    viewData->setMaximumHeight(viewData->verticalHeader()->height()*1.5 + viewData->horizontalHeader()->height());
    viewData->horizontalScrollBar()->setVisible(false);    
    viewData->setStyleSheet("border:none;");
    dataLay->addWidget(viewData);

    QFrame *botFrame = new QFrame();
    QHBoxLayout *botLay = new QHBoxLayout(botFrame);
    botLay->setSpacing(1);
    chart = new QChartView();
    chart->setRenderHint(QPainter::Antialiasing);       
    refresh();
    viewPoints->verticalHeader()->setVisible(false);
    viewPoints->setStyleSheet("border:none;");
    viewPoints->horizontalScrollBar()->setVisible(false);
    viewPoints->setColumnWidth(0,(this->width()-20)/8);
    viewPoints->setColumnWidth(1,(this->width()-20)/8);
    botLay->addWidget(chart);
    botLay->addWidget(viewPoints);
    botLay->setStretchFactor(viewPoints,1);
    botLay->setStretchFactor(chart,4);

    //MAIN LAYOUT
    QVBoxLayout *mainLay =  new QVBoxLayout();
    mainLay->setContentsMargins(0,0,0,0);
    mainLay->addWidget(upFrame);
    mainLay->addWidget(dataFrame);
    mainLay->addWidget(botFrame);
    mainLay->setStretchFactor(upFrame,1);
    mainLay->setStretchFactor(dataFrame,0.1);
    mainLay->setStretchFactor(botFrame,10);
    setLayout(mainLay);

    this -> setWindowTitle("Kalk");
    this -> resize(850,500);
    this -> setStyleSheet("background-color:white");
}

MainWindow::~MainWindow()
{
    delete g;
    delete chart;
    delete lineX;
    delete lineY;
}

void MainWindow::qtbaddClick()
{
    double nx = lineX->text().toDouble(), ny = lineY->text().toDouble();
    if(g->insert(Punto(nx,ny))){
        dynamic_cast<QStandardItemModel*>(viewPoints->model())->
                appendRow(QList<QStandardItem*>{
                              new QStandardItem(lineX->text()),new QStandardItem(lineY->text())
                          });
        refresh();
        refreshTable();
    }
}

void MainWindow::refresh()
{
    QChart* c = new QChart();
    QScatterSeries *ss = new QScatterSeries();
    connect(ss,SIGNAL(clicked(QPointF)),this,SLOT(qpointClick(QPointF)));
    QLineSeries *sl = new QLineSeries();
    QLineSeries *sl2 = new QLineSeries();
    ss->setMarkerShape(QScatterSeries::MarkerShapeCircle);
    ss->setMarkerSize(10);
    ss->setColor(QRgb(0x32CD32));
    list<Punto>* l = g->clone();
    auto it = l->begin();    

    double mx = 0, my = 0;
    while(it != l->end())
    {
        mx = it->getX();
        my = it->getY();        
        ss->append(mx,my);
        sl->append(mx,my);
        it++;
    }
    sl2->append(l->begin()->getX(),0);
    sl2->append(mx,0);
    QAreaSeries* as = new QAreaSeries(sl,sl2);
    as->setColor(QRgb(0xa6ff8c));   
    c->addSeries(as);    
    c->addSeries(ss);
    c->createDefaultAxes();
    double maxx = g->getMaxX() + 5 ;
    double minx = g->getMinX() - 5;
    double maxy = g->getMaxY() + 5;
    double miny = g->getMin()->getY() -5;
    c->axisX()->setMax(maxx);
    c->axisY()->setMax(maxy);
    c->axisX()->setMin(minx);
    c->axisY()->setMin(miny);
    c->legend()->hide();
    chart->setChart(c);  
}
void MainWindow::refreshTable()
{
    std::string result = std::to_string(g->getArea());
    QStandardItemModel *model = new QStandardItemModel(1,4);
    model->setHorizontalHeaderLabels(QStringList{"area","lenght","max","min"});
    QStandardItem *item = new QStandardItem(QString::fromStdString(result));
    model->setItem(0,0,item);
    result = std::to_string(g->getLenght());
    model->setItem(0,1,new QStandardItem(QString::fromStdString(result)));
    Punto* p = g->getMax();
    result = std::to_string(p->getX()).append(",").append(std::to_string(p->getY()));
    model->setItem(0,2,new QStandardItem(QString::fromStdString(result)));
    p = g->getMin();
    result = std::to_string(p->getX()).append(",").append(std::to_string(p->getY()));
    model->setItem(0,3,new QStandardItem(QString::fromStdString(result)));
    viewData->setModel(model);
    viewData->setColumnWidth(0, (this->width()-20)/4);
    viewData->setColumnWidth(1, (this->width()-20)/4);
    viewData->setColumnWidth(2, (this->width()-20)/4);
    viewData->setColumnWidth(3, (this->width()-20)/4);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{    
    refresh();
    refreshTable();
    event->accept();
}

void MainWindow::qpointClick(QPointF p){
    QMessageBox *m = new QMessageBox();
    m->setText(QString::fromStdString(std::to_string(p.x()).append(std::to_string(p.y()))));

    m->show();
}

void MainWindow::customMenuRequested(QPoint pos){
    QModelIndex index= viewPoints->indexAt(pos);

    QMenu *menu=new QMenu(this);
    menu->addAction(new QAction("Modifica", this));
    menu->addAction(new QAction("Elimina", this));
    menu->popup(viewPoints->viewport()->mapToGlobal(pos));
}
