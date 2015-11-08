#include "textitem.h"

TextItem::TextItem(int w, int h, QString str, QGraphicsItem *parent):
    QGraphicsRectItem(parent)
{
    width = w;
    height = h;
    text = str;
    Font = QFont("Arial");
    Font.setBold(true);
    Font.setPixelSize(height*0.75);
}

void TextItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE
{
    painter->setFont(Font);
    painter->drawText(-width/2, -height/2, width, height, Qt::AlignCenter, text);
}

TextItem::~TextItem()
{

}

