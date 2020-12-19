#ifndef CONTROLWORD_H
#define CONTROLWORD_H

#include <QMap>
#include <QString>

class ControlWord
{
public:
    ControlWord();
private:
    QMap<QString, QString> *controlWordMap;
};

#endif // CONTROLWORD_H
