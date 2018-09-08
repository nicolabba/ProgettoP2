#include "stringmain.h"
#include <QPushButton>
#include <QScrollBar>
#include <QLabel>

StringMain::StringMain(QWidget *parent) :
    QWidget(parent)
{
    resize(400,176);
    setStyleSheet("background-color: white");
    setWindowFlags( Qt::WindowTitleHint |  Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    QVBoxLayout* layout = new QVBoxLayout();
    QHBoxLayout* opLayout = new QHBoxLayout();

    inpCont = new QScrollArea(this);
    inp = new Inputs(inpCont);
    inpCont->setWidget(inp);
    inpCont->setWidgetResizable(true);
    inpCont->setStyleSheet("QScrollArea{border:none; background-color: white;}");
    inpCont->verticalScrollBar()->setStyleSheet("QScrollBar,QScrollBar::up-arrow,QScrollBar::down-arrow,QScrollBar::add-line,QScrollBar::sub-line{background:#e8e8e8; border:none;} QScrollBar::handle{background:#86ff86;border:none;}");
    layout->setSpacing(0);
    opLayout->setSpacing(4);

    QLabel* lblInput = new QLabel("Stringhe:",this);
    layout->addWidget(lblInput,0,Qt::AlignCenter);

    layout->addWidget(inpCont);
    myStrings = QList<MyString*>();
    myStrings.append(new MyString());
    activeInp = QList<bool>();
    activeInp.append(true);
    inp->refresh(myStrings,activeInp);
    //layout->addWidget(inp);
    connect(inp,SIGNAL(changed(int,QString,bool)),this,SLOT(updateStoredData(int,QString,bool)));

    QPushButton* addButton = new QPushButton("+",this);
    addButton->setToolTip("Aggiungi una riga di input");
    addButton->setStyleSheet("QPushButton{width:30; color:green; background: qlineargradient( x1:0 y1:0, x2:0 y2:1, stop:0 lightgreen, stop:1 white); border:none;}");
    connect(addButton,SIGNAL(pressed()),this,SLOT(addInput()));
    layout->addWidget(addButton,0,Qt::AlignTop|Qt::AlignRight);

    layout->addSpacing(15);
    layout->addLayout(opLayout,0);

    QString opStyleSheet = "QPushButton{ background-color: #f0f0f0; border:none; width:35px; height:35px }";
    QPushButton* remInpButton = new QPushButton("Delete",this);
    QPushButton* appendButton = new QPushButton("Add", this);
    QPushButton* removeButton = new QPushButton("Remove", this);
    QPushButton* searchButton = new QPushButton("Search", this);
    QPushButton* splitButton = new QPushButton("Split", this);
    QPushButton* hashButton = new QPushButton("Hash", this);
    QPushButton* dupButton = new QPushButton("Copy", this);
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
//    opLayout->addStretch(1);
//    opLayout->addSpacing(100);
    opLayout->addWidget(appendButton,1);
    opLayout->addWidget(removeButton,1);
    opLayout->addWidget(searchButton,1);
    opLayout->addWidget(splitButton,1);
    opLayout->addWidget(hashButton,1);
    opLayout->addWidget(remInpButton,1);
    opLayout->addWidget(dupButton,1);
//    opLayout->addSpacing(100);
//    opLayout->addStretch(1);


    QLineEdit* opLine = new QLineEdit(this);
    opInput = MyString();
    opLine->setToolTip("Se un'operazione richiede l'utilizzo di un'altra stringa per\nfunzionare (Add, Remove, Split) essa va inserita qui");
    connect(opLine,SIGNAL(textEdited(QString)),this,SLOT(editOpInput(QString)));
    opLine->setStyleSheet("QLineEdit{height: 30px; width: 234px; border: none; selection-background-color:darkgray; background-color: #c6ffac; margin-top:5px}");
    layout->addWidget(opLine,0);//,Qt::AlignCenter | Qt::AlignHCenter);
    //layout->addStretch(1);

    setLayout(layout);
    refreshSize();
}

void StringMain::updateStoredData(int index, const QString &value, bool active)
{
    myStrings[index] = new MyString(value.toStdString());
    activeInp[index] = active;
}
void StringMain::refreshSize()
{
    //start with 122 without label
    this->setFixedHeight(139 + (myStrings.size()<10?myStrings.size() : 10 )* 37);
}
void StringMain::addInput()
{
    myStrings.append(new MyString());
    activeInp.append(true);
    refreshSize();
    inp->refresh(myStrings,activeInp);
}

void StringMain::removeInput()
{
    int deleted = 0;
    for(int i = 0; i < inp->getEleNumber(); i++)
        if(myStrings.size() != 1)
        {
            if(activeInp[i-deleted])
            {
                myStrings.removeAt(i-deleted);
                activeInp.removeAt(i-deleted);
                deleted++;
            }
        }
        else
            if(activeInp[0])
            {
                myStrings[0] = new MyString();

            }
    refreshSize();
    inp->refresh(myStrings,activeInp);
}
void StringMain::append()
{
    for(int i = 0; i<myStrings.size(); i++)
    {
       if(activeInp[i])
           myStrings[i]->append(opInput);
    }
    inp->refresh(myStrings,activeInp);
}
void StringMain::remove()
{
    for(int i = 0; i<myStrings.size(); i++)
    {
        if(activeInp[i])
            myStrings[i]->remove(opInput);
    }
    inp->refresh(myStrings,activeInp);
}
void StringMain::search()
{
    int temp;
    for(int i = 0; i<myStrings.size(); i++)
    {
        if(activeInp[i])
        {
            temp = myStrings[i]->search(opInput);
            if(temp!=-1)
                inp->setSelection(i,temp,opInput.size());
        }
    }
}
void StringMain::split()
{
    QList<MyString *> res = QList<MyString *>();
    QList<bool> res2 = QList<bool>();
    std::vector<MyString> * temp = new std::vector<MyString>();
    for(int i = 0; i<myStrings.size(); i++)
    {
        if(activeInp[i])
        {
            temp = new std::vector<MyString>(myStrings[i]->split(opInput));
            for(unsigned int j = 0; j<temp->size(); j++)
            {
                res.append(&(*temp)[j]);
                res2.append(true);
            }
        }else
        {
            res.append(myStrings[i]);
            res2.append(false);
        }
    }
    myStrings = QList<MyString *>(res);
    activeInp = QList<bool>(res2);
    inp->refresh(myStrings,activeInp);
    refreshSize();
}
void StringMain::duplicate()
{
    QList<MyString *> res = QList<MyString *>();
    QList<bool> res2 = QList<bool>();
    for(int i = 0; i<myStrings.size(); i++)
    {

        res.append(myStrings[i]);
        res2.append(false);
        if(inp->getActive(i))
        {
            res.append(new MyString(*(myStrings[i])));
            res2.append(true);
        }
    }
    myStrings = QList<MyString *>(res);
    activeInp = QList<bool>(res2);
    inp->refresh(myStrings,activeInp);
    refreshSize();
}
void StringMain::hash()
{
    for(int i = 0; i<myStrings.size(); i++)
    {
        if(inp->getActive(i))
            myStrings[i] = new MyString(std::to_string(myStrings[i]->hash()));
    }
    inp->refresh(myStrings,activeInp);
}
void StringMain::editOpInput(const QString &s)
{
    opInput = MyString(s.toStdString());
}
