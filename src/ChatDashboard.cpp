#include "ChatDashboard.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>

ChatDashboard::ChatDashboard(QWidget* parent) : BaseDashboard(parent) {
    setupUI();
    
    connect(&m_chat, &ChatManager::messageAppended, this, &ChatDashboard::onMessageAppended);
    connect(&m_chat, &ChatManager::errorOccurred, this, [this](const QString& err){
        appendToView({"system", QStringLiteral("[Error] %1").arg(err)});
    });

    // Load previous history into the view
    for (const ChatMessage& m : m_chat.history()) {
        appendToView(m);
    }
}

void ChatDashboard::setupUI() {
    m_view = new QTextEdit(this);
    m_view->setReadOnly(true);

    m_input = new QLineEdit(this);
    m_sendBtn = new QPushButton("Send", this);
    m_newChatBtn = new QPushButton("New Chat", this);

    QHBoxLayout* inputLayout = new QHBoxLayout;
    inputLayout->addWidget(m_input);
    inputLayout->addWidget(m_sendBtn);
    inputLayout->addWidget(m_newChatBtn);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(m_view);
    mainLayout->addLayout(inputLayout);

    connect(m_sendBtn, &QPushButton::clicked, this, &ChatDashboard::onSendClicked);
    connect(m_newChatBtn, &QPushButton::clicked, this, &ChatDashboard::onNewChatClicked);
    connect(m_input, &QLineEdit::returnPressed, this, &ChatDashboard::onSendClicked);
}

void ChatDashboard::onActivate() {
    // Focus the input when this dashboard becomes active
    m_input->setFocus();
}

void ChatDashboard::onDeactivate() {
    // Optional: perform any cleanup when dashboard is hidden
}

void ChatDashboard::onSendClicked() {
    const QString text = m_input->text().trimmed();
    if (text.isEmpty()) return;
    m_input->clear();
    m_chat.sendUserMessage(text);
}

void ChatDashboard::onNewChatClicked() {
    m_chat.newChat();
    m_view->clear();
}

void ChatDashboard::onMessageAppended(const ChatMessage& msg) {
    appendToView(msg);
}

void ChatDashboard::appendToView(const ChatMessage& msg) {
    static const QHash<QString, QString> colorFor{{"user", "#1e90ff"}, {"assistant", "#32cd32"}, {"system", "#ff4500"}};
    const QString color = colorFor.value(msg.role, "#ffffff");
    m_view->append(QString("<b><font color='%1'>%2:</font></b> %3").arg(color, msg.role, msg.content.toHtmlEscaped()));
}