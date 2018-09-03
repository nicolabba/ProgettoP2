#include "mainwindow.h"
#include "QBoxLayout.h"
#include "statographicsitem.h"
#include "transizionegraphicsitem.h"
#include "nfa.h"
#include <QPushButton>
#include "statodialog.h"
#include <QMessageBox>
#include "transizionedialog.h"

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent){

    this->setStyleSheet("background-color: white");
    this->setWindowFlags( Qt::WindowTitleHint |  Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

    QHBoxLayout* layout = new QHBoxLayout();
    QVBoxLayout* checkLayout = new QVBoxLayout();
    QVBoxLayout* opLayout = new QVBoxLayout();
    view = new AutomaGraphicsView();

    layout->addLayout(checkLayout,1);
    layout->addWidget(view,2);
    layout->addLayout(opLayout,0);

    check = new QTextEdit(this);
    checkLayout->addWidget(check,0);

    view->changeType(AutomaGraphicsView::AutomaType::NFA);
    view->addStato("q0");
    view->addStato("q1");
    view->addStato("q2");
    view->setStartingState("q0");
    view->addTransizione("q0","q1",'1');
    view->addTransizione("q1","q2",'2');
    view->addTransizione("q1","q2",'3');
    view->addTransizione("q1","q2",'4');
    view->removeTransizione("q1","q2",'2');
    view->setFinal("q2",true);
    //view->setBackgroundBrush(QColor(230, 200, 167));

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
    connect(settings,SIGNAL(pressed()),view,SLOT(editAutoma()));
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
                view->addStato(nome);
                if(win->getIniziale())
                    view->setStartingState(nome);
                if(win->getFinale())
                    view->setFinal(nome, true);
            }
        }
    }while(error);
    delete win;
}

void MainWindow::addTransizione()
{
    TransizioneDialog* win = new TransizioneDialog(this,Qt::WindowFlags(),view->getStatesName());
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

