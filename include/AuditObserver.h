#ifndef AUDITOBSERVER_H
#define AUDITOBSERVER_H

#include "LibraryObserver.h"
#include "Logger.h"
#include <memory>

class AuditObserver : public LibraryObserver {
public:
    explicit AuditObserver(std::shared_ptr<Logger> logger);

    void onBookChanged(const std::string &message) override;

private:
    std::shared_ptr<Logger> logger;
};

#endif // AUDITOBSERVER_H