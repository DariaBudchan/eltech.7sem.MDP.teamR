#ifndef CONDITIONITEM_H
#define CONDITIONITEM_H

/*
 *Класс места
 */

#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QPainter>

class ConditionItem : public QGraphicsEllipseItem
{

public:
    ConditionItem(QGraphicsItem* parent = 0);
    ~ConditionItem();
};

#endif // CONDITIONITEM_H
