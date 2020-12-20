#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("SAP Microcode Generator");

    jsonDocument = new QJsonDocument();

    ui->fetchCycle->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_showFetchCycle_toggled(bool checked)
{
    checked ? ui->fetchCycle->show() : ui->fetchCycle->hide();
}

void MainWindow::on_save_pressed()
{

}
