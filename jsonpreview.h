#ifndef JSONPREVIEW_H
#define JSONPREVIEW_H

#include <QWidget>

namespace Ui {
class JSONPreview;
}

class JSONPreview : public QWidget
{
    Q_OBJECT

public:
    explicit JSONPreview(QWidget *parent = nullptr);
    void setText(QByteArray json);
    ~JSONPreview();

private:
    Ui::JSONPreview *ui;
};

#endif // JSONPREVIEW_H
