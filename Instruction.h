#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QString>
#include <QVector>
#include <QVariant>
#include <QJsonObject>
#include <QJsonArray>
#include <QMetaEnum>



class Instruction : public QObject
{
    Q_OBJECT
public:
    enum AddressingMode
    {
        Register,
        Immediate,
        Direct,
        Implied,
        None
    };
    Q_ENUM(AddressingMode)

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
        instructionJSON["AddressingMode"] = QMetaEnum::fromType<AddressingMode>().valueToKey(addressingMode);

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
};

#endif // INSTRUCTION_H
