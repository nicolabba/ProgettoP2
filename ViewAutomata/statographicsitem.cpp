#include "statographicsitem.h"
#include "arrowhead.h"

StatoGraphicsItem::StatoGraphicsItem(Stato* stato):QGraphicsItem(), s(stato), iniziale(false)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

StatoGraphicsItem::StatoGraphicsItem(StatoGraphicsItem & st):QGraphicsItem(st.parentObject()), s(st.s), iniziale(st.iniziale)
{

}

QRectF StatoGraphicsItem::boundingRect() const
{
    return QRectF(0,0,50,50);
}

void StatoGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QPen pen = QPen(isSelected()?Qt::darkGreen : Qt::black,3);
    painter->setPen(pen);
    painter->drawEllipse(rect);
    painter->setFont(QFont("Arial",18));
    painter->drawText(rect, QString::fromStdString(s->getNome()), QTextOption(Qt::AlignCenter));
    if(s->isFinale())
        painter->drawEllipse(5,5,40,40);
    if(iniziale)
    {
        painter->setPen(QPen(Qt::black,3));
        QPainterPath path;
        path.addPolygon((new ArrowHead(QPointF(rect.left(),rect.top() + 25),0))->getPoly());
        path.closeSubpath();
        painter->drawPath(path);
        painter->fillPath(path, QBrush(Qt::black));
        painter->setFont(QFont("Arial",12));
        painter->drawText(QRectF(rect.left() - 50, rect.top() + 15, 40 ,20), QString::fromStdString("Start"), QTextOption(Qt::AlignCenter));
    }
}

void StatoGraphicsItem::setIniziale(bool value)
{
    iniziale = value;
    this->update();
}

bool StatoGraphicsItem::getIniziale()
{
    return iniziale;
}

void StatoGraphicsItem::setFinale(bool value)
{
    s->setFinale(value);
    this->update();
}

bool StatoGraphicsItem::getFinale()
{
    return s->isFinale();
}

Stato *StatoGraphicsItem::getStato()
{
    return s;
}

