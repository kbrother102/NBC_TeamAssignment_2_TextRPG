#pragma once
#include <vector>
#include <string>

class Logger
{
private:
    static std::vector<std::string> _logs;

public:
    // 로그 추가 
    static void Add(const std::string& msg);

    // 저장된 로그 전체 가져오기
    static const std::vector<std::string>& GetLogs();
};