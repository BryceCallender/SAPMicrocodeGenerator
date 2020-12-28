#include "settingsmanager.h"

#include <QStandardPaths>
#include <QDebug>

bool SettingsManager::created = false;
SettingsManager* SettingsManager::instance = nullptr;

SettingsManager::SettingsManager()
{
    //Required to be set in order to use the QSettings!
    QCoreApplication::setOrganizationName("SAP1EMU");
    QCoreApplication::setApplicationName("SAPMicroCodeGenerator");

    settings = new QSettings();

    qDebug() << QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
}

SettingsManager::~SettingsManager()
{
    settings->sync();
    qDebug() << "Saving...";
    delete settings;
}

void SettingsManager::saveSettings()
{
    settings->sync();
}

QVariant SettingsManager::getValue(const QString &key)
{
    if(key.contains("mainGeometry"))
    {
        return settings->value(key, QRect(0,0,1321,862)); //hard code values that make it nice
    }

    return QVariant();
}

void SettingsManager::saveValue(const QString &groupName, const QString &name, const QVariant &data)
{
    settings->beginGroup(groupName);
        settings->setValue(name, data);
    settings->endGroup();
}
