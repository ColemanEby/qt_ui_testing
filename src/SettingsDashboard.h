#pragma once

#include "BaseDashboard.h"

class QLineEdit;
class QComboBox;
class QPushButton;
class QFormLayout;

class SettingsDashboard : public BaseDashboard {
    Q_OBJECT
public:
    explicit SettingsDashboard(QWidget* parent = nullptr);
    
    // Override BaseDashboard methods
    QString dashboardName() const override { return "Settings"; }

private slots:
    void onSaveClicked();
    void loadSettings();

private:
    QLineEdit* m_serverUrlEdit;
    QComboBox* m_modelSelect;
    QPushButton* m_saveBtn;
    
    void setupUI();
    void saveSettings();
};