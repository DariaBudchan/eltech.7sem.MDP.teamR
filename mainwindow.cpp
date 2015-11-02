#include "mainwindow.h"

QToolButton *MainWindow::createToolBoxButton(QString text, int type){
    QToolButton* button = new QToolButton;
    button->setCheckable(true);
    button->setText(text);
    button->setFixedSize(70,40);
    itemsButtonGroup->addButton(button, type);
    return button;
}

void MainWindow::deselect()
{
    QList<QAbstractButton*> buttons = itemsButtonGroup->buttons();
    itemsButtonGroup->setExclusive(false);
    foreach (QAbstractButton* button, buttons) {
            button->setChecked(false);
    }
    itemsButtonGroup->setExclusive(true);
}

void MainWindow::createActions(){
    sceneSetMoveMode = new QAction("Move", this);
    connect(sceneSetMoveMode, SIGNAL(triggered()),
            this, SLOT(sceneMove()));
    sceneSetLineMode = new QAction("Connect", this);
    connect(sceneSetLineMode, SIGNAL(triggered()),
            this, SLOT(sceneLine()));
    itemDelete = new QAction("Delete", this);
    connect(itemDelete, SIGNAL(triggered()),
            this, SLOT(deleteItem()));
    itemConditionInc = new QAction("Increase", this);
    connect(itemConditionInc, SIGNAL(triggered()),
            this, SLOT(conditionInc()));
    itemConditionDec = new QAction("Decrease", this);
    connect(itemConditionDec, SIGNAL(triggered()),
            this, SLOT(conditionDec()));
    sceneNew = new QAction("New", this);
    connect(sceneNew, SIGNAL(triggered()),
            this ,SLOT(New()));
    sceneStepForward = new QAction("Next", this);
    connect(sceneStepForward, SIGNAL(triggered()),
            this, SLOT(StepForward()));
    sceneStepBack = new QAction("Previus", this);
    connect(sceneStepBack, SIGNAL(triggered()),
            this, SLOT(StepBack()));
}

void MainWindow::createToolBox()
{
    itemsButtonGroup = new QButtonGroup(this);
    itemsButtonGroup->setExclusive(true);
    connect(itemsButtonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(itemsButtonClicked(int)));
    QVBoxLayout* layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop);
    layout->addWidget(createToolBoxButton("Condition", ConditionItem::Type));
    layout->addWidget(createToolBoxButton("Process", ProcessItem::Type));
    QWidget* widget = new QWidget;
    widget->setLayout(layout);
    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->addItem(widget, "Objects");
    toolBox->setMinimumWidth(widget->sizeHint().width());
}

void MainWindow::createToolbars()
{
    diagramToolBar = addToolBar("Diagram");
    diagramToolBar->addAction(sceneNew);

    modeToolBar = addToolBar("Diagram mode");
    modeToolBar->addAction(sceneSetMoveMode);
    modeToolBar->addAction(sceneSetLineMode);

    itemToolBar = addToolBar("Item");
    itemToolBar->addAction(itemDelete);

    condiotionToolBar = addToolBar("Condition");
    condiotionToolBar->addAction(itemConditionDec);
    condiotionToolBar->addAction(itemConditionInc);

    emulationToolBar = addToolBar("Emulation");
    emulationToolBar->addAction(sceneStepBack);
    emulationToolBar->addAction(sceneStepForward);
}

void MainWindow::createScene()
{
    scene = new DiagramScene();
    scene->setSceneRect(-1000, -1000, 2000, 2000);
    scene->setMode(DiagramScene::Move);
    view = new QGraphicsView(this);
    view->setScene(scene);
    connect(scene, SIGNAL(itemInserted(QGraphicsItem*)),
            this, SLOT(itemInserted(QGraphicsItem*)));
    connect(scene, SIGNAL(itemSelected(QGraphicsItem*)),
            this, SLOT(itemSelected(QGraphicsItem*)));
}

void MainWindow::itemsButtonClicked(int id)
{
    QList<QAbstractButton*> buttons = itemsButtonGroup->buttons();
    foreach (QAbstractButton* button, buttons) {
        if(itemsButtonGroup->button(id) != button)
            button->setChecked(false);
    }
    scene->setMode(DiagramScene::Draw);
    switch (id) {
    case ProcessItem::Type:
    case ConditionItem::Type:
        scene->setItemType(id);
        break;
    default:
        scene->setMode(DiagramScene::Move);
        break;
    }
}

void MainWindow::itemInserted(QGraphicsItem *item)
{
    deselect();
    scene->setMode(DiagramScene::Move);
}

void MainWindow::itemSelected(QGraphicsItem *item)
{
    deselect();
}

void MainWindow::deleteItem()
{

}

void MainWindow::sceneMove()
{
    scene->setMode(DiagramScene::Move);
}

void MainWindow::sceneLine()
{
    scene->setMode(DiagramScene::Line);
}

void MainWindow::conditionInc()
{

}

void MainWindow::conditionDec()
{

}

void MainWindow::New()
{

}

void MainWindow::StepForward()
{

}

void MainWindow::StepBack()
{

}

MainWindow::MainWindow()
{
    createActions();
    createScene();
    createToolbars();
    createToolBox();

    QVBoxLayout* centralLayout = new QVBoxLayout;
    centralLayout->setAlignment(Qt::AlignLeft);
    QHBoxLayout* workspace = new QHBoxLayout;
    workspace->setAlignment(Qt::AlignTop);

    workspace->addWidget(toolBox);
    workspace->addWidget(view);

    centralLayout->addItem(workspace);

    QWidget* central = new QWidget;
    central->setLayout(centralLayout);
    setCentralWidget(central);
}

MainWindow::~MainWindow()
{

}
