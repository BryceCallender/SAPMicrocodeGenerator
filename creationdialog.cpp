#include "creationdialog.h"
#include "ui_creationdialog.h"

CreationDialog::CreationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreationDialog)
{
    ui->setupUi(this);

    setWindowTitle("Instruction Set Creation");

    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

QString CreationDialog::getName()
{
    return ui->setName->text();
}

QString CreationDialog::getDescription()
{
    return ui->setDescription->toPlainText();
}

CreationDialog::~CreationDialog()
{
    delete ui;
}

void CreationDialog::on_setName_textChanged(const QString &arg1)
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(!arg1.isEmpty());
}
