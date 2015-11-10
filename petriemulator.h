#ifndef PETRIEMULATOR_H
#define PETRIEMULATOR_H

#include <QObject>

#include "diagramscene.h"

class PetriEmulator : public QObject
{
    Q_OBJECT
public:
    explicit PetriEmulator(QObject *parent = 0);
    ~PetriEmulator();
    bool isValid(DiagramScene* scene);
    void nextStep(DiagramScene* scene);
    void previousStep(DiagramScene* scene);
signals:

public slots:
};

#endif // PETRIEMULATOR_H
