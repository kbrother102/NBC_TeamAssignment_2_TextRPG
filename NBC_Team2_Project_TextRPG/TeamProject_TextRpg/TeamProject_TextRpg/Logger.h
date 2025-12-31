/*
===========================================================================
 [ 로거(Logger) 사용 가이드 ]

 1. 목적
    - std::cout 대신 사용하여 콘솔에 색상을 입혀 출력합니다.
    - 출력된 내용은 자동으로 벡터에 저장되어 나중에 다시 볼 수 있습니다.

 2. 사용 방법 (객체 생성 불필요!)
    - 그냥 아무데서나 아래처럼 부르세요. (static 함수입니다)

    Logger::Add(LogType::INFO,   "메시지 내용"); // 일반 정보 (청록색)
    Logger::Add(LogType::COMBAT, "메시지 내용"); // 전투 로그 (빨간색)
    Logger::Add(LogType::ERROR,  "메시지 내용"); // 에러 확인 (노란색)
    Logger::Add(LogType::UI,     "메시지 내용"); // 말머리 없는 순수 텍스트

 3. 예시 코드
    Logger::Add(COMBAT, "슬라임에게 10의 데미지!");
    Logger::Add(INFO,   "포션을 획득했습니다.");
    Logger::Add(UI,     "========== [ 상태창 ] ==========");

 4. 주의사항
    - #include "Logger.h" 를 꼭 해주세요.
    - cout 대신 사용해주세요. (나중에 로그 저장 기능 추가 예정)
===========================================================================
*/

#pragma once
#include <string>
#include <vector>

enum LogType
{
    INFO,
    COMBAT,
    ERROR,
    UI
};

class Logger
{
private:
    static std::vector<std::string> Logs;
    static const int MAX_LOG_COUNT = 50; // 로그 최대 저장 갯수 

public:
    
    static void Add(LogType type, const std::string& msg);
    static const std::vector<std::string>& GetLogs();
    static void Clear();
};