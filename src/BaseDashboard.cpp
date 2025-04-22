#include "BaseDashboard.h"

BaseDashboard::BaseDashboard(QWidget* parent) : QWidget(parent) {
    // Base setup if needed
}

BaseDashboard::~BaseDashboard() {
    // Cleanup if needed
}

void BaseDashboard::onActivate() {
    // Base implementation does nothing
    // Subclasses can override to perform actions when dashboard becomes active
}

void BaseDashboard::onDeactivate() {
    // Base implementation does nothing
    // Subclasses can override to perform actions when dashboard becomes inactive
}