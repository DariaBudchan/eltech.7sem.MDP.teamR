#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QObject>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QToolButton>
#include <QToolBox>

#include "diagramscene.h"

class MainWindow : public QWidget
{
    Q_OBJECT

    DiagramScene* scene;
    QGraphicsView* view;

    QButtonGroup* itemsButtonGroup;
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
