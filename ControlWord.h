#ifndef CONTROLWORD_H
#define CONTROLWORD_H

#include <QMap>
#include <QString>
#include <QVariant>
#include <QPair>
#include <QVector>
#include <QString>

class ControlWord
{
public:
    QVector<QPair<QString, QVariant>> *controlWordList;

    ControlWord()
    {
        controlWordList = new QVector<QPair<QString, QVariant>>(
        {
            { "CP", false },    //Increment PC
            { "EP", false },    //Enable PC
            { "LP_", true },    //Load PC

            { "LI_", true },    //Load IR

            { "EIP1", false },  //Enable Input Port 1
            { "EIP2", false },  //Enable Input Port 2

            { "LM_", true },    //Load RAM (MAR)
            { "EM_", true },    //Enable RAM
            { "LR_", true },    //Load RAM from MDR
            { "LMDR_", true },  //Load Memory Data Register
            { "EMDR", false },  //Enable Memory Data Register

            { "LA_", true },    //Load Accumulator
            { "EA", false },    //Enable Accumulator
            { "LT_", true },    //Load Temp
            { "ET", false },    //Enable Temp
            { "LB_", true },    //Load B
            { "EB", false},     //Enable B
            { "LC_", true },    //Load C
            { "EC", false },    //Enable C
            { "LF", false},     //Load flag
            { "EU", false },    //Enable ALU

            { "LO3_", true },   //Load Output port 3
            { "LO4_", true },   //Load Output port 4

            { "ALU", 0 },       //ALU Control flags
            { "JC", 0 },        //Jump Control flags

            { "UB", false },    //take bus upper byte if on or output to bus upper byte
            { "CLR", false },   //Clear bus value when outputting to bus
            { "RTNA", false }   //Return Address => Marks whether to make MAR point to 0xFFFE or 0xFFFF for pc contents in memory
        });
    }

    void setControlWord(const QString& controlWord)
    {
        int index = 0;
        for(QPair<QString, QVariant>& pair : *controlWordList)
        {
            if(pair.second.type() == QVariant::Bool)
            {
                pair.second = (bool)controlWord[index].digitValue();
                index++;
            }
            else
            {
                int stride = 0;
                if(pair.first == "ALU")
                {
                    stride = 5;
                }
                else
                {
                    stride = 3;
                }

                bool ok;
                pair.second = controlWord.mid(index, stride).toInt(&ok, 2);

                index += stride;
            }
        }
    }

};

#endif // CONTROLWORD_H
