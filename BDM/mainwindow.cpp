#include <QMessageBox>
#include <QCoreApplication>
#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
//    std::cout << "Hello World!" << std::endl;
}

void MainWindow::on_graphicsView_customContextMenuRequested(const QPoint &pos)
{
    std::cout << pos.x() << " " << pos.y() << std::endl;
}

void MainWindow::on_action_triggered()
{
    std::cout << "もうだめだーおしまいだー" << std::endl;
    QCoreApplication::quit();
}

void MainWindow::on_action_3_triggered()
{
    std::cout << "垢消せ" << std::endl;
    QCoreApplication::quit();
}

void MainWindow::on_action_5_triggered()
{
    std::cout << "Send Command to the Helicopter!!" << std::endl;
}
