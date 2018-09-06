#ifndef STATEGRAPHICSITEM_H
#define STATEGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include "state.h"

class StateGraphicsItem : public QGraphicsItem
{
private:
    State* state;
    bool starting;
public:
    StateGraphicsItem(State* = nullptr);
    StateGraphicsItem(StateGraphicsItem&);
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void setStarting(bool);
    bool getStarting();
    void setFinal(bool);
    bool getFinal();
    State* getState();
};

#endif // STATEGRAPHICSITEM_H
