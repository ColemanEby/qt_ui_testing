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
    void onSettingsChanged();

private:
    void loadHistory();
    void saveHistory();
    void updateFromSettings();

    QVector<ChatMessage> m_history;
    QNetworkAccessManager m_net;
    QString m_model;                     // Will be loaded from settings
    QString m_serverUrl;                 // Will be loaded from settings
    QString m_historyFile;               // Absolute path to JSON history on disk
};