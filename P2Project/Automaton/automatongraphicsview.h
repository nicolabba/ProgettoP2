#ifndef AUTOMATONGRAPHICSVIEW_H
#define AUTOMATONGRAPHICSVIEW_H

#include <QGraphicsView>
#include "abstractautomaton.h"
#include "stategraphicsitem.h"
#include "transitiongraphicsitem.h"
#include <QVector>
#include <list>

class AutomatonGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    enum AutomaType
    {
        DFA,
        NFA,
        PDA
    };
    AutomatonGraphicsView(QWidget * = nullptr, AutomaType = NFA, QString = "", char = '&');
    AutomaType getCurrentType() const;
    bool check(QString) const;
    void addState(QString, bool = false, bool = false, int = 0, int = 0);
    void addTransition(QString, QString, QChar, QChar = '\0', QString = "");
    void removeState(QString);
    void removeTransition(QString, QString, QChar, QChar = '\0', QString = "");
    void setAlphabetDFA(QString);
    void update();
    bool doesStateExist(QString) const;
    bool doesTransitionExist(QString, QString) const;
    void setStartingState(QString);
    void setFinal(QString, bool);
    QList<QString> *getStatesNames() const;
    QString getAlphabet() const;
    char getEpsilon() const;
    void setEpsilon(char) const;
    void reset(AutomaType = NFA, QString = "", char = '&');
private:
    AutomaType currentType;
    AbstractAutomaton* automaton;
    QGraphicsScene* scene;
    QVector<StateGraphicsItem*> states;
    QVector<TransitionGraphicsItem*> transitions;
    void mouseMoveEvent(QMouseEvent*);
    void resizeEvent(QResizeEvent*);
    void removeTransitions(QString, QString);

public slots:
    void editAutomaton();
    void removeSelected();
    void editSelected();
};

#endif // AUTOMATONGRAPHICSVIEW_H
