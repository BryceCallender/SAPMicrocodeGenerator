#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QString>
#include <QList>
#include <QVariant>

enum AddressingMode
{
    Register,
    Immediate,
    Direct,
    Implied,
    None
};


struct Instruction
{
    QString opCode;
    QString binCode;
    int TStates;
    bool affectsFlags;
    AddressingMode addressingMode;
    int bytes;
    QList<QString> microCode;
    QVariant updatedFetchCycleStates;
};

#endif // INSTRUCTION_H
