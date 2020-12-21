#ifndef INSTRUCTIONSET_H
#define INSTRUCTIONSET_H

#include "Instruction.h"

#include <QString>
#include <QVector>

struct InstructionSet
{
    QString setName;
    QString setDescription;
    QVector<Instruction> instructions;
};

#endif // INSTRUCTIONSET_H
