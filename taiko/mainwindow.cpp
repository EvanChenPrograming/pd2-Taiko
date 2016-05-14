#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new Scene();
    ui->graphicsView->setScene(scene);
    scene->setSceneRect(10,5,750,395);
    settingBg();
    ui->graphicsView->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::settingBg()
{
    QImage bg;
    bg.load(":/pics/pics/open.jpg");
    bg = bg.scaled(770,400);
    scene->setBackgroundBrush(bg);
    /* Goto setting the initial page for bbtan */
    //scene->Init(x_start);
}
