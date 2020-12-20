#ifndef CONTROLWORDMANAGER_H
#define CONTROLWORDMANAGER_H

#include "ControlWord.h"

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QSpinBox>

class ControlWordManager : public QWidget
{
public:
    explicit ControlWordManager(QWidget* parent = nullptr);
    QString convertControlWordToString();
private:
    ControlWord *controlWord;
    QGridLayout *gridLayout;
    const int MAX_JUMP_NUMBER = 8;
    const int MAX_ALU_NUMBER = 32;
};

#endif // CONTROLWORDMANAGER_H
