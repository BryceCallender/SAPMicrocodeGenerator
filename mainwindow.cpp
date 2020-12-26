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

        int i = 0;
        for (const QJsonValue& set : instructionSets)
        {
            QJsonObject instructionSet = set.toObject();
            this->instructionSets.push_back(InstructionSet());

            ui->instructionSetList->addItem(instructionSet["SetName"].toString());

            this->instructionSets[i].setName = instructionSet["SetName"].toString();
            this->instructionSets[i].setDescription = instructionSet["SetDescription"].toString();

            QJsonArray instructions = instructionSet["Instructions"].toArray();

            foreach (const QJsonValue& instructions, instructions)
            {
                this->instructionSets[i].instructions.push_back(Instruction::JSONToInstruction(instructions.toObject()));
            }

            i++;
        }

        // Reset back to the first set in the json file
        if(instructionSets.size() == 1)
        {
            ui->instructionSetList->currentIndexChanged(0);
        }
        else
        {
            ui->instructionSetList->setCurrentIndex(0);
        }


        ui->instructionList->setEnabled(true);
    }
    else
    {
        this->jsonDocument = new QJsonDocument();

        ui->modifyInstruction->hide();
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
    if(cwManagerMicroCode == nullptr)
    {
        cwManagerMicroCode = new ControlWordManager(this, arg1);
    }
    else
    {
        cwManagerMicroCode->setTStateCount(arg1);
    }

    ui->scrollArea->setWidget(cwManagerMicroCode);
}

void MainWindow::on_addInstruction_pressed()
{
    if(instructionSets.isEmpty())
    {
        CreationDialog setDialog;

        int result = setDialog.exec();

        if(result == QDialog::Accepted)
        {
            QString name = setDialog.getName();
            QString description = setDialog.getDescription();

            qDebug() << name << description;
        }
        else
        {
            return;
        }
    }


    Instruction instruction;

    instruction.opCode = ui->opCode->text();
    instruction.binCode = ui->binaryCode->text();
    instruction.TStates = ui->tStates->value();
    instruction.affectsFlags = ui->affectsFlags->isChecked();
    instruction.addressingMode = (AddressingMode)ui->addressingMode->currentIndex();
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

    ui->instructionList->blockSignals(true);

    ui->instructionList->clear();
    ui->instructionList->addItem("-- Select Instruction --");
    foreach(const Instruction& instruction, instructionSets[index].instructions)
    {
        ui->instructionList->addItem(instruction.opCode);
    }

    ui->instructionList->blockSignals(false);
}

void MainWindow::on_modifyInstruction_pressed()
{
    ui->instructionSetGroupBox->show();
}

void MainWindow::on_instructionList_currentIndexChanged(int index)
{
    Instruction chosenInstruction = instructionSets[instructionSetNumber].instructions[index - 1]; // - 1 because of the first fill slot

    cwManagerMicroCode = new ControlWordManager(this, chosenInstruction.TStates);
    cwManagerMicroCode->setControlWords(chosenInstruction.microCode);

    ui->opCode->setText(chosenInstruction.opCode);
    ui->binaryCode->setText(chosenInstruction.binCode);
    ui->tStates->setValue(chosenInstruction.TStates);
    ui->affectsFlags->setChecked(chosenInstruction.affectsFlags);
    ui->addressingMode->setCurrentIndex((int)chosenInstruction.addressingMode);
    ui->byteCount->setValue(chosenInstruction.bytes);

//    ui->scrollArea->setWidget(cwManagerMicroCode);
}
