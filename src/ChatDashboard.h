#pragma once

#include "BaseDashboard.h"
#include "ChatManager.h"

class QTextEdit;
class QLineEdit;
class QPushButton;

class ChatDashboard : public BaseDashboard {
    Q_OBJECT
public:
    explicit ChatDashboard(QWidget* parent = nullptr);
    
    // Override BaseDashboard methods
    QString dashboardName() const override { return "Chat"; }
    void onActivate() override;
    void onDeactivate() override;

private slots:
    void onSendClicked();
    void onNewChatClicked();
    void onMessageAppended(const ChatMessage& msg);

private:
    ChatManager m_chat;
    QTextEdit* m_view;
    QLineEdit* m_input;
    QPushButton* m_sendBtn;
    QPushButton* m_newChatBtn;

    void setupUI();
    void appendToView(const ChatMessage& msg);
};