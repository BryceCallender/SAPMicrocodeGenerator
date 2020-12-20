#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controlwordmanager.h"

#include <QMainWindow>
#include <QJsonDocument>

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

private:
    Ui::MainWindow *ui;
    QJsonDocument *jsonDocument;
    QVector<ControlWordManager> *microCode;
    QVector<ControlWordManager> *updatedFetchCycleCode;
};
#endif // MAINWINDOW_H
