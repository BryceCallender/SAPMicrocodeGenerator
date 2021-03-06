#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controlwordmanager.h"
#include "Instruction.h"
#include "jsonpreview.h"
#include "InstructionSet.h"
#include "creationdialog.h"
#include "settingsmanager.h"

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QFileDialog>
#include <QStandardPaths>
#include <QVector>
#include <QMessageBox>
#include <QInputDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, QJsonDocument* jsonDocument = nullptr);
    void closeEvent(QCloseEvent *event);
    ~MainWindow();

private slots:
    void on_showFetchCycle_toggled(bool checked);

    void on_save_pressed();

    void on_addInstruction_pressed();

    void on_tStates_valueChanged(int arg1);

    void on_preview_pressed();

    void on_instructionSetList_currentIndexChanged(int index);

    void on_modifyInstruction_pressed();

    void on_instructionList_currentIndexChanged(int index);

    void on_addSetButton_pressed();

private:
    void clearInstructionUI();


    Ui::MainWindow *ui;
    QJsonDocument* jsonDocument;

    QVector<InstructionSet> instructionSets;

    ControlWordManager* cwManagerMicroCode;
    ControlWordManager* cwManagerFetchCycle;

    JSONPreview* jsonPreviewWindow;

    int instructionSetNumber = 0;

    Instruction currentInstruction;
    int currentInstructionIndex = -1;
};
#endif // MAINWINDOW_H
