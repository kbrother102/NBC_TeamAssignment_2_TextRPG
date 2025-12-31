#pragma once
#include <string>
#include <iostream>

// 복잡한 enum class 대신, 초보자에게 직관적인 문자열이나 단순 정수를 사용해도 됩니다.
// 하지만 가독성을 위해 간단한 열거형을 추천합니다.
enum LogType
{
    INFO,   // 일반 정보
    COMBAT, // 전투 (빨간색)
    ERROR   // 오류 (노란색)
};

class Logger
{
public:
    // 'static'은 "이 함수는 객체를 만들지 않고도 쓸 수 있다"는 뜻입니다.
    // 팀원들은 Logger::Print(...) 형태만 기억하면 됩니다.
    static void Print(LogType type, std::string message);
};