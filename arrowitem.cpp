#include "arrowitem.h"
#include "diagramscene.h"
#include "conditionitem.h"
#include "processitem.h"

#define PI 3.1415

void ArrowItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if (startItem->collidesWithItem(endItem))
        return;

    painter->setPen(pen());
    painter->setBrush(Qt::black);
    painter->drawLine(this->line());
    qreal arrowSize = 8;

    setLine(startItem->pos().x(), startItem->pos().y(), endItem->pos().x(), endItem->pos().y());

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
    this->setZValue(1000);
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

