#ifndef SETTINGSMANAGER_H
#define SETTINGSMANAGER_H

#include <QCoreApplication>
#include <QSettings>
#include <QRect>
#include <QColor>
#include <QFont>

/*! \class SettingsManager
    \brief Manages user settings for this application.

    This class is responsible for displaying and saving the users preferences. It is a singleton class structure
 */
class SettingsManager
{
public:
    //! Save Settings
    /*!
      Will sync all the settings to the save location in order to reflect the changes
     */
     void saveSettings();


    //! Saved Value Retrieval
    /*!
      Retrieves the value associated with the key
      \param key the key to search for and return its value as a QVariant
     */
    QVariant getValue(const QString& key);

    //! Save
    /*!
      Saves the specified data in the group and under the key
      \param groupName The grouping name like /code or /text
      \param name The name of the key
      \param data The data to save at the specified group and key
     */
    void saveValue(const QString& groupName, const QString &name, QVariant data);


    //! Singleton Instance
    /*!
      Manages creating and grabbing of the singleton instance
     */
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

    static bool created; /*!< If we have created an instance of this class yet. */
    static SettingsManager* instance; /*!< Singleton instance to allow querying the class. */
    QSettings* settings; /*!< QSettings is how we do crossplatform saving. */
};

#endif // SETTINGSMANAGER_H
