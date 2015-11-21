#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

/*
 *Класс сцены
 */

#include <QGraphicsScene>
#include <QObject>

#include "conditionitem.h"
#include "processitem.h"
#include "arrowitem.h"

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Mode {Draw, Line, Move}; //режимы сцены
    DiagramScene(QObject* parent = 0);
    ~DiagramScene();
private:
    Mode mode; //режим
    int current_type; //тип объекта для отрисовки
    QGraphicsLineItem* line; //вспомогательная линия
    QPointF startPoint; //начальная точка

    void drawItem(QGraphicsSceneMouseEvent* mouseEvent); //нарисовать объект
    void addArrow(QGraphicsItem* start, QGraphicsItem* end); //добавить стрелку между объектами
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
public slots:
    void itemChanged(QGraphicsItem* item); //если выбранный объект изменился
    void setMode(Mode newmode); //установка текущего режима
    void setItemType(int type); //установка текущего типа объекта
signals:
    void itemSelected(QGraphicsItem* item);
    void itemInserted(QGraphicsItem* item);
};

#endif // DIAGRAMSCENE_H
