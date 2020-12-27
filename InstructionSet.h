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

    QJsonObject toJSON()
    {
        QJsonObject json;

        json["SetName"] = setName;
        json["SetDescription"] = setDescription;

        QJsonArray instructionsArray;

        foreach (Instruction instruction, instructions)
        {
           instructionsArray.push_back(instruction.toJSON());
        }

        json["Instructions"] = instructionsArray;

        return json;
    }
};

#endif // INSTRUCTIONSET_H
