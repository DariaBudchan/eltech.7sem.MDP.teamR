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
#include <QCloseEvent>
#include <QStatusBar>

#include "diagramscene.h"
#include "petriemulator.h"
#include "testing.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

    DiagramScene* scene;
    QGraphicsView* view;
    PetriEmulator* emulator;

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
    QAction* itemConditionReset;
    QAction* sceneNew;
    QAction* sceneStepForward;
    QAction* sceneStartEmulation;
    QAction* sceneStopEmulation;

    bool isOnWork;

    QToolButton* createToolBoxButton(QString text, int type);
    void deselect(); //снятие выделения с кнопок
    void createActions(); //создание actions
    void createToolBox(); //создание меню объектов
    void createToolbars(); //создание панели управления
    void createScene(); //создание сцены

private slots:
    /*
     *функции для работы со сценой
     */
    void itemsButtonClicked(int id);
    void itemInserted(QGraphicsItem* item);
    void itemSelected(QGraphicsItem* item);
    void deleteItem();
    void sceneMove();
    void sceneLine();
    void New();
    /*
     *функции для работы с состояниями
     */
    void conditionInc();
    void conditionDec();
    void conditionReset();
    /*
     *функции для работы с эмулятором
     */
    void StepForward();
    void StartEmulation();
    void StopEmulation();
protected:
    void closeEvent(QCloseEvent* event) Q_DECL_OVERRIDE;
public:
    MainWindow();
    ~MainWindow();
};

#endif // MAINWINDOW_H

