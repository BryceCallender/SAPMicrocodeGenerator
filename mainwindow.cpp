#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent, QJsonDocument *jsonDocument)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Setup on window and ui
    ui->setupUi(this);
    setWindowTitle("SAP Microcode Generator");

    if(jsonDocument != nullptr)
    {
        this->jsonDocument = jsonDocument;

        QJsonArray instructionSets = this->jsonDocument->array();

        for (QJsonValue set : instructionSets) {
            ui->instructionSetList->addItem(set.toObject()["SetName"].toString());
        }

        // Reset back to the first set in the json file
        ui->instructionSetList->setCurrentIndex(0);
    }
    else
    {
        this->jsonDocument = new QJsonDocument();
    }


    // Set up manager for updated fetch's that could be used later
    cwManagerFetchCycle = new ControlWordManager(this, 3);
    ui->fetchCycleScrollArea->setWidget(cwManagerFetchCycle);

    // All the UI components being hidden
    ui->fetchCycle->hide();
    ui->instructionSetGroupBox->hide();

    // Make sure nothing is focused
    setFocus();
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

    instructionSets[instructionSetNumber].instructions.push_back(instruction);
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

void MainWindow::on_instructionSetList_currentIndexChanged(int index)
{
    instructionSetNumber = index;
}

void MainWindow::on_modifyInstruction_pressed()
{
    ui->instructionSetGroupBox->show();
}

void MainWindow::on_instructionList_currentIndexChanged(int index)
{

}
