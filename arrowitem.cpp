#include "arrowitem.h"
#include "diagramscene.h"
#include "conditionitem.h"
#include "processitem.h"

#define PI 3.1415

void ArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (startItem->collidesWithItem(endItem))
        return;
    /*
     * Установка цвета линии и размера указателя
     */

    if(this->isSelected()){
        painter->setBrush(Qt::red);
         painter->setPen(QPen(Qt::red, 3));
    }else{
        painter->setBrush(Qt::black);
         painter->setPen(QPen(Qt::black, 2));
    }
    painter->drawLine(this->line());
    qreal arrowSize = 9;
    /*
     *определение точки пересечения линни стрелки и окружности, для корректного размещения указателя стрелки
     */
    if(ConditionItem* cs = dynamic_cast<ConditionItem*> (endItem)){
        QPointF endPoint = cs->pos();
        QPointF startPoint = startItem->pos();
        double dy = endPoint.y() - startPoint.y();
        double dx = endPoint.x() - startPoint.x();
        double line_length = sqrt(pow(dx,2) + pow(dy,2));
        double _cos = dx/line_length;
        double _sin = dy/line_length;
        endPoint = endPoint-QPointF(25*_cos, 25*_sin);
        setLine(endPoint.x(), endPoint.y(), startPoint.x(), startPoint.y());
    }
    /*
     *определение точки пересечения линии стрелки и прямоугольника, для корректного размещения указателя стрелки
     */
    if(ProcessItem* ps = dynamic_cast<ProcessItem*> (endItem)){
        QPointF endPoint = ps->pos();
        QPointF startPoint = startItem->pos();
        QPolygonF poly = QPolygonF(ps->rect());
        QLineF polyLine;
        QPointF intersectPoint, p1, p2;

        for(int i = 1; i < poly.count(); i++){
            p1 = poly.at(i-1) + ps->pos();
            p2 = poly.at(i) + ps->pos();
            polyLine = QLineF(p1,p2);
            QLineF::IntersectType intersectType = polyLine.intersect(this->line(), &intersectPoint);
            if(intersectType == QLineF::BoundedIntersection){
                endPoint = intersectPoint;
                break;
            }
        }

        setLine(endPoint.x(), endPoint.y(), startPoint.x(), startPoint.y());
    }

    /*
     *определение наклона стрелки и отрисовка указателя
     */
    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0)
        angle = (PI * 2) - angle;

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + PI / 3) * arrowSize,
                                    cos(angle + PI / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + PI - PI / 3) * arrowSize,
                                    cos(angle + PI - PI / 3) * arrowSize);

    arrowHead.clear();
    arrowHead << line().p1() << arrowP1 << arrowP2;

    painter->drawPolygon(arrowHead);

}

QVariant ArrowItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if(change == QGraphicsItem::ItemSelectedHasChanged){
        if(DiagramScene* d_scene = dynamic_cast<DiagramScene*>(this->scene())){
            d_scene->itemChanged(this);
        }
    }

    return value;
}

ArrowItem::ArrowItem(QGraphicsItem* start, QGraphicsItem* end, QGraphicsItem* parent)
    :QGraphicsLineItem(parent)
{
    startItem = start;
    endItem = end;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setPen(QPen(Qt::black, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    this->setZValue(-1000);
}

QRectF ArrowItem::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
        .normalized()
        .adjusted(-extra, -extra, extra, extra);
}

QPainterPath ArrowItem::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

ArrowItem::ArrowType ArrowItem::arrowType()
{
    if(dynamic_cast<ConditionItem*> (startItem)){
        return fromCondition;
    }
    else{
        return toCondition;
    }
}

void ArrowItem::disconnect()
{
    if(ConditionItem* cs = dynamic_cast<ConditionItem*> (startItem)){
        cs->removeArrow(this);
    }
    else
        if(ProcessItem* ps = dynamic_cast<ProcessItem*> (startItem)){
            ps->removeArrow(this);
        }

    if(ConditionItem* ce = dynamic_cast<ConditionItem*> (endItem)){
        ce->removeArrow(this);
    }
    else
        if(ProcessItem* pe = dynamic_cast<ProcessItem*> (endItem)){
            pe->removeArrow(this);
        }
}

void ArrowItem::updatePosition()
{
    double x1 = endItem->pos().x();
    double y1 = endItem->pos().y();
    double x2 = startItem->pos().x();
    double y2 = startItem->pos().y();

    QLineF line(x1,y1,x2,y2);
    setLine(line);
}

ArrowItem::~ArrowItem()
{

}

