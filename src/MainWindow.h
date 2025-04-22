#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include <QToolBar>
#include <QHash>
#include <QString>

// Forward declarations
class QAction;
class BaseDashboard;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

    // Add a dashboard to the main window
    void addDashboard(BaseDashboard* dashboard, const QString& name, const QString& iconName = QString());

private slots:
    void onActionTriggered(QAction* action);

private:
    QToolBar* m_navBar;
    QStackedWidget* m_stack;
    QHash<QAction*, int> m_actionToIndexMap;

    void setupUI();
};