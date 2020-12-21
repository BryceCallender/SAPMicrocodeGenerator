#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include "mainwindow.h"

#include <QWidget>

namespace Ui {
class StartWindow;
}

class StartWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StartWindow(QWidget *parent = nullptr);
    ~StartWindow();

private slots:
    void on_startNew_pressed();

    void on_resume_pressed();

private:
    Ui::StartWindow *ui;
    MainWindow* mainWindow;
};

#endif // STARTWINDOW_H
