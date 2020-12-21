#include "controlwordmanager.h"

#include <QLabel>
#include <QDebug>

ControlWordManager::ControlWordManager(QWidget* parent, int tStates) : QWidget(parent)
{
    gridLayout = new QGridLayout();

    gridLayout->setHorizontalSpacing(0);

    row = 0;
    column = 0;
    currentTState = 1;

    // Set up all control word values to NOP
    for (int i = 0; i < tStates; i++)
    {
        controlWords.push_back(new ControlWord());
    }

    for (ControlWord* cw : qAsConst(controlWords))
    {
        column = 0;
        QLabel* label = new QLabel(QString("T" + QString::number(currentTState)));
        label->setAlignment(Qt::AlignCenter);
        gridLayout->addWidget(label, row, column);
        row++;
        currentTState++;

        for(QPair<QString, QVariant>& pair : *cw->controlWordList)
        {
            if(column == NEW_COLUMN_COUNT)
            {
                row++;
                column = 0;
            }

            if(pair.second.type() == QVariant::Bool)
            {
                QPushButton* pushButton = new QPushButton(pair.first);

                pushButton->setCheckable(true);

                pushButton->setChecked(pair.second.toBool());

                gridLayout->addWidget(pushButton, row, column);
                column++;
            }
            else
            {
                QLabel* label = new QLabel(pair.first);
                QSpinBox* spinBox = new QSpinBox();

                spinBox->setValue(0);
                spinBox->setMinimum(0);
                spinBox->setSingleStep(1);

                if(pair.first == "ALU")
                {
                    spinBox->setMaximum(MAX_ALU_NUMBER);
                }
                else if(pair.first == "JC")
                {
                    spinBox->setMaximum(MAX_JUMP_NUMBER);
                }

                gridLayout->addWidget(label, row, column);
                column++;
                gridLayout->addWidget(spinBox, row, column);
                column++;
            }
        }
        row++;

        // Adds a seperator line between each t State control word section
        if(currentTState <= tStates)
        {
            for(int i = 0; i < NEW_COLUMN_COUNT; i++)
            {
                QFrame* line = new QFrame();
                line->setFrameShape(QFrame::HLine);
                line->setFrameShadow(QFrame::Sunken);
                gridLayout->addWidget(line, row, i);
            }
        }

        row++;
    }

    setLayout(gridLayout);
    //parent->setLayout(gridLayout);
}

QVector<QString> ControlWordManager::convertControlWordToString()
{
    QVector<QString> binary;
    QString binaryBuilder;

    for (auto cw : qAsConst(controlWords))
    {
        for(const auto &pair : qAsConst(*cw->controlWordList))
        {
            int value = pair.second.toInt();
            QString binValue = QString::number(value, 2);

            if(pair.first == "ALU")
            {
                binValue = binValue.rightJustified(5, '0');
            }
            else if(pair.first == "JC")
            {
                binValue = binValue.rightJustified(3, '0');
            }

            binaryBuilder.append(binValue);
        }

        binary.push_back(binaryBuilder);
    }

    return binary;
}
