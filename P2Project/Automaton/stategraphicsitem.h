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
    bool getStarting() const;
    void setFinal(bool);
    bool getFinal() const;
    State* getState() const;
};

#endif // STATEGRAPHICSITEM_H
