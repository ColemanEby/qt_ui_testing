#include "SettingsDashboard.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QSettings>
#include <QGroupBox>

SettingsDashboard::SettingsDashboard(QWidget* parent) : BaseDashboard(parent) {
    setupUI();
    loadSettings();
}

void SettingsDashboard::setupUI() {
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    // Server settings group
    QGroupBox* serverGroup = new QGroupBox("Server Settings", this);
    QFormLayout* serverForm = new QFormLayout(serverGroup);
    
    m_serverUrlEdit = new QLineEdit(this);
    m_serverUrlEdit->setPlaceholderText("http://localhost:11434");
    serverForm->addRow("Ollama Server URL:", m_serverUrlEdit);
    
    // Model settings group
    QGroupBox* modelGroup = new QGroupBox("Model Settings", this);
    QFormLayout* modelForm = new QFormLayout(modelGroup);
    
    m_modelSelect = new QComboBox(this);
    m_modelSelect->addItems({"mistral-nemo:latest", "llama3:latest", "mixtral:latest", "phi3-mini:latest"});
    m_modelSelect->setEditable(true);
    modelForm->addRow("Default Model:", m_modelSelect);
    
    // Add groups to main layout
    mainLayout->addWidget(serverGroup);
    mainLayout->addWidget(modelGroup);
    
    // Save button at the bottom
    m_saveBtn = new QPushButton("Save Settings", this);
    mainLayout->addWidget(m_saveBtn);
    
    // Add stretch to push everything to the top
    mainLayout->addStretch(1);
    
    // Connect signals and slots
    connect(m_saveBtn, &QPushButton::clicked, this, &SettingsDashboard::onSaveClicked);
}

void SettingsDashboard::loadSettings() {
    QSettings settings;
    
    // Load server URL (default to localhost if not set)
    QString serverUrl = settings.value("server/url", "http://localhost:11434").toString();
    m_serverUrlEdit->setText(serverUrl);
    
    // Load default model
    QString model = settings.value("model/default", "mistral-nemo:latest").toString();
    m_modelSelect->setCurrentText(model);
}

void SettingsDashboard::saveSettings() {
    QSettings settings;
    
    // Save server settings
    settings.setValue("server/url", m_serverUrlEdit->text());
    
    // Save model settings
    settings.setValue("model/default", m_modelSelect->currentText());
    
    settings.sync();
}

void SettingsDashboard::onSaveClicked() {
    saveSettings();
    emit statusMessage("Settings saved successfully");
}