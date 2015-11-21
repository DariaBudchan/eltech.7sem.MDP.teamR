#include "petriemulator.h"

PetriEmulator::PetriEmulator(DiagramScene* scene, QObject *parent)
    : QObject(parent)
{
    this->scene = scene;
}

PetriEmulator::~PetriEmulator()
{
    _isWork = false;
}

bool PetriEmulator::isValid()
{
    /*
     * проверка всех объектов состояний и переходов
     * если состояние, проверяем наличие связей
     * если переход, проверяем чтобы были связи входящие и выходящие
     */
    foreach (QGraphicsItem* item, scene->items()){
        switch (item->type()) {
        case ConditionItem::Type:
            if(ConditionItem* ci = dynamic_cast<ConditionItem*> (item)){
                if(ci->getArrows().count() <= 0)
                    return false;
            }
            break;
        case ProcessItem::Type:
            if(ProcessItem* pi = dynamic_cast<ProcessItem*> (item)){
                if(pi->arrowsFromCondition().count() <= 0 || pi->arrowsToCondition().count() <= 0)
                    return false;
            }
            break;
        default:
            break;
        }
    }

    return true;
}

void PetriEmulator::nextStep()
{
    QList<ConditionItem*> readyConditions; //готовые состояния
    readyConditions.clear();

    QList<ProcessItem*> readyProcesses; //переходы который должны быть выполнены
    readyProcesses.clear();

    bool flag = false;

    foreach (QGraphicsItem* item, scene->items()){
        flag = false;
        /*
         * проверка, готов ли переход выполниться
         */
        if(ProcessItem* pi = dynamic_cast<ProcessItem*> (item)){
            QList<ArrowItem*> temp_arrows = pi->arrowsFromCondition();
            QList<ConditionItem*> temp_conditions;
            temp_conditions.clear();
            foreach (ArrowItem* arrow, temp_arrows) {
                if(ConditionItem* ci1 = dynamic_cast<ConditionItem*> (arrow->getStart())){
                    if(ci1->getValue() >= 1){
                        temp_conditions.append(ci1);
                    }
                    else{
                        temp_conditions.clear();
                        flag = true;
                        break;
                    }
                }
            }
            /*
             *проверка, может ли выполниться переход
             */
            temp_arrows = pi->arrowsToCondition();
            foreach (ArrowItem* arrow, temp_arrows) {
                if(ConditionItem* ci3 = dynamic_cast<ConditionItem*> (arrow->getEnd())){
                    if(ci3->getValue() == ci3->maxValue()){
                        flag = true;
                        temp_conditions.clear();                        
                        break;
                    }
                }
            }
            /*
             *если переход не выполним, переход дальше
             */
            if(flag)
                continue;
            /*
             * если переход выполним, дополняем множесвто готовых состояний  и переходов
             */
            foreach (ConditionItem* ci2, temp_conditions){
                if(!readyConditions.contains(ci2)){
                    readyConditions.append(ci2);
                }
            }
            temp_conditions.clear();
            readyProcesses.append(pi);
        }
    }

    if(readyProcesses.count() <= 0) //если нет готовых состояний (а занчит и переходов), завершаем работу
        _isWork = false;
    /*
     * уменьшение маркеров готовых состояний
     */
    foreach (ConditionItem* ci, readyConditions){
        ci->decreaseValue();
    }

    QTime time;
    time.start();
    while(time.elapsed() < 150){
        qApp->processEvents();
    }
    /*
     * увеличение маркеров в следующих состояних
     */
    foreach (ProcessItem* pi, readyProcesses){
        QList<ArrowItem*> arrows = pi->arrowsToCondition();
        foreach (ArrowItem* arrow, arrows){
            if(ConditionItem* ci = dynamic_cast<ConditionItem*> (arrow->getEnd())){
                ci->increaseValue();
            }
        }
    }
}

void PetriEmulator::emulate()
{
    /*
     *эмуляцию, выполнение последовательных шагов, пока сеть не придет в конечное состояние или не будет остановлена
     */
    QTime time;
    _isWork = true;
    do{
        nextStep();
        time.start();
        while(time.elapsed() < 650){
            qApp->processEvents();
        }
    }while(_isWork);
    _isWork = false;
}

void PetriEmulator::setWork(bool val)
{
    _isWork = val;
}

bool PetriEmulator::isWork()
{
    return _isWork;
}







