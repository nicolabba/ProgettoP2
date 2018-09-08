#include "arrowhead.h"
#include <QTransform>
ArrowHead::ArrowHead(QPointF vertex, double rotation)
{
    QVector<QPointF>* vertices = new QVector<QPointF>();
    vertices->append(vertex);
    vertices->append(QPointF(vertex.x() - 7, vertex.y() + 7));
    vertices->append(QPointF(vertex.x() - 7, vertex.y() - 7));
    poly = new QPolygonF(*vertices);
    *poly = QTransform().translate(vertex.x(), vertex.y())
                                .rotate(-rotation)
                                .translate(-vertex.x(), -vertex.y())
            .map(*poly);
}

QPolygonF &ArrowHead::getPoly() const
{
    return *poly;
}
