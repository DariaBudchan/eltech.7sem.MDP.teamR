#ifndef PROCESSITEM_H
#define PROCESSITEM_H

/*
 *Класс перехода
 */

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QPainter>

class ProcessItem : public QGraphicsRectItem
{
    enum {Type = UserType+1};
public:
    ProcessItem(QGraphicsItem* parent = 0);
    ~ProcessItem();
};

#endif // PROCESSITEM_H
