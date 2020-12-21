#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    setWindowTitle("SAP Microcode Generator");
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::on_startNew_pressed()
{
    this->close();
    mainWindow = new MainWindow();
    mainWindow->show();
}

void StartWindow::on_resume_pressed()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), QStandardPaths::writableLocation(QStandardPaths::DesktopLocation), tr("JSON Files (*.json)"));

    QFile file(fileName);

    QJsonParseError parseError;

    if(!file.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, "Couldn't open file", "Could not open the desired file", QMessageBox::Ok);
        return;
    }

    QJsonDocument jsonDocument = QJsonDocument::fromJson(file.readAll(), &parseError);

    this->close();
    mainWindow = new MainWindow(nullptr, &jsonDocument);
    mainWindow->show();
}
