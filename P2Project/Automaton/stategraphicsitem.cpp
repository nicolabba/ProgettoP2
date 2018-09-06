#include "stategraphicsitem.h"
#include "arrowhead.h"

StateGraphicsItem::StateGraphicsItem(State* state):QGraphicsItem(), state(state), starting(false)
{
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

StateGraphicsItem::StateGraphicsItem(StateGraphicsItem & st):QGraphicsItem(st.parentObject()), state(st.state), starting(st.starting)
{

}

QRectF StateGraphicsItem::boundingRect() const
{
    return QRectF(0,0,50,50);
}

void StateGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QPen pen = QPen(isSelected()?Qt::darkGreen : Qt::black,3);
    painter->setPen(pen);
    painter->drawEllipse(rect);
    painter->setFont(QFont("Arial",18));
    painter->drawText(rect, QString::fromStdString(state->getName()), QTextOption(Qt::AlignCenter));
    if(state->isFinal())
        painter->drawEllipse(5,5,40,40);
    if(starting)
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

void StateGraphicsItem::setStarting(bool value)
{
    starting = value;
    update();
}

bool StateGraphicsItem::getStarting()
{
    return starting;
}

void StateGraphicsItem::setFinal(bool value)
{
    state->setFinal(value);
    update();
}

bool StateGraphicsItem::getFinal()
{
    return state->isFinal();
}

State *StateGraphicsItem::getState()
{
    return state;
}

