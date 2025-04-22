#include "ChatWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>

ChatWindow::ChatWindow(QWidget* parent) : QMainWindow(parent) {
    QWidget* central = new QWidget(this);
    setCentralWidget(central);

    m_view = new QTextEdit(this);
    m_view->setReadOnly(true);

    m_input = new QLineEdit(this);
    m_sendBtn = new QPushButton("Send", this);
    m_newChatBtn = new QPushButton("New Chat", this);

    QHBoxLayout* inputLayout = new QHBoxLayout;
    inputLayout->addWidget(m_input);
    inputLayout->addWidget(m_sendBtn);
    inputLayout->addWidget(m_newChatBtn);

    QVBoxLayout* mainLayout = new QVBoxLayout(central);
    mainLayout->addWidget(m_view);
    mainLayout->addLayout(inputLayout);

    connect(m_sendBtn, &QPushButton::clicked, this, &ChatWindow::onSendClicked);
    connect(m_newChatBtn, &QPushButton::clicked, this, &ChatWindow::onNewChatClicked);
    connect(&m_chat, &ChatManager::messageAppended, this, &ChatWindow::onMessageAppended);
    connect(&m_chat, &ChatManager::errorOccurred, this, [this](const QString& err){
        appendToView({"system", QStringLiteral("[Error] %1").arg(err)});
    });

    // Load previous history into the view
    for (const ChatMessage& m : m_chat.history()) {
        appendToView(m);
    }

    setWindowTitle("Ollama Chat");
    resize(600, 800);
}

void ChatWindow::onSendClicked() {
    const QString text = m_input->text().trimmed();
    if (text.isEmpty()) return;
    m_input->clear();
    m_chat.sendUserMessage(text);
}

void ChatWindow::onNewChatClicked() {
    m_chat.newChat();
    m_view->clear();
}

void ChatWindow::onMessageAppended(const ChatMessage& msg) {
    appendToView(msg);
}

void ChatWindow::appendToView(const ChatMessage& msg) {
    static const QHash<QString, QString> colorFor{{"user", "#1e90ff"}, {"assistant", "#32cd32"}, {"system", "#ff4500"}};
    const QString color = colorFor.value(msg.role, "#ffffff");
    m_view->append(QString("<b><font color='%1'>%2:</font></b> %3").arg(color, msg.role, msg.content.toHtmlEscaped()));
}
