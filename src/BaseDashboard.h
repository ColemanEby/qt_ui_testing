#pragma once

#include <QWidget>

class BaseDashboard : public QWidget {
    Q_OBJECT
public:
    explicit BaseDashboard(QWidget* parent = nullptr);
    virtual ~BaseDashboard();
    
    // Virtual methods that can be overridden by subclasses
    virtual void onActivate();  // Called when dashboard is shown
    virtual void onDeactivate();  // Called when dashboard is hidden
    virtual QString dashboardName() const = 0;  // Must be implemented by subclasses

signals:
    void statusMessage(const QString& message);
    void titleChanged(const QString& title);
};