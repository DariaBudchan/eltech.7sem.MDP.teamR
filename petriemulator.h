#ifndef PETRIEMULATOR_H
#define PETRIEMULATOR_H

#include <QObject>
#include <QTime>
#include <QCoreApplication>

#include "diagramscene.h"

class PetriEmulator : public QObject
{
    Q_OBJECT
    bool _isWork;
    DiagramScene* scene;
public:
    explicit PetriEmulator(DiagramScene* scene, QObject *parent = 0);
    ~PetriEmulator();
    bool isValid();
    void nextStep();
    void Emulate();
    void setWork(bool val);
    bool isWork();
signals:
};

#endif // PETRIEMULATOR_H
