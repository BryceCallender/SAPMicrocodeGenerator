#ifndef CREATIONDIALOG_H
#define CREATIONDIALOG_H

#include <QDialog>
#include <QPushButton>

namespace Ui {
class CreationDialog;
}

class CreationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreationDialog(QWidget *parent = nullptr);
    QString getName();
    QString getDescription();
    ~CreationDialog();

private slots:
    void on_setName_textChanged(const QString &arg1);

private:
    Ui::CreationDialog *ui;
};

#endif // CREATIONDIALOG_H
