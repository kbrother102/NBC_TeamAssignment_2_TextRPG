#include "Logger.h"

// Windows 콘솔 색상 코드 (외울 필요 없이 복사해서 쓰면 됩니다)
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[31m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_CYAN    "\033[36m"

void Logger::Print(LogType type, std::string message)
{
    std::string colorCode;
    std::string prefix;

    // switch문: type에 따라 색상과 말머리를 결정
    switch (type)
    {
    case INFO:
        colorCode = COLOR_CYAN;
        prefix = "[정보]";
        break;
    case COMBAT:
        colorCode = COLOR_RED;
        prefix = "[전투]";
        break;
    case ERROR:
        colorCode = COLOR_YELLOW;
        prefix = "[오류]";
        break;
    }

    // 실제 출력: 색상코드 + 말머리 + 메시지 + 리셋코드
    std::cout << colorCode << prefix << " " << message << COLOR_RESET << std::endl;
}