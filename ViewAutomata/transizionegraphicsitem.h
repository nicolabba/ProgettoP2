#ifndef TRANSIZIONEGRAPHICSITEM_H
#define TRANSIZIONEGRAPHICSITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include "transizione.h"
#include "statographicsitem.h"

class TransizioneGraphicsItem : public QGraphicsItem
{
public:
    std::list<Transizione*>* transizioni;
    StatoGraphicsItem* da,* a;
    bool doppia;

    TransizioneGraphicsItem(Transizione* = nullptr, StatoGraphicsItem* = nullptr, StatoGraphicsItem* = nullptr, bool = false);
    TransizioneGraphicsItem(TransizioneGraphicsItem&);
    QRectF boundingRect() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    void add(Transizione*);
};

#endif // TRANSIZIONEGRAPHICSITEM_H
