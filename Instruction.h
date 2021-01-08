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

    QJsonObject toJSON()
    {
        QJsonObject instructionJSON;

        instructionJSON["OpCode"] = opCode;
        instructionJSON["BinCode"] = binCode;
        instructionJSON["TStates"] = TStates;
        instructionJSON["AffectsFlags"] = affectsFlags;
        instructionJSON["AddressingMode"] = enumToString(addressingMode);
        instructionJSON["Bytes"] = bytes;

        QJsonArray microCodeArray;

        foreach (const QString code, microCode)
        {
           microCodeArray.push_back(code);
        }

        instructionJSON["MicroCode"] = microCodeArray;

        QJsonArray fetchCycleArray;

        foreach (const QVariant& code, updatedFetchCycleStates.toList())
        {
           fetchCycleArray.push_back(code.toString());
        }

        if(fetchCycleArray.size() > 0)
        {
            instructionJSON["UpdatedFetchCycleStates"] = fetchCycleArray;
        }

        return instructionJSON;
    }

    static Instruction fromJson(const QJsonObject& json)
    {
        Instruction instruction;

        instruction.opCode = json["OpCode"].toString();
        instruction.binCode = json["BinCode"].toString();
        instruction.TStates = json["TStates"].toInt();
        instruction.affectsFlags = json["AffectsFlags"].toBool();
        instruction.addressingMode = stringToEnum(json["AddressingMode"].toString());
        instruction.bytes = json["Bytes"].toInt();

        QJsonArray binary = json["MicroCode"].toArray();

        foreach (const QJsonValue &bin, binary)
        {
            instruction.microCode.push_back(bin.toString());
        }

        if(json.contains("UpdatedFetchCycleStates"))
        {
            instruction.updatedFetchCycleStates = json["UpdatedFetchCycleStates"].toVariant();
        }

        return instruction;
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
            default: return "None";
        }
    }

    static AddressingMode stringToEnum(QString addressingMode)
    {
        if(addressingMode == "Register")
        {
            return Register;
        }
        else if(addressingMode == "Immediate")
        {
            return Immediate;
        }
        else if(addressingMode == "Direct")
        {
            return Direct;
        }
        else if(addressingMode == "Implied")
        {
            return Implied;
        }
        else
        {
            return None;
        }
    }
};

#endif // INSTRUCTION_H
