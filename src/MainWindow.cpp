#include "MainWindow.h"
#include "BaseDashboard.h"
#include <QAction>
#include <QIcon>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setupUI();
    resize(800, 600);
    setWindowTitle("Ollama UI");
}

MainWindow::~MainWindow() {
    // The QObject parent-child mechanism will handle widget cleanup
}

void MainWindow::setupUI() {
    // Create the navigation bar (top toolbar)
    m_navBar = new QToolBar("Navigation", this);
    m_navBar->setMovable(false);
    m_navBar->setIconSize(QSize(32, 32));
    m_navBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    addToolBar(Qt::TopToolBarArea, m_navBar);
    
    // Create stacked widget to hold all dashboards
    m_stack = new QStackedWidget(this);
    setCentralWidget(m_stack);
    
    // Connect signals and slots
    connect(m_navBar, &QToolBar::actionTriggered, this, &MainWindow::onActionTriggered);
}

void MainWindow::addDashboard(BaseDashboard* dashboard, const QString& name, const QString& iconName) {
    // Add the dashboard to the stack
    int index = m_stack->addWidget(dashboard);
    
    // Create an action for the navigation bar
    QAction* action = new QAction(name, this);
    if (!iconName.isEmpty()) {
        action->setIcon(QIcon::fromTheme(iconName, QIcon(":/icons/" + iconName + ".png")));
    }
    
    // Map the action to the stack index
    m_actionToIndexMap[action] = index;
    
    // Add action to the navigation bar
    m_navBar->addAction(action);
    
    // Initialize with the first dashboard
    if (m_stack->count() == 1) {
        m_stack->setCurrentIndex(0);
        action->setChecked(true);
    }
}

void MainWindow::onActionTriggered(QAction* action) {
    // Switch to the corresponding dashboard
    int index = m_actionToIndexMap.value(action, -1);
    if (index >= 0) {
        m_stack->setCurrentIndex(index);
    }
}