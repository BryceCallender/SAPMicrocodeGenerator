#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controlwordmanager.h"
#include "Instruction.h"
#include "jsonpreview.h"

#include <QMainWindow>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QFileDialog>
#include <QStandardPaths>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_showFetchCycle_toggled(bool checked);

    void on_save_pressed();

    void on_addInstruction_pressed();

    void on_tStates_valueChanged(int arg1);

    void on_preview_pressed();

private:
    Ui::MainWindow *ui;
    QJsonDocument *jsonDocument;

    QVector<QJsonObject> instructions;

    ControlWordManager* cwManagerMicroCode;
    ControlWordManager* cwManagerFetchCycle;

    JSONPreview* jsonPreviewWindow;
};
#endif // MAINWINDOW_H
