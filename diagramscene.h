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
    DiagramScene(QObject* parent = 0);
    ~DiagramScene();
public slots:
    void itemChanged(QGraphicsItem* item); //если выбранный объект меняется, должен вызваться этот слот
signals:
    void itemSelected(QGraphicsItem* item);
};

#endif // DIAGRAMSCENE_H
