#pragma once

#include <QObject>
#include <QVector>
#include <QNetworkAccessManager>
#include <QStandardPaths>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include "ChatMessage.h"

class ChatManager : public QObject {
    Q_OBJECT
public:
    explicit ChatManager(QObject* parent = nullptr);

    const QVector<ChatMessage>& history() const { return m_history; }

    // Send a user message, the assistant reply will be emitted via messageAppended()
    void sendUserMessage(const QString& text);

    // Start a fresh chat (clears history in‑memory, but previous history remains on disk)
    void newChat();

signals:
    void messageAppended(const ChatMessage& msg);
    void errorOccurred(const QString& error);

private slots:
    void handleReply(QNetworkReply* reply);

private:
    void loadHistory();
    void saveHistory();

    QVector<ChatMessage> m_history;
    QNetworkAccessManager m_net;
    QString m_model = "mistral-nemo:latest";                // Change to your Ollama model name
    QString m_historyFile;                      // Absolute path to JSON history on disk
};
