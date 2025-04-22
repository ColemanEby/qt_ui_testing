#include "SettingsManager.h"
#include <QSettings>

SettingsManager& SettingsManager::instance() {
    static SettingsManager instance;
    return instance;
}

SettingsManager::SettingsManager(QObject* parent) : QObject(parent) {
    // Initialize defaults if needed
}

QString SettingsManager::serverUrl() const {
    QSettings settings;
    return settings.value("server/url", "http://localhost:11434").toString();
}

void SettingsManager::setServerUrl(const QString& url) {
    QSettings settings;
    settings.setValue("server/url", url);
    settings.sync();
    emit settingsChanged();
}

QString SettingsManager::defaultModel() const {
    QSettings settings;
    return settings.value("model/default", "mistral-nemo:latest").toString();
}

void SettingsManager::setDefaultModel(const QString& model) {
    QSettings settings;
    settings.setValue("model/default", model);
    settings.sync();
    emit settingsChanged();
}