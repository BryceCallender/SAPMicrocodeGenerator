#ifndef CONTROLWORDMANAGER_H
#define CONTROLWORDMANAGER_H

#include "ControlWord.h"

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QSpinBox>
#include <QScrollArea>
#include <QVector>
#include <GridLayoutUtil.h>

class ControlWordManager : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWordManager(QWidget* parent = nullptr, int tStates = 3);
    QVector<QString> convertControlWordToString();
    void setControlWords(const QVector<QString>& words);
    void setTStateCount(const int count);
private:
    void generateControlWordLayout();
    void cleanUpLayout();
    void saveChange(int tState, const QString& key, QVariant value);

    QVector<ControlWord*> controlWords;
    QGridLayout *gridLayout;

    const int MAX_JUMP_NUMBER = 8;
    const int MAX_ALU_NUMBER = 32;
    const int NEW_COLUMN_COUNT = 15;

    int row;
    int column;

    int currentTState;
    int tStates;
};

#endif // CONTROLWORDMANAGER_H
