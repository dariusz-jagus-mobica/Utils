#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <fstream>
#include <iostream>
#include <mutex>
#include <chrono>
#include <iomanip>

enum class LogLevel {
    INFO,
    WARNING,
    ERROR,
    DEBUG
};

class Logger {
public:
    Logger(const std::string& filename = "", bool logToConsole = true);
    ~Logger();

    void log(const std::string& message, LogLevel level = LogLevel::INFO);

    void setLogToConsole(bool enable);
    void setLogLevel(LogLevel level);

private:
    std::ofstream fileStream;
    bool logToConsole;
    LogLevel currentLevel;
    std::mutex logMutex;

    std::string getTimestamp();
    std::string levelToString(LogLevel level);
};

#endif // LOGGER_H

