#include "ChatManager.h"
#include "SettingsManager.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject>
#include <QDir>

ChatManager::ChatManager(QObject* parent) : QObject(parent) {
    // Determine a writable path to persist chat history
    const QString dataDir = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(dataDir);
    m_historyFile = dataDir + "/ollama_chat_history.json";
    
    // Load settings
    updateFromSettings();
    
    // Connect to settings changes
    connect(&SettingsManager::instance(), &SettingsManager::settingsChanged, 
            this, &ChatManager::onSettingsChanged);
    
    // Load chat history
    loadHistory();

    // Connect network reply handler
    connect(&m_net, &QNetworkAccessManager::finished, this, &ChatManager::handleReply);
}

void ChatManager::updateFromSettings() {
    // Get settings from the SettingsManager
    m_model = SettingsManager::instance().defaultModel();
    m_serverUrl = SettingsManager::instance().serverUrl();
}

void ChatManager::onSettingsChanged() {
    // Update local settings when global settings change
    updateFromSettings();
}

void ChatManager::loadHistory() {
    QFile f(m_historyFile);
    if (!f.open(QIODevice::ReadOnly)) return;

    const QJsonDocument doc = QJsonDocument::fromJson(f.readAll());
    f.close();
    const QJsonArray arr = doc.array();
    for (const QJsonValue& v : arr) {
        const QJsonObject o = v.toObject();
        m_history.append({o["role"].toString(), o["content"].toString()});
    }
}

void ChatManager::saveHistory() {
    QJsonArray arr;
    for (const ChatMessage& m : std::as_const(m_history)) {
        QJsonObject o;
        o["role"] = m.role;
        o["content"] = m.content;
        arr.append(o);
    }
    QFile f(m_historyFile);
    if (!f.open(QIODevice::WriteOnly | QIODevice::Truncate)) return;
    f.write(QJsonDocument(arr).toJson(QJsonDocument::Compact));
    f.close();
}

void ChatManager::sendUserMessage(const QString& text) {
    // Append user message locally & persist
    ChatMessage userMsg{"user", text};
    m_history.append(userMsg);
    emit messageAppended(userMsg);
    saveHistory();

    // Construct Ollama chat body
    QJsonArray msgArr;
    for (const ChatMessage& m : std::as_const(m_history)) {
        QJsonObject o;
        o["role"] = m.role;
        o["content"] = m.content;
        msgArr.append(o);
    }
    QJsonObject body{{"model", m_model}, {"messages", msgArr}};

    // Create request using server URL from settings
    QUrl apiUrl(m_serverUrl + "/api/chat");
    QNetworkRequest req(apiUrl);
    req.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    
    // Send request
    m_net.post(req, QJsonDocument(body).toJson());
}

void ChatManager::handleReply(QNetworkReply* reply) {
    if (reply->error() != QNetworkReply::NoError) {
        emit errorOccurred(reply->errorString());
        reply->deleteLater();
        return;
    }
    const QByteArray raw = reply->readAll();
    reply->deleteLater();

    QJsonDocument doc = QJsonDocument::fromJson(raw);
    if (!doc.isObject()) {
        emit errorOccurred("Malformed JSON from Ollama");
        return;
    }
    const QJsonObject obj = doc.object();
    const QString assistantText = obj.value("message").toObject().value("content").toString();

    ChatMessage assistantMsg{"assistant", assistantText};
    m_history.append(assistantMsg);
    emit messageAppended(assistantMsg);
    saveHistory();
}

void ChatManager::newChat() {
    m_history.clear();
    saveHistory();
}