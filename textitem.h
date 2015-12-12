#ifndef TEXTITEM_H
#define TEXTITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsItem>
#include <QString>
#include <QFont>
#include <QPainter>

class TextItem : public QGraphicsRectItem
{
public:
    enum {Type = UserType+100}; // для корректного преобразования типов
    QFont Font;
    TextItem(int w, int h, QString str = "", QGraphicsItem* parent = 0);
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;
    ~TextItem();
private:
    int width;
    int height;
    QString text; // Цифра - количество меток в состоянии
};

#endif // TEXTITEM_H
