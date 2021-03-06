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
    QGraphicsItem* startItem; //начальный объект
    QGraphicsItem* endItem; //конечный объект
    QPolygonF arrowHead;
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
public:
    enum {Type = UserType + 3};  //тип объекта, для корректного преобразования класса
    enum ArrowType{fromCondition, toCondition}; //тип связи (направление)
    ArrowItem(QGraphicsItem* start, QGraphicsItem* end, QGraphicsItem* parent = 0);
    int type() const Q_DECL_OVERRIDE {return Type;}
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    QGraphicsItem* getStart(){return startItem;}
    QGraphicsItem* getEnd(){return endItem;}
    ArrowType arrowType();
    void disconnect(); //отсоединение стрелки
    void updatePosition(); //обновление позиции
    ~ArrowItem();
};

#endif // ARROWITEM_H
