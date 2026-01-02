#include "Logger.h"
#include <iostream>

// 색상 코드
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_CYAN    "\033[36m"

// 자주 쓰는 것들 선언 (여기서 선언했으니, 아래에서는 std:: 빼고 씁니다)
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::vector; // vector도 추가했습니다.

// static 변수 메모리 할당
vector<string> Logger::Logs;

void Logger::Add(const string& msg)
{
    // 타입을 입력 안 하면 자동으로 UI 타입으로 처리해서 넘김
    Add(UI, msg);
}

void Logger::Add(LogType type, const string& msg)
{
    string Prefix = ""; // 기본값 빈 문자열
    string ColorCode = COLOR_RESET;

    switch (type) // 태그에 따른 로그 말머리 및 컬러지정
    {
    case INFO:
        Prefix = "[정보] ";
        ColorCode = COLOR_CYAN;
        break;

    case COMBAT:
        Prefix = "[전투] ";
        ColorCode = COLOR_RED;
        break;

    case WARNING:
        Prefix = "[오류] ";
        ColorCode = COLOR_YELLOW;
        break;

    case UI:
        Prefix = ""; // UI 말머리 없음
        ColorCode = COLOR_RESET; // 혹은 원하는 색 (예: 흰색)
        break;
    }

    // prefix가 비어있으면 그냥 msg만 나감
    string FinalLog = Prefix + msg;

    // 1. 콘솔 출력 
    cout << ColorCode << FinalLog << COLOR_RESET << endl;

    // 2. 벡터 저장
    Logs.push_back(FinalLog);
    if (Logs.size() > MAX_LOG_COUNT)
    {
        Logs.erase(Logs.begin());
    }
}


// 추후 UI 변경시를 위한 벡터 문자열 저장
const vector<string>& Logger::GetLogs()
{
    return Logs;
}

void Logger::Clear()
{
    Logs.clear();
}