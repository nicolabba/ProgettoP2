#include "graphmain.h"
#include "punto.h"
#include <QStandardItemModel>
#include <QScrollBar>
#include <QPushButton>
#include <QBoxLayout>
#include <QHeaderView>
#include <QMessageBox>
#include <QMenu>

GraphMain::GraphMain(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout * layout = new QVBoxLayout();


    g = new Grafico();
    lineX = new QLineEdit();
    lineY = new QLineEdit();
    twTopData = new QTableView();
    twPoints = new QTableView();//x e y list table
    twPoints->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(twPoints , SIGNAL(customContextMenuRequested(QPoint)),
             SLOT(customMenuRequested(QPoint)));

    QStandardItemModel *model = new QStandardItemModel();
    model->setHorizontalHeaderLabels(QStringList{"X","Y"});
    twPoints->setModel(model);
    twPoints->verticalScrollBar()->setStyleSheet("QScrollBar,QScrollBar::up-arrow,QScrollBar::down-arrow,QScrollBar::add-line,QScrollBar::sub-line{background:#e8e8e8;border:none;} QScrollBar::handle{background:#86ff86;border:none;}");

    lineX->setValidator(new QDoubleValidator());
    lineY->setValidator(new QDoubleValidator());
    lineX->setPlaceholderText("insert x value here");
    lineY->setPlaceholderText("insert y value here");
    lineX->setStyleSheet("QLineEdit{height:30px;border:0px solid gray;selection-background-color: darkgray; background-color: #e6ffcc}");
    lineY->setStyleSheet("QLineEdit{height:30px;border:0px solid gray;selection-background-color: darkgray; background-color: #e6ffcc}");

    QPushButton *qtbadd = new QPushButton("+");
    qtbadd->setStyleSheet("QPushButton{height:26px;border:2px solid green;background-color:lightgreen}");
    connect(qtbadd,SIGNAL(clicked()),this,SLOT(qtbaddClick()));

    QHBoxLayout *upLay = new QHBoxLayout();
    upLay->setSpacing(5);
    upLay->addWidget(lineX,2);
    upLay->addWidget(lineY,2);
    upLay->addWidget(qtbadd,1);
    layout->addLayout(upLay);

    QHBoxLayout *dataLay = new QHBoxLayout(/*dataFrame*/);
    twTopData->setEditTriggers(QAbstractItemView::NoEditTriggers);
    twTopData->horizontalHeader()->setSectionsClickable(false);
    twTopData->verticalHeader()->setVisible(false);
    twTopData->setSelectionMode(QAbstractItemView::NoSelection);
    twTopData->setMaximumHeight(twTopData->verticalHeader()->height()*3 + twTopData->horizontalHeader()->height());
    twTopData->horizontalScrollBar()->setVisible(false);
    twTopData->setStyleSheet("QTableView{border:none;}");
    dataLay->addWidget(twTopData);
    layout->addLayout(dataLay);

    QHBoxLayout *botLay = new QHBoxLayout(/*botFrame*/);

    chart = new QCustomPlot();
    chart->addGraph();
    chart->xAxis->setLabel("x");
    chart->yAxis->setLabel("y");
    QPen* p = new QPen(QRgb(0x32CD32));
    p->setWidth(5);
    chart->graph(0)->setPen(*p);
    chart->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc,Qt::darkGreen,10));
    chart->graph(0)->setBrush(QBrush(QRgb(0xa6ff8c)));
    chart->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    //refreshGraph();
    twPoints->verticalHeader()->setVisible(false);
    twPoints->horizontalHeader()->setSectionsClickable(false);
    twPoints->setEditTriggers(QTableView::NoEditTriggers);

    twPoints->setStyleSheet("QTableView{background-color: white; selection-background-color: #c6ffac; selection-color:black; border: none;}");
    twPoints->horizontalScrollBar()->setVisible(false);
    twPoints->setSelectionBehavior( QAbstractItemView::SelectRows );
    twPoints->setSelectionMode( QAbstractItemView::SingleSelection );
    layout->addLayout(botLay);

    botLay->addWidget(chart,1);
    botLay->addWidget(twPoints);

    setLayout(/*mainLay*/layout);

    resize(850,500);
    setStyleSheet("GraphMain{background-color:white}");
}

GraphMain::~GraphMain()
{
    delete g;
    delete chart;
    delete lineX;
    delete lineY;
}

void GraphMain::qtbaddClick()
{
    double nx = lineX->text().toDouble(), ny = lineY->text().toDouble();
    if(g->insert(new Punto(nx,ny))){
        dynamic_cast<QStandardItemModel*>(twPoints->model())->
                appendRow(QList<QStandardItem*>{
                              new QStandardItem(QString::fromStdString(std::to_string(nx))),
                              new QStandardItem(QString::fromStdString(std::to_string(ny)))});
        refreshGraph();
        refreshTopTable();
        lineX->setText("");
        lineY->setText("");
    }
    else
    {
        QMessageBox * temp = new QMessageBox("Errore", "Non si puo' inserire un punto con coordinata x gia' presente",
                                             QMessageBox::Warning,
                                             QMessageBox::Ok,
                                             QMessageBox::NoButton,
                                             QMessageBox::NoButton,this);
        temp->show();
    }
}

void GraphMain::refreshGraph()
{
    list<Punto*>* l = g->clone();
    QVector<double> x(l->size()), y(l->size());
    if(l->size() != 0){
        list<Punto*>::iterator it = l->begin();
        int index = 0;

        while(it != l->end())
        {
            x[index] = (*it)->getX();
            y[index] = (*it)->getY();
            it++;
            index++;
        }
        double maxx = g->getMaxX() + 5 ;
        double minx = g->getMinX() - 5;
        double maxy = g->getMaxY() + 5;
        double miny = g->getMin()->getY() -5;
        chart->xAxis->setRange(minx, maxx);
        chart->yAxis->setRange(miny, maxy);
    }
    chart->graph(0)->setData(x,y);
    chart->replot();
}

void GraphMain::refreshTopTable()
{
    if(g->size() != 0){
        std::string result = std::to_string(g->getArea());
        QStandardItemModel *model = new QStandardItemModel(1,4);
        model->setHorizontalHeaderLabels(QStringList{"area","length","max","min"});
        QStandardItem *item = new QStandardItem(QString::fromStdString(result));
        model->setItem(0,0,item);
        result = std::to_string(g->getLenght());
        model->setItem(0,1,new QStandardItem(QString::fromStdString(result)));
        Punto* p = g->getMax();
        result = std::to_string(p->getX()).append(" , ").append(std::to_string(p->getY()));
        model->setItem(0,2,new QStandardItem(QString::fromStdString(result)));
        p = g->getMin();
        result = std::to_string(p->getX()).append(" , ").append(std::to_string(p->getY()));
        model->setItem(0,3,new QStandardItem(QString::fromStdString(result)));
        twTopData->setModel(model);
    }
    twTopData->setRowHeight(0,40);
    twTopData->setColumnWidth(0, (this->width()-20)/4);
    twTopData->setColumnWidth(1, (this->width()-20)/4);
    twTopData->setColumnWidth(2, (this->width()-20)/4);
    twTopData->setColumnWidth(3, (this->width()-20)/4);

}

void GraphMain::resizeEvent(QResizeEvent *event)
{
    refreshGraph();
    refreshTopTable();
    event->accept();
}

void GraphMain::qpointClick(QPointF p){
    QMessageBox *m = new QMessageBox();
    m->setText(QString::fromStdString(std::to_string(p.x()).append(std::to_string(p.y()))));
    m->show();
}

void GraphMain::customMenuRequested(QPoint pos){
    QMenu *menu=new QMenu(this);
    QAction *act1 = new QAction("Modifica", this);
    QAction *act2 = new QAction("Elimina", this);
    connect(act1, SIGNAL(triggered(bool)), this, SLOT(btModifica()));
    connect(act2, SIGNAL(triggered(bool)), this, SLOT(btElimina()));
    menu->setStyleSheet("QMenu::item::selected {background-color: lightgreen;}");

    menu->addAction(act1);
    menu->addAction(act2);
    menu->popup(twPoints->viewport()->mapToGlobal(pos));
}

void GraphMain::btModifica(){
    int r = twPoints->selectionModel()->currentIndex().row();
    QModelIndex index1 = twPoints->model()->index(r, 0, QModelIndex());
    QModelIndex index2 = twPoints->model()->index(r, 1, QModelIndex());
    auto mx = twPoints->model()->data(index1).toString();
    auto my = twPoints->model()->data(index2).toString();
    lineX->setText(mx);
    lineY->setText(my);
    g->remove(new Punto(mx.toDouble(), my.toDouble()));
    twPoints->model()->removeRow(r);
    refreshGraph();
    refreshTopTable();
}

void GraphMain::btElimina(){
    int r = twPoints->selectionModel()->currentIndex().row();
    QModelIndex index1 = twPoints->model()->index(r, 0, QModelIndex());
    QModelIndex index2 = twPoints->model()->index(r, 1, QModelIndex());
    auto mx = twPoints->model()->data(index1).toString().toDouble();
    auto my = twPoints->model()->data(index2).toString().toDouble();
    g->remove(new Punto(mx,my));
    twPoints->model()->removeRow(r);
    refreshGraph();
    refreshTopTable();
}

