#ifndef ARROWITEM_H
#define ARROWITEM_H

/*
 *Класс связи(стрелки)
 */

#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <math.h>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>

#include <QDebug>

class ArrowItem : public QGraphicsLineItem
{
    enum {Type = UserType + 3};
    QGraphicsItem* startItem;
    QGraphicsItem* endItem;
    QPolygonF arrowHead;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
public:
    ArrowItem(QGraphicsItem* start, QGraphicsItem* end, QGraphicsItem* parent = 0);
    int type() const Q_DECL_OVERRIDE {return Type;}
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    QGraphicsItem* getStart(){return startItem;}
    QGraphicsItem* getEnd(){return endItem;}
    void updatePosition();
    ~ArrowItem();
};

#endif // ARROWITEM_H
