#include "petriemulator.h"

PetriEmulator::PetriEmulator(QObject *parent) : QObject(parent)
{

}

PetriEmulator::~PetriEmulator()
{

}

bool PetriEmulator::isValid(DiagramScene *scene)
{
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

void PetriEmulator::nextStep(DiagramScene *scene)
{
    QList<ConditionItem*> readyConditions;
    readyConditions.clear();

    QList<ProcessItem*> readyProcesses;
    readyProcesses.clear();

    bool flag = false;

    foreach (QGraphicsItem* item, scene->items()){
        flag = false;
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

            if(flag)
                continue;

            foreach (ConditionItem* ci2, temp_conditions){
                if(!readyConditions.contains(ci2)){
                    readyConditions.append(ci2);
                }
            }
            temp_conditions.clear();
            readyProcesses.append(pi);
        }
    }

    foreach (ConditionItem* ci, readyConditions){
        ci->decreaseValue();
    }

    foreach (ProcessItem* pi, readyProcesses){
        QList<ArrowItem*> arrows = pi->arrowsToCondition();
        foreach (ArrowItem* arrow, arrows){
            if(ConditionItem* ci = dynamic_cast<ConditionItem*> (arrow->getEnd())){
                ci->increaseValue();
            }
        }
    }
}

void PetriEmulator::previousStep(DiagramScene *scene)
{

}

