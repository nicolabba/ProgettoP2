#ifndef STATOGRAPHICSITEM_H
#define STATOGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include "stato.h"

class StatoGraphicsItem : public QGraphicsItem
{
private:
    Stato* s;
    bool iniziale;
public:
    StatoGraphicsItem(Stato* = nullptr);
    StatoGraphicsItem(StatoGraphicsItem&);
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void setIniziale(bool value);
    bool getIniziale();
    void setFinale(bool value);
    bool getFinale();
    Stato* getStato();
};

#endif // STATOGRAPHICSITEM_H
