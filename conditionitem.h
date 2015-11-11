#ifndef CONDITIONITEM_H
#define CONDITIONITEM_H

/*
 *Класс места
 */

#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QPainter>
#include <math.h>

#include "arrowitem.h"
#include "textitem.h"

class ConditionItem : public QGraphicsEllipseItem
{
    unsigned int current_value;
    unsigned int max_value;
    QList<ArrowItem*> arrows;
public:
    enum {Type = UserType+2};
    ConditionItem(QGraphicsItem* parent = 0);
    int type() const Q_DECL_OVERRIDE {return Type;}
    void increaseValue();
    void decreaseValue();
    void setValue(unsigned int value);
    unsigned int maxValue();
    unsigned int getValue();

    void removeArrow(ArrowItem* arrow);
    void removeArrows();
    void addArrow(ArrowItem* arrow);
    QList<ArrowItem*> getArrows();
    void contectDraw(unsigned int value);

    void updateItem();

    ~ConditionItem();
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
signals:
    void selectedChange(QGraphicsItem* item);
};

#endif // CONDITIONITEM_H
