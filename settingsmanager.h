#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QCoreApplication>
#include <QSettings>
#include <QRect>
#include <QColor>
#include <QFont>

class SettingsManager
{
public:
    void saveSettings();
    QVariant getValue(const QString& key);
    void saveValue(const QString& groupName, const QString &name, const QVariant& data);

    static SettingsManager* getInstance()
    {
        if (!created)
        {
            instance = new SettingsManager();
            created = true;
            return instance;
        }
        else
        {
            return instance;
        }
    }
private:
    SettingsManager();
    ~SettingsManager();

    static bool created;
    static SettingsManager* instance;
    QSettings* settings;
};

#endif // SETTINGSMANAGER_H
