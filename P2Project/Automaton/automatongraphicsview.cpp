#include "automatongraphicsview.h"
#include "dfa.h"
#include "nfa.h"
#include "pda.h"
#include <QResizeEvent>
#include <QGraphicsItem>
#include "statedialog.h"
#include "transitiondialog.h"
#include "settingsdialog.h"
#include <QMessageBox>


AutomatonGraphicsView::AutomatonGraphicsView(QWidget *parent, AutomatonGraphicsView::AutomaType type, const QString& alphabet, const QChar& epsilon) : QGraphicsView(parent)
{
    scene = new QGraphicsScene(this);
    automaton = nullptr;
    reset(type,alphabet,epsilon);
    setScene(scene);
}

AutomatonGraphicsView::AutomaType AutomatonGraphicsView::getCurrentType() const
{
    return currentType;
}



void AutomatonGraphicsView::addState(const QString &name, bool final, bool starting, int left, int top)
{
    FA* a;
    class PDA* b;
    std::string nameStd = name.toStdString();
    switch(currentType)
    {
    case NFA:
    case DFA:
        a = dynamic_cast<FA*>(automaton);
        a->addState(nameStd,final);
        states.push_back(new StateGraphicsItem(a->getState(nameStd)));
        break;
    case PDA:
        b = static_cast<class PDA*>(automaton);
        b->addState(nameStd, final);
        states.push_back(new StateGraphicsItem(b->getState(nameStd)));
        break;
    }
    scene->addItem(states.last());
    states.last()->moveBy(left,top);
    if(starting)
        setStartingState(name);
}

void AutomatonGraphicsView::removeState(const QString& name)
{

    FA* a;
    class PDA* b;
    State* temp;
    std::string nameStd = name.toStdString();
    switch(currentType)
    {
    case NFA:
    case DFA:
        a = dynamic_cast<FA*>(automaton);
        temp = a->getState(nameStd);
        break;
    case PDA:
        b = static_cast<class PDA*>(automaton);
        temp = b->getState(nameStd);
        break;
    }
    if(temp)
    {
        for(int i = 0; i < transitions.length(); i++)
        {
            if(transitions.at(i)->from->getState() == temp || transitions.at(i)->to->getState() == temp)
            {
                scene->removeItem(transitions.at(i));
                transitions.remove(i);
                i--;
            }
        }
        int index = -1;
        for(int i = 0; i < states.length(); i++)
        {
            if(states.at(i)->getState() == temp)
                index = i;
        }
        if(index != -1)
        {
            scene->removeItem(states.at(index));
            states.remove(index);
        }
    }
    automaton->removeState(nameStd);
}


void AutomatonGraphicsView::setStartingState(const QString& name)
{
    std::string nameStd = name.toStdString();
    automaton->setStartingState(nameStd);
    for(QVector<StateGraphicsItem*>::iterator i = states.begin(); i != states.end(); i++)
    {
        if((*i)->getState()->getName() == nameStd)
            (*i)->setStarting(true);
        else if((*i)->getStarting())
            (*i)->setStarting(false);

    }
}

void AutomatonGraphicsView::setFinal(const QString &name, bool val)
{
    FA* a;
    class PDA* b;
    State* temp;
    std::string nameStd = name.toStdString();
    switch(currentType)
    {
    case NFA:
    case DFA:
        a = dynamic_cast<FA*>(automaton);
        temp = a->getState(nameStd);
        break;
    case PDA:
        b = static_cast<class PDA*>(automaton);
        temp = b->getState(nameStd);
        break;
    }
    temp->setFinal(val);
}

QList<QString>* AutomatonGraphicsView::getStatesNames() const
{
    QList<QString>* ret = new QList<QString>();
    for(QVector<StateGraphicsItem*>::ConstIterator i = states.begin(); i != states.end(); i++)
    {
        ret->push_back(QString::fromStdString((*i)->getState()->getName()));
    }
    return ret;
}

QString AutomatonGraphicsView::getAlphabet() const
{
    class DFA* temp;
    if(currentType == DFA)
    {
        temp = dynamic_cast<class DFA*>(automaton);
        return QString::fromStdString(temp->getAlphabet());
    }
    else
        return "";
}

char AutomatonGraphicsView::getEpsilon() const
{
    class NFA* tempN;
    class PDA* tempP;
    if(currentType == NFA)
    {
        tempN = dynamic_cast<class NFA*>(automaton);
        return tempN->getEpsilon();
    }
    if(currentType == PDA)
    {
        tempP = dynamic_cast<class PDA*>(automaton);
        return tempP->getEpsilon();
    }
    return '\0';
}


void AutomatonGraphicsView::reset(AutomatonGraphicsView::AutomaType type, const QString& alphabet, const QChar& epsilon)
{
    scene->clear();
    transitions.clear();
    states.clear();
    delete automaton;

    currentType = type;
    switch(type)
    {
    case NFA: automaton = new class NFA(epsilon.toLatin1());
        break;
    case DFA: automaton = new class DFA(alphabet.toStdString());
        break;
    case PDA: automaton = new class PDA(epsilon.toLatin1());
        break;
    }
}

void AutomatonGraphicsView::update()
{
    QGraphicsView::update();
    scene->setSceneRect(rect());
    scene->update(sceneRect());
    setScene(scene);
}

bool AutomatonGraphicsView::doesStateExist(const QString& name) const
{
    std::string nameStd = name.toStdString();
    FA* a;
    class PDA* b;
    bool ret;
    switch(currentType)
    {
    case NFA:
    case DFA:
        a = dynamic_cast<FA*>(automaton);
        ret = a->getState(nameStd);
        break;
    case PDA:
        b = static_cast<class PDA*>(automaton);
        ret = b->getState(nameStd);
        break;
    }
    return ret;
}

bool AutomatonGraphicsView::doesTransitionExist(const QString& from, const QString& to) const
{
    std::string fromStd = from.toStdString();
    std::string toStd = to.toStdString();
    bool ret = false;
    for(QVector<TransitionGraphicsItem*>::ConstIterator i = transitions.cbegin(); i!= transitions.cend() && !ret; i++)
    {
        if((*i)->from->getState()->getName() == fromStd && (*i)->to->getState()->getName() == toStd)
            ret = true;
    }
    return ret;
}

void AutomatonGraphicsView::mouseMoveEvent(QMouseEvent * me)
{
    QGraphicsView::mouseMoveEvent(me);
    update();
}

void AutomatonGraphicsView::resizeEvent(QResizeEvent * re)
{
    QGraphicsView::resizeEvent(re);
    scene->setSceneRect(0, 0, re->size().width(), re->size().height());
}

void AutomatonGraphicsView::removeTransitions(QString from, QString to)
{
    std::string fromStd = from.toStdString();
    std::string toStd = to.toStdString();
    TransitionPDA* temp;
    FA* a;
    class PDA* b;
    StateFA* tempSFA;
    StatePDA* tempSPDA;
    bool deleted = false;
    switch(currentType)
    {
    case NFA:
    case DFA:
        a = dynamic_cast<FA*>(automaton);
        tempSFA = a->getState(fromStd);
        for(QVector<TransitionGraphicsItem*>::iterator i = transitions.begin(); !deleted && i != transitions.end(); i++)
            if((*i)->from->getState()->getName() == fromStd && (*i)->to->getState()->getName() == toStd)
            {
                for(std::list<Transition*>::iterator j = (*i)->transitions->begin(); j != (*i)->transitions->end(); j++)
                    tempSFA->remove(a->getState(toStd),(*j)->getInput());
                scene->removeItem(*i);
                transitions.erase(i);
                deleted = true;
            }
        break;
    case PDA:
        b = static_cast<class PDA*>(automaton);
        tempSPDA = b->getState(fromStd);
        for(QVector<TransitionGraphicsItem*>::iterator i = transitions.begin(); !deleted && i != transitions.end(); i++)
            if((*i)->from->getState()->getName() == fromStd && (*i)->to->getState()->getName() == toStd)
            {
                for(std::list<Transition*>::iterator j = (*i)->transitions->begin(); j != (*i)->transitions->end(); j++)
                {
                    temp = dynamic_cast<TransitionPDA*>(*j);
                    tempSPDA->remove(b->getState(toStd),temp->getInput(),temp->getHead(),temp->getNewHead());
                }
                scene->removeItem(*i);
                transitions.erase(i);
                deleted = true;
            }
        break;
    }
}

void AutomatonGraphicsView::editAutomaton()
{
    SettingsDialog* win = new SettingsDialog(this,Qt::WindowFlags(),currentType, getAlphabet(), QChar::fromLatin1(getEpsilon()));
    if(win->exec())
    {
        if(win->getType() != currentType)
        {
            reset(win->getType(), win->getAlphabet(), win->getEpsilon().toLatin1());
        }else
        {
            if(currentType == NFA)
            {
                class NFA* tempN = dynamic_cast<class NFA*>(automaton);
                tempN->setEpsilon(win->getEpsilon().toLatin1());
            } else
                if(currentType == PDA)
                {
                    class PDA* tempP = dynamic_cast<class PDA*>(automaton);
                    tempP->setEpsilon(win->getEpsilon().toLatin1());
                }
            else
                {
                    class DFA* a = dynamic_cast<class DFA*>(automaton);
                    a->setAlphabet(win->getAlphabet().toStdString());
                }
        }
    }
    delete win;
}

void AutomatonGraphicsView::removeSelected()
{
    bool found = false;
    for(QVector<StateGraphicsItem*>::iterator i = states.begin(); i != states.end() && !found; i++)
    {
        if((*i)->isSelected())
        {
            found = true;
            std::string name = (*i)->getState()->getName();
            for(QVector<TransitionGraphicsItem*>::iterator j = transitions.begin(); j != transitions.end();)
            {
                if((*j)->from == (*i) || (*j)->to == (*i))
                {
                    (*j)->scene()->removeItem(*j);
                    j = transitions.erase(j);

                }
                else j++;
            }
            automaton->removeState(name);
            scene->removeItem(*i);
            states.erase(i);

        }
    }
    for(QVector<TransitionGraphicsItem*>::iterator i = transitions.begin(); i != transitions.end() && !found; i++)
    {
        if((*i)->isSelected())
        {
            found = true;
            removeTransitions(QString::fromStdString((*i)->from->getState()->getName()),QString::fromStdString((*i)->to->getState()->getName()));
        }
    }
    update();
}

void AutomatonGraphicsView::editSelected()
{
    bool found = false;
    for(QVector<StateGraphicsItem*>::iterator i = states.begin(); i != states.end() && !found; i++)
    {
        if((*i)->isSelected())
        {
            found = true;
            State* active = (*i)->getState();
            StateDialog* win = new StateDialog(this, Qt::WindowFlags(),QString::fromStdString(active->getName()),automaton->getStartingState() == active,active->isFinal());
            bool error;
            do
            {
                error = false;

                if(win->exec())
                {
                    QString name = win->getInput();
                    if(active->getName() != name.toStdString() && doesStateExist(name))
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
                        active->rename(name.toStdString());
                        if(win->getStarting())
                            setStartingState(name);
                        if(win->getFinal())
                            setFinal(name, true);
                    }
                }
            }while(error);
            delete win;
        }
    }
    for(QVector<TransitionGraphicsItem*>::iterator i = transitions.begin(); i != transitions.end() && !found; i++)
    {
        if((*i)->isSelected())
        {
            found = true;
            //EDIT TRANSIZIONE
            QString inputs, heads, newHeads = "";
            TransitionPDA* tempPDA;
            for(std::list<Transition*>::iterator j = (*i)->transitions->begin(); j != (*i)->transitions->end();)
            {
                inputs.append((*j)->getInput());
                if(currentType == AutomaType::PDA)
                {
                    tempPDA = dynamic_cast<TransitionPDA*>(*j);
                    heads.append(tempPDA->getHead());
                    newHeads.append(QString::fromStdString(tempPDA->getNewHead()));
                    if(j != (*i)->transitions->end())
                    {
                        heads.append(",");
                        newHeads.append(",");
                    }
                }
                if(++j != (*i)->transitions->end())
                    inputs.append(",");
            }
            TransitionDialog* win = new TransitionDialog(this,Qt::WindowFlags(),getStatesNames(),currentType,
                                                         QString::fromStdString((*i)->from->getState()->getName()),
                                                         QString::fromStdString((*i)->to->getState()->getName()), inputs, heads, newHeads);
            bool error;
            do
            {
                error = false;
                if(win->exec())
                {
                    if(win->getInput()->size() > 0)
                    {
                        removeTransitions(QString::fromStdString((*i)->from->getState()->getName()),
                                          QString::fromStdString((*i)->to->getState()->getName()));

                        QList<QChar>::iterator h = win->getHead()->begin();
                        QList<QString>::iterator nh = win->getNewHead()->begin();
                        for(QList<QChar>::iterator i = win->getInput()->begin(); i != win->getInput()->end(); i++)
                        {
                            addTransition(win->getFrom(), win->getTo(),*i,*h,*nh);
                            if(currentType == AutomatonGraphicsView::AutomaType::PDA)
                            {
                                h++;
                                nh++;
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

bool AutomatonGraphicsView::check(const QString &s) const
{
    return automaton->start(s.toStdString());
}

void AutomatonGraphicsView::addTransition(const QString& from, const QString& to, const QChar& input, const QChar& head, const QString& newHead)
{
    std::string fromStd = from.toStdString();
    std::string toStd = to.toStdString();
    Transition *temp = nullptr;
    FA* a;
    class PDA* b;
    switch(currentType)
    {
    case NFA:
    case DFA:
        a = dynamic_cast<FA*>(automaton);
        a->addTransition(fromStd,toStd,input.toLatin1());
        temp = a->getState(fromStd)->getTrans(a->getState(toStd),input.toLatin1());
        break;
    case PDA:
        b = static_cast<class PDA*>(automaton);
        b->addTransition(fromStd,toStd,input.toLatin1(),head.toLatin1(),newHead.toStdString());
        temp = b->getState(fromStd)->getTrans(b->getState(toStd),input.toLatin1(),head.toLatin1(),newHead.toStdString());
        break;
    }
    if(temp)
    {
        StateGraphicsItem* gFrom, *gTo;
        for(QVector<StateGraphicsItem*>::iterator i = states.begin(); i != states.end(); i++)
        {
            if((*i)->getState()->getName() == fromStd)
                gFrom = *i;
            if((*i)->getState()->getName() == toStd)
                gTo = *i;
        }
        if(doesTransitionExist(QString::fromStdString(gFrom->getState()->getName()), QString::fromStdString(gTo->getState()->getName())))
        {
            for(QVector<TransitionGraphicsItem*>::iterator i = transitions.begin(); i!= transitions.end(); i++)
                if((*i)->from == gFrom && (*i)->to == gTo)
                    (*i)->add(temp);
        }
        else
        {
            TransitionGraphicsItem* tempT = new TransitionGraphicsItem(temp,gFrom,gTo);
            for(QVector<TransitionGraphicsItem*>::iterator i = transitions.begin(); i!= transitions.end(); i++)
                if((*i)->from == gTo && (*i)->to == gFrom)
                {
                    (*i)->doubleTransition = true;
                    tempT->doubleTransition = true;
                }
            transitions.push_back(tempT);
            scene->addItem(tempT);
        }
    }
}

void AutomatonGraphicsView::removeTransition(const QString& from, const QString& to, const QChar& input, const QChar& head, const QString& newHead)
{
    std::string fromStd = from.toStdString();
    std::string toStd = to.toStdString();
    bool deleted = false;
    Transition* temp;
    FA* a;
    class PDA* b;
    StateFA* tempSFA;
    StatePDA* tempSPDA;
    switch(currentType)
    {
    case NFA:
    case DFA:
        a = dynamic_cast<FA*>(automaton);
        tempSFA = a->getState(fromStd);
        temp = tempSFA->getTrans(a->getState(toStd),input.toLatin1());
        for(QVector<TransitionGraphicsItem*>::iterator i = transitions.begin(); i != transitions.end() && !deleted; i++)
            if((*i)->from->getState()->getName() == fromStd && (*i)->to->getState()->getName() == toStd)
                for(std::list<Transition*>::iterator j = (*i)->transitions->begin(); j != (*i)->transitions->end() && !deleted; j++)
                {
                    if(*j == temp)
                    {
                        (*i)->transitions->remove(temp);
                        deleted = true;
                    }
                    if((*i)->transitions->empty())
                    {
                        scene->removeItem(*i);
                        transitions.erase(i);
                    }
                }
        tempSFA->remove(a->getState(toStd),input.toLatin1());
        break;
    case PDA:
        b = static_cast<class PDA*>(automaton);
        tempSPDA = b->getState(fromStd);
        temp = tempSPDA->getTrans(b->getState(toStd),input.toLatin1(), head.toLatin1(), newHead.toStdString());
        for(QVector<TransitionGraphicsItem*>::iterator i = transitions.begin(); i != transitions.end() && !deleted; i++)
            if((*i)->from->getState()->getName() == fromStd && (*i)->to->getState()->getName() == toStd)
                for(std::list<Transition*>::iterator j = (*i)->transitions->begin(); j != (*i)->transitions->end() && !deleted; j++)
                {
                    if(*j == temp)
                    {
                        (*i)->transitions->remove(temp);
                        deleted = true;
                    }
                    if((*i)->transitions->empty())
                    {
                        scene->removeItem(*i);
                        transitions.erase(i);
                    }
                }
        tempSPDA->remove(b->getState(toStd),input.toLatin1(),head.toLatin1(),newHead.toStdString());
        break;
    }
}

