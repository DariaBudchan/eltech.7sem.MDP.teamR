#ifndef PETRIEMULATOR_H
#define PETRIEMULATOR_H

#include <QObject>
#include <QTime>
#include <QCoreApplication>

#include "diagramscene.h"

class PetriEmulator : public QObject
{
    Q_OBJECT
    bool _isWork; //режим работы, true - работает, false - остановка
    DiagramScene* scene; //свена, на которой надо произвести эмуляцию
public:
    explicit PetriEmulator(DiagramScene* scene, QObject *parent = 0);
    ~PetriEmulator();
    bool isValid(); //проверка корректности сети Петри
    void nextStep(); // выполинть следующий шаг
    void emulate(); // запустить эмуляцию
    void setWork(bool val); //установка режима работы
    bool isWork(); // проверка, работает ли эмулятор
signals:
};

#endif // PETRIEMULATOR_H
