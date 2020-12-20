#include "controlwordmanager.h"

ControlWordManager::ControlWordManager(QWidget* parent) : QWidget(parent)
{
    controlWord = new ControlWord();

    gridLayout = new QGridLayout(parent);

    for (QPair<QString, QVariant>& pair : *controlWord->controlWordList)
    {
        if(pair.second.type() == QVariant::Bool)
        {
            QPushButton* widget = new QPushButton(pair.first);

            widget->setCheckable(true);

            gridLayout->addWidget(widget);
        }
        else
        {
            QSpinBox* widget = new QSpinBox();

            widget->setValue(0);
            widget->setMinimum(0);
            widget->setSingleStep(1);

            if(pair.first == "ALU")
            {
                widget->setMaximum(MAX_ALU_NUMBER);
            }
            else if(pair.first == "JC")
            {
                widget->setMaximum(MAX_JUMP_NUMBER);
            }

            gridLayout->addWidget(widget);
        }
    }
}

QString ControlWordManager::convertControlWordToString()
{
    QString binary;

    for (QPair<QString, QVariant>& pair : *controlWord->controlWordList)
    {
        int value = pair.second.toInt();
        binary.append(QString::number(value, 2));
    }

    return binary;
}
