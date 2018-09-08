#ifndef TRANSITIONGRAPHICSITEM_H
#define TRANSITIONGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include "transition.h"
#include "stategraphicsitem.h"

class TransitionGraphicsItem : public QGraphicsItem
{
public:
    std::list<Transition*>* transitions;
    StateGraphicsItem* from,* to;
    bool doubleTransition;

    TransitionGraphicsItem(Transition* = nullptr, StateGraphicsItem* = nullptr, StateGraphicsItem* = nullptr, bool = false);
    TransitionGraphicsItem(TransitionGraphicsItem&);
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void add(Transition*);
};

#endif // TRANSITIONGRAPHICSITEM_H
