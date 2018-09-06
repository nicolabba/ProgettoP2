#include "mainwidget.h"
#include <QBoxLayout>
#include <QPushButton>

#include "Automaton/automatonmain.h"
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    setStyleSheet("background-color: white");
    resize(200,100);

    QVBoxLayout * layout = new QVBoxLayout();

    QString buttonStyleSheet = "QPushButton{ background-color: #f0f0f0; border:none; height:35px } QPushButton:pressed{ background-color: #d0d0d0;}";

    QPushButton * sButton, * gButton, * aButton;
    sButton = new QPushButton("Stringhe",this);
    gButton = new QPushButton("Grafico",this);
    aButton = new QPushButton("Automa",this);

    sButton->setToolTip("Questo pulsante apre un editor di stringhe");
    gButton->setToolTip("Questo pulsante apre un editor di grafici");
    aButton->setToolTip("Questo pulsante apre un editor di automi");

    connect(sButton,SIGNAL(pressed()),this,SLOT(openStringEditor()));
    connect(gButton,SIGNAL(pressed()),this,SLOT(openGraphicEditor()));
    connect(aButton,SIGNAL(pressed()),this,SLOT(openAutomatonEditor()));

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

}

void MainWidget::openGraphicEditor()
{

}

void MainWidget::openAutomatonEditor()
{
    AutomatonMain* w = new AutomatonMain();
    w->show();
}
