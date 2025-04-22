#pragma once

#include <QMainWindow>
#include "ChatManager.h"

class QTextEdit;
class QLineEdit;
class QPushButton;

class ChatWindow : public QMainWindow {
    Q_OBJECT
public:
    explicit ChatWindow(QWidget* parent = nullptr);

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

    void appendToView(const ChatMessage& msg);
};