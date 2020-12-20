#include "jsonpreview.h"
#include "ui_jsonpreview.h"

JSONPreview::JSONPreview(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::JSONPreview)
{
    ui->setupUi(this);

    setWindowTitle("JSON Preview");
}

void JSONPreview::setText(QByteArray json)
{
    ui->textEdit->setText(json);
}

JSONPreview::~JSONPreview()
{
    delete ui;
}
