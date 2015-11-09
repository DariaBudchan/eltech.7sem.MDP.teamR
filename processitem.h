#ifndef PROCESSITEM_H
#define PROCESSITEM_H

/*
 *Класс перехода
 */

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QPainter>

#include "arrowitem.h"

class ProcessItem : public QGraphicsRectItem
{
    unsigned int current_value;
    QList<ArrowItem*> arrows;
public:
    enum {Type = UserType+1};
    ProcessItem(QGraphicsItem* parent = 0);
    int type() const Q_DECL_OVERRIDE {return Type;}

    void removeArrow(ArrowItem* arrow);
    void removeArrows();
    void addArrow(ArrowItem* arrow);
    QList<ArrowItem*> arrowsFromCondition();
    QList<ArrowItem*> arrowsToCondition();
    QList<ArrowItem*> getArrows();
    void updateItem();
    ~ProcessItem();
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;
signals:
    void selectedChange(QGraphicsItem* item);
};

#endif // PROCESSITEM_H
