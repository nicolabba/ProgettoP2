#include "mainwindow.h"
#include <QPushButton>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    this->setStyleSheet("background-color: white");
    this->setWindowFlags( Qt::WindowTitleHint |  Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    QVBoxLayout* layout = new QVBoxLayout();
    QHBoxLayout* opLayout = new QHBoxLayout();
    inpCont = new QScrollArea(this);
    inp = new Inputs(inpCont);
    inpCont->setWidget(inp);
    inpCont->setWidgetResizable(true);
    inpCont->setStyleSheet("border:none;");
    inpCont->verticalScrollBar()->setStyleSheet("QScrollBar,QScrollBar::up-arrow,QScrollBar::down-arrow,QScrollBar::add-line,QScrollBar::sub-line{background:#e8e8e8; border:none;} QScrollBar::handle{background:#86ff86;border:none;}");
    layout->setSpacing(0);
    opLayout->setSpacing(4);

    layout->addWidget(inpCont);
    stringhe = QList<Stringa*>();
    stringhe.append(new Stringa());
    activeInp = QList<bool>();
    activeInp.append(true);
    inp->refresh(stringhe,activeInp);
    //layout->addWidget(inp);
    connect(inp,SIGNAL(changed(int,QString,bool)),this,SLOT(updateStoredData(int,QString,bool)));

    QPushButton* addButton = new QPushButton("+",this);
    addButton->setToolTip("Aggiungi una riga di input");
    addButton->setStyleSheet("QPushButton{width:30; color:green; background: qlineargradient( x1:0 y1:0, x2:0 y2:1, stop:0 lightgreen, stop:1 white); border:none; margin-right:6}QToolTip{border:none; background-color:#f0f0f0}");
    connect(addButton,SIGNAL(pressed()),this,SLOT(addInput()));
    layout->addWidget(addButton,0,Qt::AlignTop|Qt::AlignRight);

    layout->addSpacing(15);
    layout->addLayout(opLayout,0);

    QString opStyleSheet = "QPushButton{ background-color: #f0f0f0; border:none; width:35px; height:35px } QToolTip{border:none; background-color:#f0f0f0}";
    QPushButton* remInpButton = new QPushButton("?",this);
    QPushButton* appendButton = new QPushButton("+", this);
    QPushButton* removeButton = new QPushButton("-", this);
    QPushButton* searchButton = new QPushButton("Q", this);
    QPushButton* splitButton = new QPushButton("Y", this);
    QPushButton* hashButton = new QPushButton("#", this);
    QPushButton* dupButton = new QPushButton("//", this);
    remInpButton->setToolTip("Rimuovi tutti gli input attivi");
    appendButton->setToolTip("Aggiungi la stringa sottostante a tutte le stringhe attive");
    removeButton->setToolTip("Rimuovi la stringa sottostante da tutte le stringhe attive");
    searchButton->setToolTip("Ricerca e seleziona dalle stringhe attive la stringa sottostante");
    splitButton->setToolTip("Divide le stringhe attive utilizzando come marker la stringa sottostante");
    hashButton->setToolTip("Genera un semplice codice hash per tutte le stringhe attive");
    dupButton->setToolTip("Duplica tutte le stringhe attive");
    connect(remInpButton,SIGNAL(pressed()),this,SLOT(removeInput()));
    connect(appendButton,SIGNAL(pressed()),this,SLOT(append()));
    connect(removeButton,SIGNAL(pressed()),this,SLOT(remove()));
    connect(searchButton,SIGNAL(pressed()),this,SLOT(search()));
    connect(splitButton,SIGNAL(pressed()),this,SLOT(split()));
    connect(hashButton,SIGNAL(pressed()),this,SLOT(hash()));
    connect(dupButton,SIGNAL(pressed()),this,SLOT(duplicate()));
    appendButton->setStyleSheet(opStyleSheet);
    remInpButton->setStyleSheet(opStyleSheet);
    removeButton->setStyleSheet(opStyleSheet);
    searchButton->setStyleSheet(opStyleSheet);
    hashButton->setStyleSheet(opStyleSheet);
    splitButton->setStyleSheet(opStyleSheet);
    dupButton->setStyleSheet(opStyleSheet);
    opLayout->addStretch(1);
    opLayout->addSpacing(100);
    opLayout->addWidget(appendButton,0,Qt::AlignCenter);
    opLayout->addWidget(removeButton,0,Qt::AlignCenter);
    opLayout->addWidget(searchButton,0,Qt::AlignCenter);
    opLayout->addWidget(splitButton,0,Qt::AlignCenter);
    opLayout->addWidget(hashButton,0,Qt::AlignCenter);
    opLayout->addWidget(remInpButton,0,Qt::AlignCenter);
    opLayout->addWidget(dupButton,0,Qt::AlignCenter);
    opLayout->addSpacing(100);
    opLayout->addStretch(1);


    QLineEdit* opLine = new QLineEdit(this);
    opInput = Stringa();
    connect(opLine,SIGNAL(textEdited(QString)),this,SLOT(editOpInput(QString)));
    opLine->setStyleSheet("height: 30px; width: 234px; border: none; selection-background-color:darkgray; background-color: #c6ffac; margin-top:5px");
    layout->addWidget(opLine,0,Qt::AlignCenter | Qt::AlignHCenter);
    //layout->addStretch(1);

    setLayout(layout);
    refreshSize();
}

void MainWindow::updateStoredData(int index, QString value,bool active)
{
    stringhe[index] = new Stringa(value.toStdString());
    activeInp[index] = active;
}
void MainWindow::refreshSize()
{
    this->setFixedHeight(122 + (stringhe.size()<10?stringhe.size() : 10 )* 37);
}
void MainWindow::addInput()
{
    stringhe.append(new Stringa());
    activeInp.append(true);
    refreshSize();
    inp->refresh(stringhe,activeInp);
}

void MainWindow::removeInput()
{
    int eliminati = 0;
    for(int i = 0; i < inp->getEleNumber(); i++)
        if(stringhe.size() != 1)
        {
            if(activeInp[i-eliminati])
            {
                stringhe.removeAt(i-eliminati);
                activeInp.removeAt(i-eliminati);
                eliminati++;
            }
        }
        else
            if(activeInp[0])
            {
                stringhe[0] = new Stringa();

            }
    refreshSize();
    inp->refresh(stringhe,activeInp);
}
void MainWindow::append()
{
    for(int i = 0; i<stringhe.size(); i++)
    {
       if(activeInp[i])
           stringhe[i]->append(opInput);
    }
    inp->refresh(stringhe,activeInp);
}
void MainWindow::remove()
{
    for(int i = 0; i<stringhe.size(); i++)
    {
        if(activeInp[i])
            stringhe[i]->remove(opInput);
    }
    inp->refresh(stringhe,activeInp);
}
void MainWindow::search()
{
    int temp;
    for(int i = 0; i<stringhe.size(); i++)
    {
        if(activeInp[i])
        {
            temp = stringhe[i]->search(opInput);
            if(temp!=-1)
                inp->setSelection(i,temp,opInput.size());
        }
    }
}
void MainWindow::split()
{
    QList<Stringa *> res = QList<Stringa *>();
    QList<bool> res2 = QList<bool>();
    std::vector<Stringa> * temp = new std::vector<Stringa>();
    for(int i = 0; i<stringhe.size(); i++)
    {
        if(activeInp[i])
        {
            temp = new std::vector<Stringa>(stringhe[i]->split(opInput));
            for(unsigned int j = 0; j<temp->size(); j++)
            {
                res.append(&(*temp)[j]);
                res2.append(true);
            }
        }else
        {
            res.append(stringhe[i]);
            res2.append(false);
        }
    }
    stringhe = QList<Stringa *>(res);
    activeInp = QList<bool>(res2);
    inp->refresh(stringhe,activeInp);
    refreshSize();
}
void MainWindow::duplicate()
{
    QList<Stringa *> res = QList<Stringa *>();
    QList<bool> res2 = QList<bool>();
    for(int i = 0; i<stringhe.size(); i++)
    {

        res.append(stringhe[i]);
        res2.append(false);
        if(inp->getActive(i))
        {
            res.append(new Stringa(*(stringhe[i])));
            res2.append(true);
        }
    }
    stringhe = QList<Stringa *>(res);
    activeInp = QList<bool>(res2);
    inp->refresh(stringhe,activeInp);
    refreshSize();
}
void MainWindow::hash()
{
    for(int i = 0; i<stringhe.size(); i++)
    {
        if(inp->getActive(i))
            stringhe[i] = new Stringa(std::to_string(stringhe[i]->hash()));
    }
    inp->refresh(stringhe,activeInp);
}
void MainWindow::editOpInput(QString s)
{
    opInput = Stringa(s.toStdString());
}
MainWindow::~MainWindow()
{
}
