#include "transitiongraphicsitem.h"
#include "arrowhead.h"
#include <math.h>
#include "transitionpda.h"


TransitionGraphicsItem::TransitionGraphicsItem(Transition * tran, StateGraphicsItem * from, StateGraphicsItem *to, bool d) : QGraphicsItem(),
    from(from), to(to), doubleTransition(d)
{
    transitions = new std::list<Transition*>();
    transitions->push_back(tran);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

TransitionGraphicsItem::TransitionGraphicsItem(TransitionGraphicsItem & tr):QGraphicsItem(tr.parentObject()), transitions(tr.transitions), from(tr.from), to(tr.to)
{

}

QRectF TransitionGraphicsItem::boundingRect() const
{
    QRectF fromRect = QRectF(from->pos(), from->boundingRect().size());
    if(from == to)
        return QRectF(fromRect.left() + 15, fromRect.top() - 20, 20, 25);
    else
    {
        QRectF toRect = QRectF(to->pos(),to->boundingRect().size());
        int angle = int((atan2(toRect.top() - fromRect.top(), fromRect.left() - toRect.left()) * 180 / M_PI) + 180) % 360;
        int left,top,right,bottom;
        if(angle >= 0 && angle < 45)
        {
            left = fromRect.right();
            bottom = fromRect.top() + (fromRect.height() / 2);
            right = toRect.left();
            top = toRect.top() + (toRect.height() / 2);
            if(doubleTransition)
            {
                top += 5;
                bottom += 5;
            }
        }
        else if(angle >= 45 && angle < 90)
        {
            left = fromRect.right() - (fromRect.width() / 2);
            bottom = fromRect.top();
            right = toRect.right() - (toRect.width() / 2);
            top = toRect.bottom();
            if(doubleTransition)
            {
                right += 5;
                left += 5;
            }
        }
        else if(angle >= 90 && angle < 135)
        {
            left = toRect.right() - (toRect.width() / 2);
            bottom = fromRect.top();
            right = fromRect.right() - (fromRect.width() / 2);
            top = toRect.bottom();
            if(doubleTransition)
            {
                right += 5;
                left += 5;
            }
        }
        else if(angle >= 135 && angle < 180)
        {
            left = toRect.right();
            bottom = fromRect.top() + (fromRect.height() / 2);
            right = fromRect.left();
            top = toRect.top() + (toRect.height() / 2);
            if(doubleTransition)
            {
                top -= 5;
                bottom -= 5;
            }
        }
        else if(angle >= 180 && angle < 225)
        {
            left = toRect.right();
            bottom = toRect.top() + (toRect.height() / 2);
            right = fromRect.left();
            top = fromRect.top() + (fromRect.height() / 2);
            if(doubleTransition)
            {
                top -= 5;
                bottom -= 5;
            }
        }
        else if(angle >= 225 && angle < 270)
        {
            left = toRect.right() - (toRect.width() / 2);
            bottom = toRect.top();
            right = fromRect.right() - (fromRect.width() / 2);
            top = fromRect.bottom();
            if(doubleTransition)
            {
                right -= 5;
                left -= 5;
            }
        }
        else if(angle >= 270 && angle < 315)
        {
            left = fromRect.right() - (fromRect.width() / 2);
            bottom = toRect.top();
            right = toRect.right() - (toRect.width() / 2);
            top = fromRect.bottom();
            if(doubleTransition)
            {
                right -= 5;
                left -= 5;
            }
        }
        else if(angle >= 315 && angle <= 360)
        {
            left = fromRect.right();
            bottom = toRect.top() + (toRect.height() / 2);
            right = toRect.left();
            top = fromRect.top() + (fromRect.height() / 2);
            if(doubleTransition)
            {
                top += 5;
                bottom += 5;
            }
        }
        return QRectF(left - 5,top - 5,right - left + 10, bottom - top + 10);
    }
}

void TransitionGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QTextOption textOptions;
    QRectF textRect;
    TransitionPDA* tempTrans;
    QString textShown = "";
    Transition* temp;
    int lines = 0;
    for(std::list<Transition*>::iterator i = transitions->begin(); i!= transitions->end();)
    {
        textShown.append((*i)->getInput());
        temp = (*i);
        if(dynamic_cast<TransitionPDA*>(temp))
        {
            tempTrans = dynamic_cast<TransitionPDA*>(temp);
            textShown.append(" ");
            textShown.append(tempTrans->getHead());
            textShown.append("/");
            textShown.append(QString::fromStdString(tempTrans->getNewHead()));
            if(++i != transitions->end())
            {
                textShown.append("\n");
                lines++;
            }
        }else
            if(++i != transitions->end())
                textShown.append(",");
    }

    painter->setPen(QPen(isSelected()?Qt::darkGreen : Qt::black,3));
    double angle;
    QPoint vertex;
    QRectF bRect = boundingRect();
    QRectF *rect;
    if(to == nullptr || from->getState() == to->getState())
    {
        rect = new QRectF(bRect.left(), bRect.top(), bRect.width(), bRect.height() - 5);
        painter->drawEllipse(*rect);
        angle = 0;
        vertex = QPoint(bRect.left() + (bRect.width() / 2), bRect.bottom() - 5);
        textRect = QRectF(bRect.left() - textShown.length() * 6,bRect.top() - 20 * (lines + 1), bRect.width() + textShown.length() * 12, 20 * (lines + 1));
        textOptions = QTextOption(Qt::AlignBottom | Qt::AlignHCenter);
    }else
    {
        QRectF fromRect = QRectF(from->pos(),from->boundingRect().size());
        QRectF toRect = QRectF(to->pos(),to->boundingRect().size());
        int angleCheck = int((atan2(toRect.top() - fromRect.top(), fromRect.left() - toRect.left()) * 180 / M_PI) + 180) % 360;
        prepareGeometryChange();
        rect = new QRectF(bRect.left() + 5,bRect.top() + 5, bRect.width() - 10, bRect.height() - 10);

        if(angleCheck >= 0 && angleCheck < 90)
        {
            angle = atan2(rect->bottom() - rect->top(), rect->right() - rect->left()) * 180 / M_PI;
            painter->drawLine(rect->bottomLeft(), rect->topRight());
            vertex = QPoint(rect->right(), rect->top());

        }
        else if(angleCheck >= 90 && angleCheck < 180)
        {
            angle = atan2(rect->bottom() - rect->top(), rect->left() - rect->right()) * 180 / M_PI;
            painter->drawLine(rect->bottomRight(), rect->topLeft());
            vertex = QPoint(rect->left(), rect->top());
        }
        else if(angleCheck >= 180 && angleCheck < 270)
        {
            angle = atan2(rect->top() - rect->bottom(), rect->left() - rect->right()) * 180 / M_PI;
            painter->drawLine(rect->topRight(), rect->bottomLeft());
            vertex = QPoint(rect->left(), rect->bottom());
        }
        else
        {
            angle = atan2(rect->top() - rect->bottom(), rect->right() - rect->left()) * 180 / M_PI;
            painter->drawLine(rect->topLeft(), rect->bottomRight());
            vertex = QPoint(rect->right(), rect->bottom());
        }

        QPoint middle = QPoint((rect->left() + (rect->right() - rect->left()) / 2), (rect->top() + (rect->bottom() - rect->top()) / 2));
        textRect = QRectF(middle.rx() - (20 + textShown.length()/(lines + 1) * 6), middle.ry() - (lines + 1) * 20, 40 + textShown.length()/(lines + 1) * 12, (lines + 1)*40);

        if(angleCheck >= 45 && angleCheck < 135)
            textOptions = QTextOption(Qt::AlignRight | Qt::AlignVCenter);
        else if (angleCheck >= 135 && angleCheck < 215)
             textOptions = QTextOption(Qt::AlignTop | Qt::AlignHCenter);
        else if(angleCheck >= 215 && angleCheck < 315)
             textOptions = QTextOption(Qt::AlignLeft | Qt::AlignVCenter);
        else
             textOptions = QTextOption(Qt::AlignBottom | Qt::AlignHCenter);
    }

    QPainterPath path;
    path.addPolygon((new ArrowHead(vertex,angle))->getPoly());
    path.closeSubpath();
    painter->drawPath(path);
    painter->fillPath(path, QBrush(isSelected()?Qt::darkGreen : Qt::black));

    painter->setPen(QPen(Qt::black,3));
    painter->setFont(QFont("Arial",12));
    painter->drawText(textRect,textShown,textOptions);



    //painter->drawText((rect.left() + (rect.right() - rect.left()) / 2) - 15, (rect.top() + (rect.bottom() - rect.top()) / 2) - 15, textShown);
}

void TransitionGraphicsItem::add(Transition * t)
{
    transitions->push_back(t);
}

