#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_initButton_clicked()
{

}

void MainWindow::on_sendCommand_clicked()
{

}

void MainWindow::on_activatePort1_clicked()
{

}

void MainWindow::on_deactivatePort1_clicked()
{

}
