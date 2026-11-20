#include "../include/Logger.h"
#include <fstream>
#include <ctime>
#include <iostream>

void Logger::Log(const std::string& level, const std::string& message) {
    std::ofstream logFile("app.log", std::ios::app);
    if (logFile.is_open()) {
        std::time_t now = std::time(nullptr);
        char timeBuf[26];
        ctime_s(timeBuf, sizeof(timeBuf), &now);
        std::string timeStr(timeBuf);
        if (!timeStr.empty() && timeStr.back() == '\n') {
            timeStr.pop_back(); // Удаляем символ переноса строки
        }

        logFile << "[" << timeStr << "] [" << level << "] " << message << std::endl;
        logFile.close();
    }
}

void Logger::Info(const std::string& message) {
    Log("INFO", message);
}

void Logger::Error(const std::string& message) {
    Log("ERROR", message);
    std::cerr << "[ERROR] " << message << std::endl;
}
