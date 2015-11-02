#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QObject>
#include <QMainWindow>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QToolButton>
#include <QToolBox>
#include <QAction>
#include <QToolBar>
#include <QIcon>

#include "diagramscene.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    DiagramScene* scene;
    QGraphicsView* view;

    QToolBox* toolBox;
    QButtonGroup* itemsButtonGroup;

    QToolBar* diagramToolBar;
    QToolBar* modeToolBar;
    QToolBar* itemToolBar;
    QToolBar* condiotionToolBar;
    QToolBar* emulationToolBar;

    QAction* sceneSetMoveMode;
    QAction* sceneSetLineMode;
    QAction* itemDelete;
    QAction* itemConditionInc;
    QAction* itemConditionDec;
    QAction* sceneNew;
    QAction* sceneStepForward;
    QAction* sceneStepBack;

    QToolButton* createToolBoxButton(QString text, int type);
    void deselect();
    void createActions();
    void createToolBox();
    void createToolbars();
    void createScene();

private slots:
    void itemsButtonClicked(int id);
    void itemInserted(QGraphicsItem* item);
    void itemSelected(QGraphicsItem* item);
    void deleteItem();
    void sceneMove();
    void sceneLine();
    void conditionInc();
    void conditionDec();
    void New();
    void StepForward();
    void StepBack();
public:
    MainWindow();
    ~MainWindow();
};

#endif // MAINWINDOW_H

