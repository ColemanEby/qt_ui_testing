#include <QApplication>
#include "MainWindow.h"
#include "ChatDashboard.h"
#include "SettingsDashboard.h"

int main(int argc, char** argv) {
    QApplication app(argc, argv);
    
    // Set application metadata
    app.setApplicationName("Ollama Qt Chat");
    app.setOrganizationName("OllamaQtChat");
    
    // Create main window
    MainWindow w;
    
    // Add dashboards
    w.addDashboard(new ChatDashboard(&w), "Chat", "chat");
    w.addDashboard(new SettingsDashboard(&w), "Settings", "settings");
    
    w.show();
    return app.exec();
}