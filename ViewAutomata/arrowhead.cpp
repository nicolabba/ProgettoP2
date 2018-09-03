#include "arrowhead.h"
#include <QTransform>
ArrowHead::ArrowHead(QPointF vertex, double rotation)
{
    QVector<QPointF>* punti = new QVector<QPointF>();
    punti->append(vertex);
    punti->append(QPointF(vertex.x() - 7, vertex.y() + 7));
    punti->append(QPointF(vertex.x() - 7, vertex.y() - 7));
    poly = new QPolygonF(*punti);
    *poly = QTransform().translate(vertex.x(), vertex.y())
                                .rotate(-rotation)
                                .translate(-vertex.x(), -vertex.y())
            .map(*poly);
}

QPolygonF &ArrowHead::getPoly() const
{
    return *poly;
}
