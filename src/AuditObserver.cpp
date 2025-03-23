#include "AuditObserver.h"

AuditObserver::AuditObserver(std::shared_ptr<Logger> logger)
    : logger(logger) {}

void AuditObserver::onBookChanged(const std::string &message) {
    logger->log("[Audit] " + message);
}