// Logger.h

#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <mutex>

class Logger {
public:
    explicit Logger(const std::string &logFilePath);
    ~Logger();

    void log(const std::string &message);

private:
    std::ofstream logFile;
    std::mutex logMutex;
};

#endif // LOGGER_H