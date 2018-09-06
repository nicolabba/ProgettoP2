#ifndef ARROWHEAD_H
#define ARROWHEAD_H

#include<QPolygonF>

class ArrowHead
{
    QPolygonF* poly;
public:
    ArrowHead(QPointF, double);
    QPolygonF& getPoly() const;
};

#endif // ARROWHEAD_H
