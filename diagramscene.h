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
    enum Mode {Draw, Line, Move};
    DiagramScene(QObject* parent = 0);
    ~DiagramScene();
private:
    Mode mode;
    int current_type;
    QGraphicsLineItem* line;
    QPointF startPoint;

    bool isItemChange(int type);
    void drawItem(QGraphicsSceneMouseEvent* mouseEvent);
    void addArrow(QGraphicsItem* start, QGraphicsItem* end);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
public slots:
    void itemChanged(QGraphicsItem* item); //если выбранный объект меняется, должен вызваться этот слот
    void setMode(Mode newmode);
    void setItemType(int type);
signals:
    void itemSelected(QGraphicsItem* item);
    void itemInserted(QGraphicsItem* item);
};

#endif // DIAGRAMSCENE_H
