#include "transizionegraphicsitem.h"
#include "arrowhead.h"
#include <math.h>
#include "transizionepda.h"
TransizioneGraphicsItem::TransizioneGraphicsItem(Transizione * tran, StatoGraphicsItem * da, StatoGraphicsItem *a, bool d) : QGraphicsItem(),
    da(da), a(a), doppia(d)
{
    transizioni = new std::list<Transizione*>();
    transizioni->push_back(tran);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

TransizioneGraphicsItem::TransizioneGraphicsItem(TransizioneGraphicsItem & tr):QGraphicsItem(tr.parentObject()), transizioni(tr.transizioni), da(tr.da), a(tr.a)
{

}

QRectF TransizioneGraphicsItem::boundingRect() const
{
    QRectF part = QRectF(da->pos(), da->boundingRect().size());
    if(da == a)
        return QRectF(part.left() + 15, part.top() - 20, 20, 25);
    else
    {
        QRectF arr = QRectF(a->pos(),a->boundingRect().size());
        int angle = int((atan2(arr.top() - part.top(), part.left() - arr.left()) * 180 / M_PI) + 180) % 360;
        int left,top,right,bottom;
        if(angle >= 0 && angle < 45)
        {
            left = part.right();
            bottom = part.top() + (part.height() / 2);
            right = arr.left();
            top = arr.top() + (arr.height() / 2);
            if(doppia)
            {
                top += 5;
                bottom += 5;
            }
        }
        else if(angle >= 45 && angle < 90)
        {
            left = part.right() - (part.width() / 2);
            bottom = part.top();
            right = arr.right() - (arr.width() / 2);
            top = arr.bottom();
            if(doppia)
            {
                right += 5;
                left += 5;
            }
        }
        else if(angle >= 90 && angle < 135)
        {
            left = arr.right() - (arr.width() / 2);
            bottom = part.top();
            right = part.right() - (part.width() / 2);
            top = arr.bottom();
            if(doppia)
            {
                right += 5;
                left += 5;
            }
        }
        else if(angle >= 135 && angle < 180)
        {
            left = arr.right();
            bottom = part.top() + (part.height() / 2);
            right = part.left();
            top = arr.top() + (arr.height() / 2);
            if(doppia)
            {
                top -= 5;
                bottom -= 5;
            }
        }
        else if(angle >= 180 && angle < 225)
        {
            left = arr.right();
            bottom = arr.top() + (arr.height() / 2);
            right = part.left();
            top = part.top() + (part.height() / 2);
            if(doppia)
            {
                top -= 5;
                bottom -= 5;
            }
        }
        else if(angle >= 225 && angle < 270)
        {
            left = arr.right() - (arr.width() / 2);
            bottom = arr.top();
            right = part.right() - (part.width() / 2);
            top = part.bottom();
            if(doppia)
            {
                right -= 5;
                left -= 5;
            }
        }
        else if(angle >= 270 && angle < 315)
        {
            left = part.right() - (part.width() / 2);
            bottom = arr.top();
            right = arr.right() - (arr.width() / 2);
            top = part.bottom();
            if(doppia)
            {
                right -= 5;
                left -= 5;
            }
        }
        else if(angle >= 315 && angle <= 360)
        {
            left = part.right();
            bottom = arr.top() + (arr.height() / 2);
            right = arr.left();
            top = part.top() + (part.height() / 2);
            if(doppia)
            {
                top += 5;
                bottom += 5;
            }
        }
        return QRectF(left - 5,top - 5,right - left + 10, bottom - top + 10);
    }
}

void TransizioneGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QTextOption textOptions;
    QRectF textRect;
    TransizionePDA* tempTrans;
    QString textShown = "";
    Transizione* temp;
    int lines = 0;
    for(std::list<Transizione*>::iterator i = transizioni->begin(); i!= transizioni->end();)
    {
        textShown.append((*i)->getInput());
        temp = (*i);
        if(dynamic_cast<TransizionePDA*>(temp))
        {
            tempTrans = dynamic_cast<TransizionePDA*>(temp);
            textShown.append(" ");
            textShown.append(tempTrans->getHead());
            textShown.append("/");
            textShown.append(QString::fromStdString(tempTrans->getNewHead()));
            if(++i != transizioni->end())
            {
                textShown.append("\n");
                lines++;
            }
        }else
            if(++i != transizioni->end())
                textShown.append(",");
    }

    painter->setPen(QPen(isSelected()?Qt::red : Qt::black,3));
    double angle;
    QPoint vertex;
    QRectF bRect = boundingRect();
    QRectF *rect;
    if(a == nullptr || da->getStato() == a->getStato())
    {
        rect = new QRectF(bRect.left(), bRect.top(), bRect.width(), bRect.height() - 5);
        painter->drawEllipse(*rect);
        angle = 0;
        vertex = QPoint(bRect.left() + (bRect.width() / 2), bRect.bottom() - 5);
        textRect = QRectF(bRect.left() - textShown.length() * 6,bRect.top() - 15 * (lines + 1), bRect.width() + textShown.length() * 12, 12 * (lines + 1));
        textOptions = QTextOption(Qt::AlignBottom | Qt::AlignHCenter);
    }else
    {
        QRectF part = QRectF(da->pos(),da->boundingRect().size());
        QRectF arr = QRectF(a->pos(),a->boundingRect().size());
        int angleCheck = int((atan2(arr.top() - part.top(), part.left() - arr.left()) * 180 / M_PI) + 180) % 360;
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
        textRect = QRectF(middle.rx() - (20 + textShown.length() * 6), middle.ry() - (20 + lines * 6), 40 + textShown.length() * 12, 40 + lines * 12);

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
    painter->fillPath(path, QBrush(isSelected()?Qt::red : Qt::black));

    painter->setPen(QPen(Qt::black,3));
    painter->setFont(QFont("Arial",12));
    painter->drawText(textRect,textShown,textOptions);



    //painter->drawText((rect.left() + (rect.right() - rect.left()) / 2) - 15, (rect.top() + (rect.bottom() - rect.top()) / 2) - 15, textShown);
}

void TransizioneGraphicsItem::add(Transizione * t)
{
    transizioni->push_back(t);
}

