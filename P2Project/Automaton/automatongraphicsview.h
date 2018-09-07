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
    AutomatonGraphicsView(QWidget * = nullptr, AutomaType = NFA, const QString& = "", const QChar& = '&');
    AutomaType getCurrentType() const;
    bool check(const QString&) const;
    void addState(const QString&, bool = false, bool = false, int = 0, int = 0);
    void addTransition(const QString&, const QString&, const QChar&, const QChar& = '\0', const QString& = "");
    void removeState(const QString&);
    void removeTransition(const QString&, const QString&, const QChar&, const QChar& = '\0', const QString& = "");
    void update();
    bool doesStateExist(const QString&) const;
    bool doesTransitionExist(const QString&, const QString&) const;
    void setStartingState(const QString&);
    void setFinal(const QString&, bool);
    QList<QString> *getStatesNames() const;
    QString getAlphabet() const;
    char getEpsilon() const;
    void reset(AutomaType = NFA, const QString& = "", const QChar& = '&');
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
