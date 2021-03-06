#include "mainwindow.h"
#include "QBoxLayout.h"
#include "statographicsitem.h"
#include "transizionegraphicsitem.h"
#include "nfa.h"
#include <QPushButton>
#include "statodialog.h"
#include <QMessageBox>
#include "transizionedialog.h"
#include "settingsdialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent){

    this->setStyleSheet("background-color: white");
    this->setWindowFlags( Qt::WindowTitleHint |  Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    resize(750,500);

    QHBoxLayout* layout = new QHBoxLayout();
    QVBoxLayout* checkLayout = new QVBoxLayout();
    QVBoxLayout* opLayout = new QVBoxLayout();
    view = new AutomaGraphicsView();

    layout->addLayout(checkLayout,1);
    layout->addWidget(view,3);
    layout->addLayout(opLayout,0);

    check = new QTextEdit(this);
    connect(check,SIGNAL(textChanged()), this,SLOT(resetResults()));
    checkLayout->addWidget(check,0);

    QString opStyleSheet = "QPushButton{ background-color: #f0f0f0; border:none; width:35px; height:35px } QToolTip{border:none; background-color:#f0f0f0}";
    QPushButton* settings = new QPushButton("Sett.",this);
    QPushButton* addStato = new QPushButton("+S",this);
    QPushButton* addTransizione = new QPushButton("+T", this);
    QPushButton* editSelected = new QPushButton("Edit", this);
    QPushButton* removeSelected = new QPushButton("-", this);
    QPushButton* start = new QPushButton("Start", this);
    settings->setToolTip("Modifica le impostazioni dell'automa");
    addStato->setToolTip("Aggiungi uno stato all'automa");
    addTransizione->setToolTip("Aggiungi una transizione all'automa");
    editSelected->setToolTip("Modifica l'elemento selezionato");
    removeSelected->setToolTip("Rimuovi l'elemento selezionato");
    start->setToolTip("Avvia l'automa utilizzando le parole nella casella di testo a sinistra come input");
    connect(settings,SIGNAL(pressed()),this,SLOT(editAutoma()));
    connect(addStato,SIGNAL(pressed()),this,SLOT(addStato()));
    connect(addTransizione,SIGNAL(pressed()),this,SLOT(addTransizione()));
    connect(editSelected,SIGNAL(pressed()),view,SLOT(editSelected()));
    connect(removeSelected,SIGNAL(pressed()),view,SLOT(removeSelected()));
    connect(start,SIGNAL(pressed()),this,SLOT(start()));
    settings->setStyleSheet(opStyleSheet);
    addStato->setStyleSheet(opStyleSheet);
    addTransizione->setStyleSheet(opStyleSheet);
    editSelected->setStyleSheet(opStyleSheet);
    removeSelected->setStyleSheet(opStyleSheet);
    start->setStyleSheet(opStyleSheet);
    //opLayout->addStretch(1);
    opLayout->addWidget(settings,1);
    opLayout->addWidget(addStato,1);
    opLayout->addWidget(addTransizione,1);
    opLayout->addWidget(editSelected,1);
    opLayout->addWidget(removeSelected,1);
    opLayout->addWidget(start,1);
    opLayout->addStretch(1);

    //testing
    view->reset(AutomaGraphicsView::AutomaType::PDA,"",'e');
    view->addStato("s",false,true,50,100);
    view->addStato("p",false,false,150,100);
    view->addStato("q",false,false,250,100);
    view->addStato("r",true,false,250,200);
    view->addTransizione("s","p",'e','e',"Z");
    view->addTransizione("p","p",'0','Z',"AZ");
    view->addTransizione("p","p",'0','A',"AA");
    view->addTransizione("p","q",'e','e',"e");
    view->addTransizione("q","q",'1','A',"e");
    view->addTransizione("q","r",'e','Z',"Z");
    check->append("0011");
    this->start();
    //testing

    setLayout(layout);
}

MainWindow::~MainWindow()
{

}

void MainWindow::addStato()
{
    StatoDialog* win = new StatoDialog(this);
    bool error;
    do
    {
        //win = new NewStatoDialog(this);
        error = false;

        if(win->exec())
        {
            if(view->doesStatoExist(win->getInput().toStdString()))
            {
                QMessageBox * temp = new QMessageBox("Errore", "Esiste gia' uno stato con questo nome",
                                                     QMessageBox::Warning,
                                                     QMessageBox::Ok,
                                                     QMessageBox::NoButton,
                                                     QMessageBox::NoButton,this);
                temp->exec();
                error = true;
            }
            else
            {
                std::string nome = win->getInput().toStdString();
                view->addStato(nome, win->getFinale(),win->getIniziale(),50,50);
            }
        }
    }while(error);
    delete win;
}

void MainWindow::addTransizione()
{
    TransizioneDialog* win = new TransizioneDialog(this,Qt::WindowFlags(),view->getStatesName(),view->getCurrentType());
    bool error;
    do
    {
        error = false;
        if(win->exec())
        {
            if(view->doesTransizioneExist(win->getPartenza(), win->getArrivo()))
            {
                    QMessageBox * temp = new QMessageBox("Errore", "Questa transizione esiste gia', per aggiungere input modificare la transizione gia' esistente",
                                                         QMessageBox::Warning,
                                                         QMessageBox::Ok,
                                                         QMessageBox::NoButton,
                                                         QMessageBox::NoButton,this);
                    temp->exec();
                    error = true;
            }
            else
            {
                std::list<char>::iterator i,h;
                std::list<std::string>::iterator nh;
                i = win->getInput()->begin();
                h = win->getHead()->begin();
                nh = win->getNewHead()->begin();
                bool fine = false;
                while(!fine)
                {
                    view->addTransizione(win->getPartenza(), win->getArrivo(),*i,*h,*nh);
                    i++;
                    if(view->getCurrentType() == AutomaGraphicsView::AutomaType::PDA)
                    {
                        fine = i == win->getInput()->end() || h == win->getHead()->end() || nh == win->getNewHead()->end();
                        h++;
                        nh++;
                    }
                    else
                    {
                        fine = i == win->getInput()->end();
                    }
                }
            }
        }
    }while(error);
    delete win;
}

void MainWindow::editAutoma()
{
    SettingsDialog* win = new SettingsDialog(this,Qt::WindowFlags(),view->getCurrentType(), QString::fromStdString(view->getAlphabet()), QChar::fromLatin1(view->getEpsilon()));
    if(win->exec())
    {
        if(win->getType() != view->getCurrentType())
        {
            view->reset(win->getType(), win->getAlphabet().toStdString(), win->getEpsilon().toLatin1());
        }else
        {
            view->setEpsilon(win->getEpsilon().toLatin1());
            view->setAlfabetoDFA(win->getAlphabet().toStdString());
        }
    }
    delete win;
}

void MainWindow::resetResults()
{
    check->setExtraSelections(QList<QTextEdit::ExtraSelection>());
}

void MainWindow::start()
{

    QList<QTextEdit::ExtraSelection> extraSelections;
    QTextEdit::ExtraSelection selection;
    QStringList words = check->toPlainText().split('\n');
    QTextCursor cur = check->textCursor();
    cur.movePosition(QTextCursor::Start);
    for(QStringList::iterator i = words.begin(); i != words.end(); i++)
    {
        selection = QTextEdit::ExtraSelection();
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = cur;
        if(view->check((*i).toStdString()))
        {
            selection.format.setBackground(Qt::green);
        }else
        {
            selection.format.setBackground(Qt::red);
        }
        extraSelections.append(selection);
        cur.movePosition(QTextCursor::NextBlock);
    }
    check->setExtraSelections(extraSelections);
}

