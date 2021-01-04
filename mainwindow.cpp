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
                this->instructionSets[i].instructions.push_back(Instruction::fromJson(instructions.toObject()));
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

        ui->currentSetLabel->setText(QString("<h2>Current Instruction Set:") + " <span style='color:#4CAF50'> " + this->instructionSets[instructionSetNumber].setName + "</span></h2>");

        ui->instructionList->setEnabled(true);
        ui->instructionListLabel->setEnabled(true);
    }
    else
    {
        this->jsonDocument = new QJsonDocument();

        ui->modifyInstruction->hide();
        ui->currentSetLabel->hide();
    }


    // Set up manager for updated fetch's that could be used later
    cwManagerFetchCycle = new ControlWordManager(this, 3);
    QVector<QString> fetchCycleInit = {"", "", ""}; //dummy object to force it to use the fetch cycle inits on the buttons/spin boxes
    cwManagerFetchCycle->setControlWords(fetchCycleInit);
    ui->fetchCycleScrollArea->setWidget(cwManagerFetchCycle);

    // All the UI components being hidden
    ui->fetchCycle->hide();
    ui->instructionSetGroupBox->hide();

    // Make sure nothing is focused
    setFocus();

    restoreGeometry(SettingsManager::getInstance()->getValue("ui/maingeometry").toByteArray());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug() << "Saved window geometry";

    SettingsManager::getInstance()->saveValue("ui", "mainGeometry", this->geometry());

    QWidget::closeEvent(event);
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
            InstructionSet newInstructionSet;

            newInstructionSet.setName = setDialog.getName();
            newInstructionSet.setDescription = setDialog.getDescription();

            instructionSets.push_back(newInstructionSet);
        }
        else
        {
            return;
        }
    }

    Instruction instruction;

    // If an instruction is being modified edit the instruction and not a new instance
    if(currentInstructionIndex != -1)
    {
        instruction = currentInstruction;
    }

    instruction.opCode = ui->opCode->text();
    instruction.binCode = ui->binaryCode->text();
    instruction.TStates = ui->tStates->value();
    instruction.affectsFlags = ui->affectsFlags->isChecked();
    instruction.addressingMode = (AddressingMode)ui->addressingMode->currentIndex();
    instruction.bytes = ui->byteCount->value();

    instruction.microCode = cwManagerMicroCode->convertControlWordToString();

    if(ui->showFetchCycle->isChecked())
    {
        QVector<QString> updatedCycle = cwManagerFetchCycle->convertControlWordToString();

        if(updatedCycle.size() > 0)
        {
            instruction.updatedFetchCycleStates = QVariant::fromValue(updatedCycle);
        }
    }

    if(currentInstructionIndex != -1)
    {
        instructionSets[instructionSetNumber].instructions[currentInstructionIndex] = instruction;
    }
    else
    {
        instructionSets[instructionSetNumber].instructions.push_back(instruction);
    }

    currentInstruction = Instruction();
    currentInstructionIndex = -1;
}

void MainWindow::on_save_pressed()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));

    if(!fileName.contains(".json"))
    {
        fileName = fileName.append(".json");
    }

    QFile file(fileName);
    if(file.open(QFile::WriteOnly))
    {
        QJsonArray instructionSets;

        foreach (InstructionSet instructionSet, this->instructionSets)
        {
            instructionSets.push_back(instructionSet.toJSON());
        }

        jsonDocument->setArray(instructionSets);
        file.write(jsonDocument->toJson(QJsonDocument::Indented));
    }
}

void MainWindow::on_preview_pressed()
{
    jsonPreviewWindow = new JSONPreview();

    QJsonArray instructionSets;

    foreach (InstructionSet instructionSet, this->instructionSets)
    {
        instructionSets.push_back(instructionSet.toJSON());
    }

    jsonDocument->setArray(instructionSets);

    jsonPreviewWindow->setText(jsonDocument->toJson(QJsonDocument::Indented));
    jsonPreviewWindow->show();
}

void MainWindow::on_instructionSetList_currentIndexChanged(int index)
{
    instructionSetNumber = index;

    ui->currentSetLabel->setText(QString("<h2>Current Instruction Set:") + " <span style='color:#4CAF50'> " + this->instructionSets[instructionSetNumber].setName + "</span></h2>");

    ui->instructionList->blockSignals(true);

    ui->instructionList->clear();
    ui->instructionList->addItem("--Select Instruction--");
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

void MainWindow::clearInstructionUI()
{
    cwManagerMicroCode = new ControlWordManager(this, 3);
    cwManagerFetchCycle = new ControlWordManager(this, 3);

    ui->opCode->setText("");
    ui->binaryCode->setText("");
    ui->tStates->setValue(3);
    ui->affectsFlags->setChecked(false);
    ui->addressingMode->setCurrentIndex(0);
    ui->byteCount->setValue(1);

    ui->showFetchCycle->setChecked(false);

    QVector<QString> fetchCycleInit = {"", "", ""}; //dummy object to force it to use the fetch cycle inits on the buttons/spin boxes
    cwManagerFetchCycle->setControlWords(fetchCycleInit);
}

void MainWindow::on_instructionList_currentIndexChanged(int index)
{
    clearInstructionUI();

    if(index == 0)
    {
        ui->addInstruction->setText("Add Instruction");
        return;
    }

    Instruction chosenInstruction = instructionSets[instructionSetNumber].instructions[index - 1]; // - 1 because of the first fill slot

    currentInstruction = chosenInstruction;
    currentInstructionIndex = index - 1;

    cwManagerMicroCode = new ControlWordManager(this, chosenInstruction.TStates);
    cwManagerMicroCode->setControlWords(chosenInstruction.microCode);

    ui->opCode->setText(chosenInstruction.opCode);
    ui->binaryCode->setText(chosenInstruction.binCode);
    ui->tStates->setValue(chosenInstruction.TStates);
    ui->affectsFlags->setChecked(chosenInstruction.affectsFlags);
    ui->addressingMode->setCurrentIndex((int)chosenInstruction.addressingMode);
    ui->byteCount->setValue(chosenInstruction.bytes);

    ui->addInstruction->setText("Modify Instruction");
}

void MainWindow::on_addSetButton_pressed()
{
    CreationDialog setDialog;

    int result = setDialog.exec();

    if(result == QDialog::Accepted)
    {
        InstructionSet newInstructionSet;

        newInstructionSet.setName = setDialog.getName();
        newInstructionSet.setDescription = setDialog.getDescription();

        instructionSets.push_back(newInstructionSet);

        ui->modifyInstruction->show();

        ui->instructionList->setEnabled(true);
        ui->instructionListLabel->setEnabled(true);

        ui->instructionSetList->blockSignals(true);
        ui->instructionSetList->addItem(newInstructionSet.setName);
        ui->instructionSetList->blockSignals(false);
    }
    else
    {
        ui->addSetButton->setChecked(false);
        return;
    }
}
