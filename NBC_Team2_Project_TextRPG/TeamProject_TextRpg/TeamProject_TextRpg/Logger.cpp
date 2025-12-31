#include "Logger.h"
#include <iostream>

std::vector<std::string> Logger::logs;

// 색상 코드
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_CYAN    "\033[36m"

// ★ 여기도 반드시 'Logger::Add' 여야 합니다! ★
void Logger::Add(LogType type, const std::string& msg)
{
    std::string prefix;
    std::string colorCode;

    switch (type)
    {
    case INFO:   prefix = "[정보]"; colorCode = COLOR_CYAN;   break;
    case COMBAT: prefix = "[전투]"; colorCode = COLOR_RED;    break;
    case ERROR:  prefix = "[오류]"; colorCode = COLOR_YELLOW; break;
    }

    std::string finalLog = prefix + " " + msg;

    // 1. 콘솔 출력
    std::cout << colorCode << finalLog << COLOR_RESET << std::endl;

    // 2. 벡터 저장
    logs.push_back(finalLog);
    if (logs.size() > MAX_LOG_COUNT)
    {
        logs.erase(logs.begin());
    }
}

const std::vector<std::string>& Logger::GetLogs()
{
    return logs;
}

void Logger::Clear()
{
    logs.clear();
}