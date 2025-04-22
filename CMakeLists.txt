cmake_minimum_required(VERSION 3.24)
project(OllamaQtChatApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets Network)

set(CMAKE_AUTOMOC ON)              # <‑‑ here (or qt_standard_project_setup())

add_executable(OllamaQtChatApp
    src/main.cpp
    src/MainWindow.cpp
    src/MainWindow.h
    src/BaseDashboard.cpp
    src/BaseDashboard.h
    src/ChatDashboard.cpp
    src/ChatDashboard.h
    src/SettingsDashboard.cpp
    src/SettingsDashboard.h
    src/ChatManager.cpp
    src/ChatManager.h
    src/ChatMessage.h
    src/SettingsManager.cpp
    src/SettingsManager.h
)

# Link Qt libraries
target_link_libraries(OllamaQtChatApp
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
)