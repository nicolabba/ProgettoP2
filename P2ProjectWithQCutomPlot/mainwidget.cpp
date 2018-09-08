#include "mainwidget.h"
#include <QBoxLayout>
#include <QPushButton>


MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{

    sm = new QList<StringMain*>();
    gm = new QList<GraphMain*>();
    am = new QList<AutomatonMain*>();

    setStyleSheet("MainWidget{background-color: white;}");
    setWindowFlags(Qt::WindowTitleHint |  Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    setFixedSize(200,150);

    QVBoxLayout * layout = new QVBoxLayout();

    QString buttonStyleSheet = "QPushButton{ background-color: #f0f0f0; border:none; height:35px } QPushButton:pressed{ background-color: #d0d0d0;}";

    QPushButton * sButton, * gButton, * aButton;
    sButton = new QPushButton("Stringhe",this);
    gButton = new QPushButton("Grafico",this);
    aButton = new QPushButton("Automa",this);

    sButton->setToolTip("Questo pulsante apre un editor di stringhe");
    gButton->setToolTip("Questo pulsante apre un editor di grafici");
    aButton->setToolTip("Questo pulsante apre un editor di automi");


    connect(sButton,SIGNAL(released()),this,SLOT(openStringEditor()));
    connect(gButton,SIGNAL(released()),this,SLOT(openGraphEditor()));
    connect(aButton,SIGNAL(released()),this,SLOT(openAutomatonEditor()));

    sButton->setStyleSheet(buttonStyleSheet);
    gButton->setStyleSheet(buttonStyleSheet);
    aButton->setStyleSheet(buttonStyleSheet);

    layout->addWidget(sButton);
    layout->addWidget(gButton);
    layout->addWidget(aButton);

    setLayout(layout);
}

MainWidget::~MainWidget()
{

}


void MainWidget::openStringEditor()
{
    sm->append(new StringMain());
    sm->last()->show();
}

void MainWidget::openGraphEditor()
{
    gm->append(new GraphMain());
    gm->last()->show();
}

void MainWidget::openAutomatonEditor()
{
    am->append(new AutomatonMain());
    am->last()->show();
}

void MainWidget::closeEvent(QCloseEvent *event)
{
    for(auto i = sm->begin(); i != sm->end(); i++)
        (*i)->close();
    for(auto i = gm->begin(); i != gm->end(); i++)
        (*i)->close();
    for(auto i = am->begin(); i != am->end(); i++)
        (*i)->close();
    delete sm;
    delete gm;
    delete am;
    QWidget::closeEvent(event);
}
