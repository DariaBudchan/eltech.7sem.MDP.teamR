#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    this->setLayout(new QVBoxLayout);

    QHBoxLayout* workspace = new QHBoxLayout;

    itemsButtonGroup = new QButtonGroup(this);
    itemsButtonGroup->setExclusive(true);

    QToolButton* btn_condition = new QToolButton(this);
    btn_condition->setText("Condition");
    btn_condition->setCheckable(true);

    QToolButton* btn_process = new QToolButton(this);
    btn_process->setText("Process");
    btn_process->setCheckable(true);

    itemsButtonGroup->addButton(btn_condition, 1);
    itemsButtonGroup->addButton(btn_process, 2);

    QVBoxLayout* toolbar = new QVBoxLayout;
    toolbar->addWidget(btn_condition);
    toolbar->addWidget(btn_process);
    toolbar->setAlignment(Qt::AlignTop);

    scene = new DiagramScene();
    scene->setSceneRect(0,0,1500,1500);
    scene->setMode(DiagramScene::Line);
    view = new QGraphicsView(this);
    view->setScene(scene);

    workspace->addItem(toolbar);
    workspace->addWidget(view);

    this->layout()->addItem(workspace);
}

MainWindow::~MainWindow()
{

}
