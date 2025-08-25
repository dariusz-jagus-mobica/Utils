#include "logger.h"

Logger::Logger(const std::string& filename, bool logToConsole)
    : logToConsole(logToConsole), currentLevel(LogLevel::INFO) {
    if (!filename.empty()) {
        fileStream.open(filename, std::ios::app);
    }
}

Logger::~Logger() {
    if (fileStream.is_open()) {
        fileStream.close();
    }
}

void Logger::log(const std::string& message, LogLevel level) {
    std::lock_guard<std::mutex> lock(logMutex);
    if (level < currentLevel) return;

    std::string output = "[" + getTimestamp() + "] [" + levelToString(level) + "] " + message;

    if (logToConsole) {
        std::cout << output << std::endl;
    }

    if (fileStream.is_open()) {
        fileStream << output << std::endl;
    }
}

void Logger::setLogToConsole(bool enable) {
    logToConsole = enable;
}

void Logger::setLogLevel(LogLevel level) {
    currentLevel = level;
}

std::string Logger::getTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm buf;
#ifdef _WIN32
    localtime_s(&buf, &in_time_t);
#else
    localtime_r(&in_time_t, &buf);
#endif
    std::ostringstream ss;
    ss << std::put_time(&buf, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string Logger::levelToString(LogLevel level) {
    switch (level) {
        case LogLevel::INFO: return "INFO";
        case LogLevel::WARNING: return "WARNING";
        case LogLevel::ERROR: return "ERROR";
        case LogLevel::DEBUG: return "DEBUG";
        default: return "UNKNOWN";
    }
}

