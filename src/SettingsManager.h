#pragma once

#include <QObject>
#include <QString>

// Singleton class to manage application settings
class SettingsManager : public QObject {
    Q_OBJECT
public:
    static SettingsManager& instance();
    
    // Server settings
    QString serverUrl() const;
    void setServerUrl(const QString& url);
    
    // Model settings
    QString defaultModel() const;
    void setDefaultModel(const QString& model);

signals:
    void settingsChanged();

private:
    explicit SettingsManager(QObject* parent = nullptr);
    ~SettingsManager() = default;
    
    // Disable copy/move constructor and assignment operators
    SettingsManager(const SettingsManager&) = delete;
    SettingsManager& operator=(const SettingsManager&) = delete;
    SettingsManager(SettingsManager&&) = delete;
    SettingsManager& operator=(SettingsManager&&) = delete;
};