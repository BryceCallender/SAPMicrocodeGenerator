#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("SAP Microcode Generator");

    jsonDocument = new QJsonDocument();

    ui->fetchCycle->hide();

    cwManagerFetchCycle = new ControlWordManager(this, 3);

    ui->scrollArea_2->setWidget(cwManagerFetchCycle);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_showFetchCycle_toggled(bool checked)
{
    checked ? ui->fetchCycle->show() : ui->fetchCycle->hide();
}

void MainWindow::on_tStates_valueChanged(int arg1)
{
    cwManagerMicroCode = new ControlWordManager(this, arg1);
    ui->scrollArea->setWidget(cwManagerMicroCode);
}

void MainWindow::on_addInstruction_pressed()
{
    Instruction instruction;

    instruction.opCode = ui->opCode->text();
    instruction.binCode = ui->binaryCode->text();
    instruction.TStates = ui->tStates->value();
    instruction.affectsFlags = ui->affectsFlags->isChecked();
    instruction.bytes = ui->byteCount->value();

    instruction.microCode = cwManagerMicroCode->convertControlWordToString();
    QVector<QString> updatedCycle = cwManagerFetchCycle->convertControlWordToString();

    if(updatedCycle.size() > 0)
    {
        instruction.updatedFetchCycleStates = QVariant::fromValue(updatedCycle);
    }

    qDebug() << instruction.convertToJSON();

    instructions.push_back(instruction.convertToJSON());

}

void MainWindow::on_save_pressed()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save File"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));

    QFile file(fileName);
    if(file.open(QFile::WriteOnly))
    {
        file.write(jsonDocument->toJson(QJsonDocument::Indented));
    }
}

void MainWindow::on_preview_pressed()
{
    jsonPreviewWindow = new JSONPreview();




    jsonPreviewWindow->setText(jsonDocument->toJson(QJsonDocument::Indented));
    jsonPreviewWindow->show();
}
