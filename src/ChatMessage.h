#pragma once
#include <QString>

struct ChatMessage {
    QString role;     // "user" or "assistant"
    QString content;  // message text
};
