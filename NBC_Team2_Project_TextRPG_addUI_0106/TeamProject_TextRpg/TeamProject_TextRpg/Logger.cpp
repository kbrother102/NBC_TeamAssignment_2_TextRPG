#include "Logger.h"

using std::string;
using std::vector;

// 정적 변수 초기화
vector<std::string> Logger::Logs;
std::function<void(LogType, int)> Logger::OnLogAdded = nullptr;

void Logger::Add(const std::string& msg)
{
	// 기본값은 INFO로 전달
	Add(INFO, msg);
}

void Logger::Add(LogType type, const std::string& msg)
{
	LogDefines::Config config = LogDefines::GetConfig(type);

	// 가져온 설정 사용
	std::string finalMsg = config.prefix + msg;

	if (Logs.size() >= MAX_LOG_COUNT)
	{
		Logs.erase(Logs.begin());
	}
	Logs.push_back(finalMsg);

	if (OnLogAdded)
		OnLogAdded(type, config.delay);
}

// 나머지 함수 유지
const vector<string>& Logger::GetLogs() 
{
	return Logs; 
}

void Logger::Clear() { Logs.clear(); }