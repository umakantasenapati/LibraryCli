// Logger.cpp

#include "Logger.h"
#include <iostream>
#include <ctime>

Logger::Logger(const std::string &logFilePath) {
    logFile.open(logFilePath, std::ios::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Unable to open log file: " + logFilePath);
    }
}

Logger::~Logger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void Logger::log(const std::string &message) {
    std::lock_guard<std::mutex> lock(logMutex);
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    char timeBuffer[30];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d %H:%M:%S", &tm);

    logFile << "[" << timeBuffer << "] " << message << std::endl;
    logFile.flush();
}