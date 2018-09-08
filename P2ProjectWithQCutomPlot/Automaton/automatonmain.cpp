#include "automatonmain.h"
#include <QBoxLayout>
#include "stategraphicsitem.h"
#include "transitiongraphicsitem.h"
#include "nfa.h"
#include <QPushButton>
#include "statedialog.h"
#include <QMessageBox>
#include "transitiondialog.h"
#include "settingsdialog.h"

AutomatonMain::AutomatonMain(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("AutomatonMain{background-color: white;} QDialog{background-color: white;}");
    setWindowFlags( Qt::WindowTitleHint |  Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);
    resize(750,500);

    QHBoxLayout* layout = new QHBoxLayout();
    QVBoxLayout* checkLayout = new QVBoxLayout();
    QVBoxLayout* opLayout = new QVBoxLayout();
    view = new AutomatonGraphicsView();

    layout->addLayout(checkLayout,1);
    layout->addWidget(view,3);
    layout->addLayout(opLayout,0);

    check = new QTextEdit(this);
    check->setToolTip("Una volta terminato l'automa qui possono essere inserite le parole che dovra' controllare, ogni riga equivale ogni parola");
    connect(check,SIGNAL(textChanged()), this,SLOT(resetResults()));
    checkLayout->addWidget(check,0);

    QString opStyleSheet = "QPushButton{ background-color: #f0f0f0; border:none; width:35px; height:35px }";
    QPushButton* settings = new QPushButton("Sett.",this);
    QPushButton* addState = new QPushButton("+S",this);
    QPushButton* addTransition = new QPushButton("+T", this);
    QPushButton* editSelected = new QPushButton("Edit", this);
    QPushButton* removeSelected = new QPushButton("-", this);
    QPushButton* start = new QPushButton("Start", this);
    settings->setToolTip("Modifica le impostazioni dell'automa");
    addState->setToolTip("Aggiungi uno stato all'automa");
    addTransition->setToolTip("Aggiungi una transizione all'automa");
    editSelected->setToolTip("Modifica l'elemento selezionato");
    removeSelected->setToolTip("Rimuovi l'elemento selezionato");
    start->setToolTip("Avvia l'automa utilizzando le parole nella casella di testo a sinistra come input");
    connect(settings,SIGNAL(pressed()),view,SLOT(editAutomaton()));
    connect(addState,SIGNAL(pressed()),this,SLOT(addState()));
    connect(addTransition,SIGNAL(pressed()),this,SLOT(addTransition()));
    connect(editSelected,SIGNAL(pressed()),view,SLOT(editSelected()));
    connect(removeSelected,SIGNAL(pressed()),view,SLOT(removeSelected()));
    connect(start,SIGNAL(pressed()),this,SLOT(start()));
    settings->setStyleSheet(opStyleSheet);
    addState->setStyleSheet(opStyleSheet);
    addTransition->setStyleSheet(opStyleSheet);
    editSelected->setStyleSheet(opStyleSheet);
    removeSelected->setStyleSheet(opStyleSheet);
    start->setStyleSheet(opStyleSheet);
    //opLayout->addStretch(1);
    opLayout->addWidget(settings,1);
    opLayout->addWidget(addState,1);
    opLayout->addWidget(addTransition,1);
    opLayout->addWidget(editSelected,1);
    opLayout->addWidget(removeSelected,1);
    opLayout->addWidget(start,1);
    opLayout->addStretch(1);

    /*testing*/
    view->reset(AutomatonGraphicsView::AutomaType::PDA,"",'&');
    view->addState("s",false,true,50,100);
    view->addState("p",false,false,150,100);
    view->addState("q",false,false,250,100);
    view->addState("r",true,false,250,200);
    view->addTransition("s","p",'&','&',"Z");
    view->addTransition("p","p",'0','Z',"AZ");
    view->addTransition("p","p",'0','A',"AA");
    view->addTransition("p","q",'&','&',"&");
    view->addTransition("q","q",'1','A',"&");
    view->addTransition("q","r",'&','Z',"&");
    check->append("0011");
    this->start();
    /*testing*/

    setLayout(layout);
}

void AutomatonMain::start()
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
        if(view->check(*i))
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

void AutomatonMain::addState()
{
    StateDialog* win = new StateDialog(this);
    bool error;
    do
    {
        //win = new NewStatoDialog(this);
        error = false;

        if(win->exec())
        {
            if(view->doesStateExist(win->getInput()))
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
                view->addState(win->getInput(), win->getFinal(),win->getStarting(),50,50);
        }
    }while(error);
    delete win;
}

void AutomatonMain::addTransition()
{
    TransitionDialog* win = new TransitionDialog(this,Qt::WindowFlags(),view->getStatesNames(),view->getCurrentType(),view->getAlphabet());
    bool error;
    do
    {
        error = false;
        if(win->exec())
        {
            if(view->doesTransitionExist(win->getFrom(), win->getTo()))
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
                QList<QChar>::iterator h = win->getHead()->begin();
                QList<QString>::iterator nh = win->getNewHead()->begin();
                for(QList<QChar>::iterator i = win->getInput()->begin(); i != win->getInput()->end(); i++)
                {
                    view->addTransition(win->getFrom(), win->getTo(),*i,*h,*nh);
                    if(view->getCurrentType() == AutomatonGraphicsView::AutomaType::PDA)
                    {
                        h++;
                        nh++;
                    }
                }
            }
        }
    }while(error);
    delete win;
}

void AutomatonMain::resetResults()
{
    check->setExtraSelections(QList<QTextEdit::ExtraSelection>());
}


