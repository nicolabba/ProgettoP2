#include "automagraphicsview.h"
#include "dfa.h"
#include "nfa.h"
#include "pda.h"
#include <QResizeEvent>
#include <QGraphicsItem>
#include "statodialog.h"
#include <QMessageBox>
#include "transizionedialog.h"


AutomaGraphicsView::AutomaGraphicsView(QWidget *parent, AutomaGraphicsView::AutomaType type, std::string alphabet, char epsilon) : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    automa = nullptr;
    reset(type,alphabet,epsilon);
    setScene(scene);
}

AutomaGraphicsView::AutomaType AutomaGraphicsView::getCurrentType() const
{
    return currentType;
}



void AutomaGraphicsView::addStato(const std::string & nome, bool finale, bool iniziale, int left, int top)
{
    FA* a;
    class PDA* b;
    switch(currentType)
    {
    case NFA:
    case DFA:
        a = dynamic_cast<FA*>(automa);
        a->addStato(nome,finale);
        stati.push_back(new StatoGraphicsItem(a->getStato(nome)));
        break;
    case PDA:
        b = static_cast<class PDA*>(automa);
        b->addStato(nome, finale);
        stati.push_back(new StatoGraphicsItem(b->getStato(nome)));
        break;
    }
    scene->addItem(stati.last());
    stati.last()->moveBy(left,top);
    if(iniziale)
        setStartingState(nome);
}

void AutomaGraphicsView::removeStato(const std::string & nome)
{

    FA* a;
    class PDA* b;
    Stato* temp;
    switch(currentType)
    {
    case NFA:
    case DFA:
        a = dynamic_cast<FA*>(automa);
        temp = a->getStato(nome);
        break;
    case PDA:
        b = static_cast<class PDA*>(automa);
        temp = b->getStato(nome);
        break;
    }
    if(temp)
    {
        for(int i = 0; i < transizioni.length(); i++)
        {
            if(transizioni.at(i)->da->getStato() == temp || transizioni.at(i)->a->getStato() == temp)
            {
                scene->removeItem(transizioni.at(i));
                transizioni.remove(i);
                i--;
            }
        }
        int index = -1;
        for(int i = 0; i < stati.length(); i++)
        {
            if(stati.at(i)->getStato() == temp)
                index = i;
        }
        if(index != -1)
        {
            scene->removeItem(stati.at(index));
            stati.remove(index);
        }
    }
    automa->removeStato(nome);
}


void AutomaGraphicsView::setStartingState(const std::string & nome)
{
    automa->setStartingState(nome);
    for(QVector<StatoGraphicsItem*>::iterator i = stati.begin(); i != stati.end(); i++)
    {
        if((*i)->getStato()->getNome() == nome)
            (*i)->setIniziale(true);
        else if((*i)->getIniziale())
            (*i)->setIniziale(false);

    }
}

void AutomaGraphicsView::setFinal(const std::string & nome, bool val)
{
    FA* a;
    class PDA* b;
    Stato* temp;
    switch(currentType)
    {
    case NFA:
    case DFA:
        a = dynamic_cast<FA*>(automa);
        temp = a->getStato(nome);
        break;
    case PDA:
        b = static_cast<class PDA*>(automa);
        temp = b->getStato(nome);
        break;
    }
    temp->setFinale(val);
//    for(QVector<StatoGraphicsItem*>::iterator i = stati.begin(); i != stati.end(); i++)
//    {
//        if((*i)->getStato()->getNome() == nome)
//            (*i)->setFinale(val);
//    }
}

std::list<std::string>* AutomaGraphicsView::getStatesName() const
{
    std::list<std::string>* ret = new std::list<std::string>();
    for(QVector<StatoGraphicsItem*>::ConstIterator i = stati.begin(); i != stati.end(); i++)
    {
        ret->push_back((*i)->getStato()->getNome());
    }
    return ret;
}

std::string AutomaGraphicsView::getAlphabet() const
{
    class DFA* temp;
    if(currentType == DFA)
    {
        temp = dynamic_cast<class DFA*>(automa);
        return temp->getAlfabeto();
    }
    else
        return "";
}

char AutomaGraphicsView::getEpsilon() const
{
    class NFA* tempN;
    class PDA* tempP;
    if(currentType == NFA)
    {
        tempN = dynamic_cast<class NFA*>(automa);
        return tempN->getEpsilon();
    }
    if(currentType == PDA)
    {
        tempP = dynamic_cast<class PDA*>(automa);
        return tempP->getEpsilon();
    }
    return '\0';
}

void AutomaGraphicsView::setEpsilon(char val) const
{
    class NFA* tempN;
    class PDA* tempP;
    if(currentType == NFA)
    {
        tempN = dynamic_cast<class NFA*>(automa);
        tempN->setEpsilon(val);
    } else
        if(currentType == PDA)
        {
            tempP = dynamic_cast<class PDA*>(automa);
            tempP->setEpsilon(val);
        }
}

void AutomaGraphicsView::reset(AutomaGraphicsView::AutomaType type, std::string alphabet, char epsilon)
{
    scene->clear();
    transizioni.clear();
    stati.clear();
    delete automa;

    currentType = type;
    switch(type)
    {
    case NFA: automa = new class NFA(epsilon);
        break;
    case DFA: automa = new class DFA(alphabet);
        break;
    case PDA: automa = new class PDA(epsilon);
        break;
    }
}

void AutomaGraphicsView::update()
{
    QGraphicsView::update();
    scene->setSceneRect(rect());
    scene->update(sceneRect());
    setScene(scene);
}

bool AutomaGraphicsView::doesStatoExist(const std::string & nome) const
{
    FA* a;
    class PDA* b;
    bool ret;
    switch(currentType)
    {
    case NFA:
    case DFA:
        a = dynamic_cast<FA*>(automa);
        ret = a->getStato(nome);
        break;
    case PDA:
        b = static_cast<class PDA*>(automa);
        ret = b->getStato(nome);
        break;
    }
    return ret;
}

bool AutomaGraphicsView::doesTransizioneExist(const std::string & part, const std::string & arr) const
{
    bool ret = false;
    for(QVector<TransizioneGraphicsItem*>::ConstIterator i = transizioni.cbegin(); i!= transizioni.cend() && !ret; i++)
    {
        if((*i)->da->getStato()->getNome() == part && (*i)->a->getStato()->getNome() == arr)
            ret = true;
    }
    return ret;
}

void AutomaGraphicsView::mouseMoveEvent(QMouseEvent * me)
{
    QGraphicsView::mouseMoveEvent(me);
    update();
}

void AutomaGraphicsView::resizeEvent(QResizeEvent * re)
{
    QGraphicsView::resizeEvent(re);
    scene->setSceneRect(0, 0, re->size().width(), re->size().height());
}

void AutomaGraphicsView::removeTransizioni(const std::string & from, const std::string & to)
{
    TransizionePDA* temp;
    FA* a;
    class PDA* b;
    StatoFA* tempSFA;
    StatoPDA* tempSPDA;
    bool eliminato = false;
    switch(currentType)
    {
    case NFA:
    case DFA:
        a = dynamic_cast<FA*>(automa);
        tempSFA = a->getStato(from);
        for(QVector<TransizioneGraphicsItem*>::iterator i = transizioni.begin(); !eliminato && i != transizioni.end(); i++)
            if((*i)->da->getStato()->getNome() == from && (*i)->a->getStato()->getNome() == to)
            {
                for(std::list<Transizione*>::iterator j = (*i)->transizioni->begin(); j != (*i)->transizioni->end(); j++)
                {
                    tempSFA->remove(a->getStato(to),(*j)->getInput());
                    //(*i)->transizioni->remove(*j);
                }
                scene->removeItem(*i);
                transizioni.erase(i);
                eliminato = true;
            }
        break;
    case PDA:
        b = static_cast<class PDA*>(automa);
        tempSPDA = b->getStato(from);
        for(QVector<TransizioneGraphicsItem*>::iterator i = transizioni.begin(); !eliminato && i != transizioni.end(); i++)
            if((*i)->da->getStato()->getNome() == from && (*i)->a->getStato()->getNome() == to)
            {
                for(std::list<Transizione*>::iterator j = (*i)->transizioni->begin(); j != (*i)->transizioni->end(); j++)
                {
                    temp = dynamic_cast<TransizionePDA*>(*j);
                    tempSPDA->remove(b->getStato(to),temp->getInput(),temp->getHead(),temp->getNewHead());
                    //(*i)->transizioni->remove(*j);
                }
                scene->removeItem(*i);
                transizioni.erase(i);
                eliminato = true;
            }
        break;
    }
}

void AutomaGraphicsView::editAutoma()
{

}

void AutomaGraphicsView::removeSelected()
{
    bool found = false;
    for(QVector<StatoGraphicsItem*>::iterator i = stati.begin(); i != stati.end() && !found; i++)
    {
        if((*i)->isSelected())
        {
            found = true;
            std::string nome = (*i)->getStato()->getNome();
            for(QVector<TransizioneGraphicsItem*>::iterator j = transizioni.begin(); j != transizioni.end();)
            {
                if((*j)->da == (*i) || (*j)->a == (*i))
                {
                    (*j)->scene()->removeItem(*j);
                    j = transizioni.erase(j);

                }
                else j++;
            }
            automa->removeStato(nome);
            scene->removeItem(*i);
            stati.erase(i);

        }
    }
    for(QVector<TransizioneGraphicsItem*>::iterator i = transizioni.begin(); i != transizioni.end() && !found; i++)
    {
        if((*i)->isSelected())
        {
            found = true;
            removeTransizioni((*i)->da->getStato()->getNome(),(*i)->a->getStato()->getNome());
        }
    }
    update();
}

void AutomaGraphicsView::editSelected()
{
    bool found = false;
    for(QVector<StatoGraphicsItem*>::iterator i = stati.begin(); i != stati.end() && !found; i++)
    {
        if((*i)->isSelected())
        {
            found = true;
            Stato* attivo = (*i)->getStato();
            StatoDialog* win = new StatoDialog(this, Qt::WindowFlags(),QString::fromStdString(attivo->getNome()),automa->getStartingState() == attivo,attivo->isFinale());
            bool error;
            do
            {
                error = false;

                if(win->exec())
                {
                    std::string nome = win->getInput().toStdString();
                    if(attivo->getNome() != nome && doesStatoExist(nome))
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
                        attivo->rename(nome);
                        if(win->getIniziale())
                            setStartingState(nome);
                        if(win->getFinale())
                            setFinal(nome, true);
                    }
                }
            }while(error);
            delete win;
        }
    }
    for(QVector<TransizioneGraphicsItem*>::iterator i = transizioni.begin(); i != transizioni.end() && !found; i++)
    {
        if((*i)->isSelected())
        {
            found = true;
            //EDIT TRANSIZIONE
            QString inputs, heads, newHeads = "";
            TransizionePDA* tempPDA;
            for(std::list<Transizione*>::iterator j = (*i)->transizioni->begin(); j != (*i)->transizioni->end();)
            {
                inputs.append((*j)->getInput());
                if(currentType == AutomaType::PDA)
                {
                    tempPDA = dynamic_cast<TransizionePDA*>(*j);
                    heads.append(tempPDA->getHead());
                    newHeads.append(QString::fromStdString(tempPDA->getNewHead()));
                    if(j != (*i)->transizioni->end())
                    {
                        heads.append(",");
                        newHeads.append(",");
                    }
                }
                if(++j != (*i)->transizioni->end())
                    inputs.append(",");
            }
            TransizioneDialog* win = new TransizioneDialog(this,Qt::WindowFlags(),getStatesName(),currentType,(*i)->da->getStato()->getNome(),(*i)->a->getStato()->getNome(), inputs, heads, newHeads);
            bool error;
            do
            {
                error = false;
                if(win->exec())
                {
                    if(win->getInput()->front())
                    {
                        removeTransizioni((*i)->da->getStato()->getNome(),(*i)->a->getStato()->getNome());
                        std::list<char>::iterator i,h;
                        std::list<std::string>::iterator nh;
                        i = win->getInput()->begin();
                        h = win->getHead()->begin();
                        nh = win->getNewHead()->begin();
                        bool fine = false;
                        while(!fine)
                        {
                            addTransizione(win->getPartenza(), win->getArrivo(),*i,*h,*nh);
                            i++;
                            if(getCurrentType() == AutomaGraphicsView::AutomaType::PDA)
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
                    }else
                    {
                        QMessageBox * temp = new QMessageBox("Errore", "Una transizione deve avere almeno un input",
                                                             QMessageBox::Warning,
                                                             QMessageBox::Ok,
                                                             QMessageBox::NoButton,
                                                             QMessageBox::NoButton,this);
                        temp->exec();
                        error = true;
                    }
                }
            }while(error);
            delete win;
        }
    }
}

bool AutomaGraphicsView::check(const std::string &s) const
{
    return automa->start(s);
}

void AutomaGraphicsView::addTransizione(const std::string & from, const std::string & to, const char & input, const char & head, const std::string & newHead)
{
    Transizione *temp = nullptr;
    FA* a;
    class PDA* b;
    switch(currentType)
    {
    case NFA:
    case DFA:
        a = dynamic_cast<FA*>(automa);
        a->addTransizione(from,to,input);
        temp = a->getStato(from)->getTrans(a->getStato(to),input);
        break;
    case PDA:
        b = static_cast<class PDA*>(automa);
        b->addTransizione(from,to,input,head,newHead);
        temp = b->getStato(from)->getTrans(b->getStato(to),input,head,newHead);
        break;
    }
    if(temp)
    {
        StatoGraphicsItem* gFrom, *gTo;
        for(QVector<StatoGraphicsItem*>::iterator i = stati.begin(); i != stati.end(); i++)
        {
            if((*i)->getStato()->getNome() == from)
                gFrom = *i;
            if((*i)->getStato()->getNome() == to)
                gTo = *i;
        }
        if(doesTransizioneExist(gFrom->getStato()->getNome(), gTo->getStato()->getNome()))
        {
            for(QVector<TransizioneGraphicsItem*>::iterator i = transizioni.begin(); i!= transizioni.end(); i++)
                if((*i)->da == gFrom && (*i)->a == gTo)
                    (*i)->add(temp);
        }
        else
        {
            TransizioneGraphicsItem* tempT = new TransizioneGraphicsItem(temp,gFrom,gTo);
            for(QVector<TransizioneGraphicsItem*>::iterator i = transizioni.begin(); i!= transizioni.end(); i++)
                if((*i)->da == gTo && (*i)->a == gFrom)
                {
                    (*i)->doppia = true;
                    tempT->doppia = true;
                }
            transizioni.push_back(tempT);
            scene->addItem(tempT);
        }
    }
}

void AutomaGraphicsView::removeTransizione(const std::string & from, const std::string & to, const char & input, const char & head, const std::string & newHead)
{
    bool eliminato = false;
    Transizione* temp;
    FA* a;
    class PDA* b;
    StatoFA* tempSFA;
    StatoPDA* tempSPDA;
    switch(currentType)
    {
    case NFA:
    case DFA:
        a = dynamic_cast<FA*>(automa);
        tempSFA = a->getStato(from);
        temp = tempSFA->getTrans(a->getStato(to),input);
        for(QVector<TransizioneGraphicsItem*>::iterator i = transizioni.begin(); i != transizioni.end() && !eliminato; i++)
            if((*i)->da->getStato()->getNome() == from && (*i)->a->getStato()->getNome() == to)
                for(std::list<Transizione*>::iterator j = (*i)->transizioni->begin(); j != (*i)->transizioni->end() && !eliminato; j++)
                {
                    if(*j == temp)
                    {
                        (*i)->transizioni->remove(temp);
                        eliminato = true;
                    }
                    if((*i)->transizioni->empty())
                    {
                        scene->removeItem(*i);
                        transizioni.erase(i);
                    }
                }
        tempSFA->remove(a->getStato(to),input);
        break;
    case PDA:
        b = static_cast<class PDA*>(automa);
        tempSPDA = b->getStato(from);
        temp = tempSPDA->getTrans(b->getStato(to),input, head, newHead);
        for(QVector<TransizioneGraphicsItem*>::iterator i = transizioni.begin(); i != transizioni.end() && !eliminato; i++)
            if((*i)->da->getStato()->getNome() == from && (*i)->a->getStato()->getNome() == to)
                for(std::list<Transizione*>::iterator j = (*i)->transizioni->begin(); j != (*i)->transizioni->end() && !eliminato; j++)
                {
                    if(*j == temp)
                    {
                        (*i)->transizioni->remove(temp);
                        eliminato = true;
                    }
                    if((*i)->transizioni->empty())
                    {
                        scene->removeItem(*i);
                        transizioni.erase(i);
                    }
                }
        tempSPDA->remove(b->getStato(to),input,head,newHead);
        break;
    }
}

void AutomaGraphicsView::setAlfabetoDFA(const std::string & alphabet)
{
    if(currentType == DFA)
    {
        class DFA* a = dynamic_cast<class DFA*>(automa);
        a->setAlfabeto(alphabet);
    }
}
