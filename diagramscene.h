#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

/*
 *Класс сцены
 */

#include <QGraphicsScene>
#include <QObject>

#include "conditionitem.h"
#include "processitem.h"

class DiagramScene : public QGraphicsScene
{
    Q_OBJECT
public:
    DiagramScene(QObject* parent = 0);
    ~DiagramScene();
};

#endif // DIAGRAMSCENE_H
