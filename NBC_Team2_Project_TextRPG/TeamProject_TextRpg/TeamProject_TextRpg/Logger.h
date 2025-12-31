#pragma once
#include <string>
#include <vector>

enum LogType
{
    INFO,
    COMBAT,
    ERROR
};

class Logger
{
private:
    static std::vector<std::string> logs;
    static const int MAX_LOG_COUNT = 50;

public:
    // ★ 여기가 반드시 'Add' 라고 되어 있어야 합니다! ★
    static void Add(LogType type, const std::string& msg);

    static const std::vector<std::string>& GetLogs();
    static void Clear();
};