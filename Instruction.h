#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QString>
#include <QVector>
#include <QVariant>
#include <QJsonObject>
#include <QJsonArray>
#include <QMetaEnum>

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
    QVector<QString> microCode;
    QVariant updatedFetchCycleStates;

    QJsonObject convertToJSON()
    {
        QJsonObject instructionJSON;

        instructionJSON["OpCode"] = opCode;
        instructionJSON["BinCode"] = binCode;
        instructionJSON["TStates"] = TStates;
        instructionJSON["AffectsFlags"] = affectsFlags;
        instructionJSON["AddressingMode"] = enumToString(addressingMode);

        QJsonArray microCodeArray;

        foreach (const QString code, microCode)
        {
           microCodeArray.push_back(code);
        }

        instructionJSON["MicroCode"] = microCodeArray;

        QJsonArray fetchCycleArray;

        foreach (const QVariant code, updatedFetchCycleStates.toList())
        {
           fetchCycleArray.push_back(code.toString());
        }

        if(fetchCycleArray.size() > 0)
        {
            instructionJSON["UpdatedFetchCycleStates"] = fetchCycleArray;
        }

        return instructionJSON;
    }

    QString enumToString(AddressingMode addressingMode)
    {
        switch(addressingMode)
        {
            case Register: return "Register";
            case Immediate: return "Immediate";
            case Direct: return "Direct";
            case Implied: return "Implied";
            case None: return "None";
        }
    }
};

#endif // INSTRUCTION_H
