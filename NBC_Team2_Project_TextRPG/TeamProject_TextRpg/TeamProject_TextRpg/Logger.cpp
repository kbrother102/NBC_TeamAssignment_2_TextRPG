#include "Logger.h"
#include <iostream>
#include <thread> // sleep_for 사용을 위해 추가
#include <chrono> // 시간 단위(ms) 사용을 위해 추가

// 색상 코드
#define COLOR_RESET         "\033[0m"
#define COLOR_RED           "\033[31m"           // 적 공격 
#define COLOR_BOLD_RED      "\033[1m\033[31m"    // 플레이어 공격 
#define COLOR_BG_RED        "\033[41m\033[37m"   // 이외 전투
#define COLOR_YELLOW        "\033[33m"
#define COLOR_CYAN          "\033[36m"
#define COLOR_GREEN         "\033[1m\033[32m"   // 밝은 녹색
#define COLOR_MAGENTA       "\033[35m"          // 보라색 
#define COLOR_BOLD_YELLOW   "\033[1m\033[33m"   // 밝은 노랑 

// 자주 쓰는 것들 선언 (여기서 선언했으니, 아래에서는 std:: 빼고 씁니다)
using std::cout;
using std::endl;
using std::string;
using std::to_string;
using std::vector; // 로그 모아서 출력하기 위해 vector도 추가
using std::flush; // flush 사용 추가

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

    // [1] 타입별 딜레이 설정 (밀리초 단위)
    // 속도 조절 변수 설정. (1000ms = 1초)
    int DelayMs = 0;

    switch (type) // 태그에 따른 로그 말머리 및 컬러지정
    {
    case INFO:
        Prefix = "[정보] ";
        ColorCode = COLOR_CYAN;
        DelayMs = 100;
        break;

    case COMBAT:
        Prefix = "[전투] ";
        ColorCode = COLOR_BOLD_RED;
        DelayMs = 200; // 전투 로그 딜레이 0.5초
        break;

    case COMBAT_PLAYER: // [플레이어가 공격]
        Prefix = "[타격] ";
        ColorCode = COLOR_BOLD_RED; 
        DelayMs = 200;
        break;

    case COMBAT_ENEMY:  // [몬스터가 공격]
        Prefix = "[피격] ";
        ColorCode = COLOR_RED;
        DelayMs = 200;
        break;

    case WARNING:
        Prefix = "[오류] ";
        ColorCode = COLOR_YELLOW;
        DelayMs = 0;
        break;

    case TALK:
        Prefix = "[대사] ";
        ColorCode = COLOR_GREEN; 
        DelayMs = 1000; // 전투 로그 딜레이 1초
        break;

    case EVENT: 
        Prefix = "[성장] "; 
        ColorCode = COLOR_MAGENTA; // 보라색 적용
        DelayMs = 500; // 성장 딜레이 0.5초
        break;

    case REWARD:
        Prefix = "[보상] ";
        ColorCode = COLOR_BOLD_YELLOW; // 보라색 적용
        DelayMs = 500; // 보상 딜레이 0.5초
        break;

    case UI:
        Prefix = ""; // UI 말머리 없음
        ColorCode = COLOR_RESET;
        DelayMs = 0;
        break;
    }

    // prefix가 비어있으면 그냥 msg만 나감
    string FinalLog = Prefix + msg;

    // [2] 콘솔 출력 및 딜레이 적용
    cout << ColorCode << FinalLog << COLOR_RESET << flush;

    // 설정된 딜레이가 있을 때만 멈춤
    if (DelayMs > 0)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(DelayMs));
    }

    cout << endl;

    // [3] 벡터 저장 (기존 동일)
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