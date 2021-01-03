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

    this->tStates = tStates;

    // Set up all control word values to NOP
    for (int i = 0; i < tStates; i++)
    {
        controlWords.push_back(new ControlWord());
    }

    generateControlWordLayout();
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
        binaryBuilder = "";
    }

    return binary;
}

void ControlWordManager::setControlWords(QVector<QString>& words)
{
    for(int i = 0; i < words.size(); i++)
    {
        if(words[i] == "" && i < 3)
        {
            words[i] = fetchCycle[i];
        }
        else if(words[i] == "")
        {
            continue;
        }
        controlWords[i]->setControlWord(words[i]);
    }

    generateControlWordLayout();
}

void ControlWordManager::setTStateCount(const int count)
{
    int beforeSize = controlWords.size();

    if(beforeSize < count)
    {
        controlWords.push_back(new ControlWord());
    }
    else
    {
        controlWords.resize(count);
    }

    tStates = count;

    generateControlWordLayout();
}

void ControlWordManager::generateControlWordLayout()
{
    cleanUpLayout();

    for (ControlWord* cw : qAsConst(controlWords))
    {
        column = 0;
        QLabel* label = new QLabel(QString("T" + QString::number(currentTState)));
        label->setAlignment(Qt::AlignCenter);
        gridLayout->addWidget(label, row, column);
        row++;

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

                int state = currentTState;
                connect(pushButton, &QPushButton::released, [this, pushButton, state]()
                {
                    saveChange(state, pushButton->text(), pushButton->isChecked());
                });

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

                spinBox->setValue(pair.second.toInt());

                gridLayout->addWidget(label, row, column);
                column++;
                gridLayout->addWidget(spinBox, row, column);

                int state = currentTState;
                connect(spinBox, QOverload<int>::of(&QSpinBox::valueChanged), [this, label, state](int value)
                {
                    saveChange(state, label->text(), value);
                });


                column++;
            }
        }
        row++;

        // Adds a seperator line between each t State control word section
        if(currentTState < tStates)
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
        currentTState++;
    }

    setLayout(gridLayout);
}

void ControlWordManager::cleanUpLayout()
{
    for(int i = 0; i < gridLayout->rowCount(); i++)
    {
        for(int j = 0; j < gridLayout->columnCount(); j++)
        {
            GridLayoutUtil::removeColumn(gridLayout, j);
        }
        GridLayoutUtil::removeRow(gridLayout, i);
    }

    currentTState = 1;
    row = 0;
    column = 0;
}

void ControlWordManager::saveChange(int tState, const QString &key, QVariant value)
{
    ControlWord* cw = controlWords[tState - 1];

    QPair<QString, QVariant> controlSignal;

    int index = 0;
    int foundIndex = -1;
    for (const auto &pair: qAsConst(*cw->controlWordList))
    {
        if(pair.first == key)
        {
            foundIndex = index;
            break;
        }
        index++;
    }

    // Not found
    if(foundIndex == -1)
    {
        return;
    }

    controlSignal = cw->controlWordList[0][foundIndex];

    if(value.type() == QVariant::Bool)
    {
        controlSignal.second = value.toBool();
    }
    else
    {
        controlSignal.second = value.toInt();
    }

    cw->controlWordList[0][foundIndex] = controlSignal;
}
