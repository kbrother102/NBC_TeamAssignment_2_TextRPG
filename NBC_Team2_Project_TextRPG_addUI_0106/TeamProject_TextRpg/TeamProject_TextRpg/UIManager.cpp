#include "UIManager.h"
#include "Logger.h"
#include "Character.h" 
#include "Monster.h"
#include "StatComponent.h"

// [LOG] 로그 출력용 색상 코드 정의
#define COLOR_RESET         "\033[0m"
#define COLOR_RED           "\033[31m"           // 적 공격 
#define COLOR_BOLD_RED      "\033[1m\033[31m"    // 플레이어 공격 
#define COLOR_BG_RED        "\033[41m\033[37m"   // 이외 전투
#define COLOR_YELLOW        "\033[33m"
#define COLOR_CYAN          "\033[36m"
#define COLOR_GREEN         "\033[1m\033[32m"    // 밝은 녹색
#define COLOR_MAGENTA       "\033[35m"           // 보라색 
#define COLOR_BOLD_YELLOW   "\033[1m\033[33m"    // 밝은 노랑

using namespace std;

UIManager::UIManager() {}
UIManager::~UIManager() {}

// 문자열이 화면에서 실제로 차지하는 칸 수(길이)를 계산
int GetVisualLength(const std::string& str)
{
    int length = 0;
    int i = 0;
    while (i < str.length())
    {
        unsigned char c = str[i];
        int charLen = 0;

        // 바이트 수 확인
        if (c < 0x80) { charLen = 1; }
        else
        {
            if ((c & 0xE0) == 0xC0) charLen = 2;
            else if ((c & 0xF0) == 0xE0) charLen = 3;
            else if ((c & 0xF8) == 0xF0) charLen = 4;
            else charLen = 1;
        }

        // [핵심 수정] 아스키 아트용이므로 특수문자도 '1칸'으로 계산합니다.
        // 그래야 중앙 정렬 계산이 정확해집니다.
        length += 1;

        i += charLen;
    }
    return length;
}

// RGB 값으로 색상 출력 / RGB 변환 / 그라데이션 계산 / 그라데이션 출력
string GetANSIColor(int r, int g, int b)
{
    return "\033[38;2;" + to_string(r) + ";" + to_string(g) + ";" + to_string(b) + "m";
}
string GetGradientColor(Color start, Color end, float ratio)
{
    int r = (int)(start.r + (end.r - start.r) * ratio);
    int g = (int)(start.g + (end.g - start.g) * ratio);
    int b = (int)(start.b + (end.b - start.b) * ratio);
    return GetANSIColor(r, g, b);
}
void UIManager::RenderGradientArt(string fileName, Color startColor, Color endColor)
{
    // 1. 파일 읽기
    ifstream file(fileName);
    if (!file.is_open()) return;

    vector<string> lines;
    string line;
    int maxLen = 0;

    // UTF-8 모드 설정 (깨짐 방지)
    UINT oldCp = GetConsoleOutputCP();
    SetConsoleOutputCP(CP_UTF8);

    while (getline(file, line))
    {
        lines.push_back(line);
        int len = GetVisualLength(line);
        if (len > maxLen) maxLen = len;
    }
    file.close();

    // 2. 출력 위치 계산 (화면 중앙)
    // (헤더에 SCREEN_WIDTH가 정의되어 있다고 가정)
    int startX = (SCREEN_WIDTH - maxLen) / 2;
    if (startX < 0) startX = 0;
    int startY = 5; // 상단 여백 (조절 가능)

    int totalLines = lines.size();

    // 3. 그라데이션 출력 루프
    for (int i = 0; i < totalLines; i++)
    {
        // 현재 줄이 전체에서 몇 퍼센트 위치인지 계산 (0.0 ~ 1.0)
        float ratio = (float)i / (float)(totalLines - 1);
        if (totalLines <= 1) ratio = 0; // 한 줄짜리 파일 예외처리

        // 그라데이션 색상 코드 가져오기
        string colorCode = GetGradientColor(startColor, endColor, ratio);

        // 좌표 이동
        GotoXY(startX, startY + i);

        // [색상 적용] -> [출력] -> [색상 리셋]
        cout << colorCode << lines[i] << "\033[0m";
    }

    // 4. 인코딩 복구
    SetConsoleOutputCP(oldCp);
}

//공백찾기 함수 [UI 덮어씌우기 연출 - 히든보스 전용]
int GetCurrentCursorX()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.X;
}

// 공통 함수 - UI 시작좌표찾기, 박스레이아웃 그리기 
void UIManager::GotoXY(int x, int y)
{
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void UIManager::DrawBox(int x, int y, int w, int h, string title)
{
    // 테두리 그리기
    GotoXY(x, y); cout << "┌";
    for (int i = 0; i < w - 2; i++) cout << "─";
    cout << "┐";

    for (int i = 1; i < h - 1; i++)
    {
        // 왼쪽 선
        GotoXY(x, y + i);
        cout << "│" << flush;

        // 오른쪽 선
        GotoXY(x + w - 1, y + i);
        cout << "│" << flush; 
    }

    GotoXY(x, y + h - 1); cout << "└";
    for (int i = 0; i < w - 2; i++) cout << "─";
    cout << "┘";

    // 제목 출력
    if (!title.empty())
    {
        GotoXY(x + 2, y); cout << " " << title << " ";
    }
}

// [1] 시스템 설정 (폰트, 창 크기 고정) / 박스 UI 그리기 / 시작 타이틀메뉴
void UIManager::InitSystem()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // 1. 폰트 설정
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(cfi);
    cfi.nFont = 0;
    cfi.dwFontSize.X = 0;
    cfi.dwFontSize.Y = 12;
    cfi.FontFamily = FF_DONTCARE;
    cfi.FontWeight = FW_NORMAL;
    wcscpy_s(cfi.FaceName, L"Consolas");
    SetCurrentConsoleFontEx(hOut, FALSE, &cfi);

    // 2. 창 크기 강제 고정 (헤더에 있는 상수 사용!)
    COORD bufferSize = { (SHORT)SCREEN_WIDTH, (SHORT)SCREEN_HEIGHT };
    SMALL_RECT windowSize = { 0, 0, (SHORT)SCREEN_WIDTH - 1, (SHORT)SCREEN_HEIGHT - 1 };

    SMALL_RECT minSize = { 0, 0, 1, 1 };
    SetConsoleWindowInfo(hOut, TRUE, &minSize);
    SetConsoleScreenBufferSize(hOut, bufferSize);
    SetConsoleWindowInfo(hOut, TRUE, &windowSize);

    // 3. 커서 숨기기 & 스타일
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1;
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hOut, &cursorInfo);

    HWND consoleWindow = GetConsoleWindow();
    long style = GetWindowLong(consoleWindow, GWL_STYLE);
    style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
    SetWindowLong(consoleWindow, GWL_STYLE, style);
}
void UIManager::RenderGameUI()
{
    system("cls");
    // 기존 박스 그리기 코드 이동
    DrawBox(MAIN_BOX_X, MAIN_BOX_Y, MAIN_BOX_W, MAIN_BOX_H, " MENU ");
    DrawBox(MONSTER_BOX_X, MONSTER_BOX_Y, MONSTER_BOX_W, MONSTER_BOX_H, " VIEW ");
    DrawBox(M_STAT_BOX_X, M_STAT_BOX_Y, M_STAT_BOX_W, M_STAT_BOX_H, " MONSTER INFO ");
    DrawBox(STAT_BOX_X, STAT_BOX_Y, STAT_BOX_W, STAT_BOX_H, " PLAYER STATUS ");
    DrawBox(LOG_BOX_X, LOG_BOX_Y, LOG_BOX_W, LOG_BOX_H, " LOG ");
}
void UIManager::RenderTitleScreen()
{
    system("cls");

    // 1. 전체 테두리 그리기
    DrawBox(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, " TEXT CONSOL RPG ");

    // 2. 타이틀 로고 출력 (그라데이션)
    Color purple = { 255, 0, 255 };
    Color cyan = { 0, 255, 255 };
    RenderGradientArt("title.txt", purple, cyan);

    // 2. 타이틀 로고 출력 (단색) / 주석처리
    /*
 
    ifstream file("title.txt");
    if (file.is_open())
    {
        string line;
        vector<string> lines;
        int maxLen = 0;

        // =========================================================
        // [핵심 수정] 출력 전에 UTF-8 모드로 변경해야 깨지지 않습니다!
        UINT oldCp = GetConsoleOutputCP();
        SetConsoleOutputCP(CP_UTF8);

        // 파일 읽기
        while (getline(file, line))
        {
            lines.push_back(line);
            int len = GetVisualLength(line);
            if (len > maxLen) maxLen = len;
        }
        file.close();

        // 중앙 정렬 좌표 계산
        int startX = (SCREEN_WIDTH - maxLen) / 2;
        if (startX < 0) startX = 0; // 안전장치

        int startY = 0;

        // 노란색으로 출력
        // cout << "\033[93m";
        for (size_t i = 0; i < lines.size(); i++)
        {
            GotoXY(startX, startY + i);
            cout << lines[i];
        }
        cout << "\033[0m"; // 색상 리셋

        // =========================================================
        // [핵심 수정] 출력이 끝나면 원래 인코딩으로 복구합니다.
        SetConsoleOutputCP(oldCp);
    }

    */

    // 3. 메뉴 출력 (여기부터는 다시 일반 영문/한글이므로 UTF-8 모드 끄고 출력)
    // (위에서 oldCp로 복구했으므로 정상 출력됩니다)

    int menuY = 45;
    string menu1 = "1. G A M E   S T A R T";
    string menu2 = "2. E X I T            ";

    GotoXY((SCREEN_WIDTH - GetVisualLength(menu1)) / 2, menuY);
    cout << menu1;
    GotoXY((SCREEN_WIDTH - GetVisualLength(menu2)) / 2, menuY + 2);
    cout << menu2;

    string guide = "SELECT OPTION >> ";
    GotoXY((SCREEN_WIDTH - guide.length()) / 2 - 2, menuY + 5);
    cout << guide;
}

// [2] 캐릭터 생성 화면 구현
// =========================================================
void UIManager::RenderCharacterCreate()
{
    // 1. 화면 깨끗하게 지우기 (전체 클리어)
    system("cls");

    // 2. 테두리만 그리기 (선택사항: 전체 테두리)
    DrawBox(0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1, "");

    // 3. 중앙 정렬 출력 람다 함수 (화면 전체 기준)
    auto PrintScreenCenter = [&](int yOffset, string text)
        {
            int textLen = GetVisualLength(text);
            // 화면 전체 너비의 절반 - 글자 길이의 절반 = 정중앙 시작점
            int x = (SCREEN_WIDTH - textLen) / 2;

            // 화면 전체 높이의 절반 + 오프셋
            int y = (SCREEN_HEIGHT / 2) + yOffset;

            GotoXY(x, y);
            cout << text;
        };

    PrintScreenCenter(-8, "=======================");
    PrintScreenCenter(-6, "    새로운 모험을    ");
    PrintScreenCenter(-4, "     시작합니다!     ");
    PrintScreenCenter(-2, "                     ");
    PrintScreenCenter(0, "    당신의 이름을    ");
    PrintScreenCenter(2, "     알려주세요.     ");
    PrintScreenCenter(4, "=======================");
}

// [3] 안전한 입력 함수 (화면 깨짐 방지)
// =========================================================
string UIManager::InputString(string prompt, int customX, int customY)
{
    int x = LOG_BOX_X + 2;          // 기본값 (로그박스 안)
    int y = LOG_BOX_Y + LOG_BOX_H - 2;

    // 1. 위치 결정 로직
    if (customY != -1)
    {
        y = customY;
        // X좌표가 들어왔으면 그걸 쓰고, 아니면 기본 들여쓰기(4칸) 사용
        if (customX != -1) x = customX;
        else x = MAIN_BOX_X + 4;
    }

    // 2. 해당 줄 청소 (잔상 제거)
    // customX가 설정된 경우(캐릭터 생성 등)에는 너무 길게 지우지 않도록 조절
    int clearLen = 0;
    if (customY == -1) clearLen = LOG_BOX_W - 6; // 로그창
    else clearLen = 50; //

    GotoXY(x, y);
    cout << string(clearLen, ' ');

    // 3. 프롬프트 출력
    GotoXY(x, y);
    cout << "\033[93m" << prompt << "\033[0m";

    // =========================================================
    // [누락된 부분 복구] 커서 제어 및 입력 받기
    // =========================================================

    // 4. 커서 잠시 보이기 (입력받을 때만 깜빡이게)
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = TRUE; // 커서 보임
    SetConsoleCursorInfo(hOut, &cursorInfo);

    // 5. 실제 입력 받기
    string input;
    getline(cin, input);

    // 6. 커서 다시 숨기기 (게임 중엔 안 보이게)
    cursorInfo.bVisible = FALSE; // 커서 숨김
    SetConsoleCursorInfo(hOut, &cursorInfo);

    // =========================================================

    // 7. 흔적 지우기 
    // (로그창일 때는 지우고, 캐릭터 생성처럼 중앙에 쓴 건 남겨두는 게 예쁨)
    if (customY == -1)
    {
        GotoXY(x, y);
        cout << string(LOG_BOX_W - 4, ' ');
    }

    return input;
}

// [4] 각 패널별 UI 생성
// =========================================================

// 좌측 메인메뉴 / 중앙 이미지로딩
void UIManager::RenderMainPanel(string title, const vector<string>& menus)
{
    int startX = MAIN_BOX_X + 2;
    int startY = MAIN_BOX_Y + 2;
    int width = MAIN_BOX_W - 4;
    int height = MAIN_BOX_H - 4;

    // 내용 지우기
    for (int i = 0; i < height; i++)
    {
        GotoXY(startX, startY + i);
        cout << string(width, ' ');
    }

    // 제목 출력
    if (!title.empty())
    {
        GotoXY(startX, startY);
        cout << "< " << title << " >";
        GotoXY(startX, startY + 1);
        cout << string(width, '-');
    }

    // 메뉴 출력
    for (size_t i = 0; i < menus.size(); i++)
    {
        if (startY + 3 + i >= startY + height) break;
        GotoXY(startX + 1, startY + 3 + i * 2);
        cout << menus[i];
    }
}
void UIManager::RenderMonsterArt(string fileName)
{
    ifstream file(fileName);
    if (!file.is_open()) return; // 파일 없으면 무시

    int startX = MONSTER_BOX_X + 2;
    int startY = MONSTER_BOX_Y + 2;
    int width = MONSTER_BOX_W - 4;
    int height = MONSTER_BOX_H - 4;

    // 1. 박스 청소
    for (int i = 0; i < height; i++)
    {
        GotoXY(startX, startY + i);
        cout << string(width, ' ');
    }

    string line;
    int lineCount = 0;

    // UTF-8 출력 설정
    UINT oldCp = GetConsoleOutputCP();
    SetConsoleOutputCP(CP_UTF8);

    while (getline(file, line) && lineCount < height)
    {
        GotoXY(startX, startY + lineCount);
        cout << line; // 자르지 않고 그대로 출력 (깨짐 방지)
        lineCount++;
    }

    SetConsoleOutputCP(oldCp);
    file.close();
}

// 캐릭터, 몬스터 스탯, 하단로그 렌더링
void UIManager::RenderStats(Character* player)
{
    if (!player) return;
    int x = STAT_BOX_X + 2;
    int y = STAT_BOX_Y + 2;

    // 잔상 제거를 위해 뒤에 공백 추가
    GotoXY(x, y++); cout << "이  름 : " << player->GetName() << "      ";
    GotoXY(x, y++); cout << "레  벨 : " << player->GetLv() << "      ";
    GotoXY(x, y++); cout << "코딩력 : " << player->GetAttack() << "      ";
    GotoXY(x, y++); cout << "포인트 : " << player->GetGold() << " Point    ";
    GotoXY(x, y++); cout << "정신력 : " << player->GetHp() << " / " << player->GetMaxHp() << "      ";
    // [HP 게이지바] ---------------------------------------------------
    // 1. 게이지 길이 계산 (최대 체력 대비 현재 체력 비율)
    int barLen = 0;
    if (player->GetMaxHp() > 0)
    {
        barLen = (player->GetHp() * 10) / player->GetMaxHp();
    }

    // 2. 게이지 그리기
    GotoXY(x, y++); // 줄 바꿈
    cout << "       [";
    for (int i = 0; i < 10; i++)
    {
        if (i < barLen) cout << "■"; // 찬 체력
        else cout << "□"; // 빈 체력
    }
    cout << "]      ";
    // -----------------------------------------------------------------

    // [EXP 게이지]-----------------------------------------------------------
    GotoXY(x, y++); // 한 줄 띄우기 (가독성)
    // 경험치 숫자 표시
    cout << "EXP  : " << player->GetExp() << " / " << player->GetMaxExp() << "      ";
    int expBarLen = 0;
    // 0으로 나누기 방지 (MaxExp가 0이면 계산 안함)
    if (player->GetMaxExp() > 0)
    {
        expBarLen = (player->GetExp() * 10) / player->GetMaxExp();
    }
    // 게이지 길이 안전장치 (0~10 사이 유지)
    if (expBarLen < 0) expBarLen = 0;
    if (expBarLen > 10) expBarLen = 10;

    GotoXY(x, y++); // 줄 바꿈
    cout << "       [";
    for (int i = 0; i < 10; i++)
    {
        if (i < expBarLen) cout << "■"; // 경험치는 채워짐
        else cout << "."; // 빈 경험치
    }
    cout << "]                ";
    // -----------------------------------------------------------

}
void UIManager::RenderMonsterStats(Monster* monster)
{
    int x = M_STAT_BOX_X + 2;
    int y = M_STAT_BOX_Y + 2;
    int width = M_STAT_BOX_W - 4;

    // 1. 몬스터가 없으면(nullptr) 내용을 지움
    if (monster == nullptr)
    {
        // 몬스터가 없으면 빈 공백으로 덮어써서 지우기
        for (int i = 0; i < 6; i++) // 6줄 정도 지움
        {
            GotoXY(x, y + i);
            cout << string(width, ' ');
        }
        return;
    }

    string mName = monster->GetName();
    string MonsterName = monster->GetName();
    int MonsterAttack = monster->GetAttack();
    int MonsterCurHp = monster->GetHealth();
    int MonsterMaxHp = monster->GetMaxHealth();

    // 2. 몬스터 정보 출력
    // (잔상 방지를 위해 뒤에 공백을 충분히 둡니다)
    GotoXY(x, y++);
    cout << "이 름 : ";

    // 최대 길이 제한 (약 30칸 제한)
    int maxAllowedWidth = 26;
    int visualLen = GetVisualLength(mName);

    if (visualLen > maxAllowedWidth)
    {
        string safeName = "";
        int currentLen = 0;
        int i = 0;

        while (i < mName.length())
        {
            unsigned char c = mName[i];
            int charByteLen = 0;
            int charVisualLen = 0;

            // 바이트 길이 계산 (UTF-8 기준)
            if (c < 0x80) { charByteLen = 1; charVisualLen = 1; }
            else if ((c & 0xE0) == 0xC0) { charByteLen = 2; charVisualLen = 2; }
            else if ((c & 0xF0) == 0xE0) { charByteLen = 3; charVisualLen = 2; }
            else if ((c & 0xF8) == 0xF0) { charByteLen = 4; charVisualLen = 2; }
            else { charByteLen = 1; charVisualLen = 1; } // 예외

            // 만약 이 글자를 더했을 때 최대 너비를 넘으면 중단
            if (currentLen + charVisualLen > maxAllowedWidth - 2) // ".." 공간 확보
                break;

            safeName += mName.substr(i, charByteLen);
            currentLen += charVisualLen;
            i += charByteLen;
        }

        cout << safeName << "..";
        // 남은 공간 공백 채우기
        cout << string(maxAllowedWidth - (currentLen + 2), ' ');
    }
    else
    {
        // 이름이 짧으면 그냥 출력하고, 남은 공간을 공백으로 싹 지움
        cout << mName;
        cout << string(maxAllowedWidth - visualLen, ' ');
    }

    GotoXY(x, y++);
    cout << "코드리뷰 시간 : " << MonsterAttack << "          "; // 뒤에 공백 추가

    GotoXY(x, y++);
    cout << "남은 과제량   : " << MonsterCurHp << " / " << MonsterMaxHp << "        "; // 뒤에 공백 추가

    // (선택사항) 체력바 그리기
    // 비율 계산: (현재체력 * 10) / 최대체력
    int barLen = 0;
    if (monster->GetMaxHealth() > 0)
    {
        barLen = (monster->GetHealth() * 10) / monster->GetMaxHealth();
    }

    GotoXY(x, y++);
    std::cout << "        [";
    for (int i = 0; i < 10; i++)
    {
        if (i < barLen) std::cout << "■"; // 찬 체력
        else std::cout << "□"; // 빈 체력
    }
    std::cout << "]    ";
}
void UIManager::RenderLogs()
{
    // 1. Logger에서 저장된 로그 목록 가져오기
    const std::vector<std::string>& logs = Logger::GetLogs();

    int startX = LOG_BOX_X + 2;
    int startY = LOG_BOX_Y + 1;
    int maxLines = LOG_BOX_H - 3;
    int maxTextLen = LOG_BOX_W - 4;

    // 2. 출력 시작 인덱스 계산
    int startIndex = 0;
    if (logs.size() > maxLines)
    {
        startIndex = logs.size() - maxLines;
    }

    int lineCount = 0;

    // 3. 로그 출력 루프
    for (size_t i = startIndex; i < logs.size(); i++)
    {
        int currentY = startY + lineCount;
        std::string msg = logs[i];

        // (1) 해당 줄 지우기 (잔상 제거)
        GotoXY(startX, currentY);
        std::cout << std::string(maxTextLen, ' ');

        // (2) 색상 결정 로직 (Logger에 있던 switch문을 여기서 if문으로 구현)
        std::string color = COLOR_RESET;

        // string::find를 사용해 말머리를 감지합니다.
        if (msg.find("[정보]") != std::string::npos)       color = COLOR_CYAN;
        else if (msg.find("[전투]") != std::string::npos)  color = COLOR_BOLD_RED;
        else if (msg.find("[타격]") != std::string::npos)  color = COLOR_BOLD_RED;
        else if (msg.find("[피격]") != std::string::npos)  color = COLOR_RED;
        else if (msg.find("[오류]") != std::string::npos)  color = COLOR_YELLOW;
        else if (msg.find("[대사]") != std::string::npos)  color = COLOR_GREEN;
        else if (msg.find("[성장]") != std::string::npos)  color = COLOR_MAGENTA;
        else if (msg.find("[보상]") != std::string::npos)  color = COLOR_BOLD_YELLOW;

        // (3) 출력 길이 제한
        if (msg.length() > maxTextLen)
        {
            msg = msg.substr(0, maxTextLen - 3) + "...";
        }

        // (4) 색상 적용해서 출력 -> 그리고 반드시 리셋!
        GotoXY(startX, currentY);
        std::cout << color << msg << COLOR_RESET;

        lineCount++;
    }
}

// @@@@@@@@@@@@ [미구현] 히든 몬스터 출현
void UIManager::RenderHiddenBossArt(string fileName)
{
    // ---------------------------------------------------------
    // 1단계: 배경 그리기 (background.txt)
    // ---------------------------------------------------------
    ifstream bgFile("background.txt");

    int startX = MAIN_BOX_X + 1;
    int startY = MAIN_BOX_Y + 1;
    int maxHeight = MAIN_BOX_H - 2;
    int maxAllowedWidth = (MAIN_BOX_W + MONSTER_BOX_W) - 2;

    UINT oldCp = GetConsoleOutputCP();
    SetConsoleOutputCP(CP_UTF8);

    if (bgFile.is_open())
    {
        string bgLine;
        int bgLineCount = 0;

        while (getline(bgFile, bgLine) && bgLineCount < maxHeight)
        {
            if (bgLine.empty()) { bgLineCount++; continue; }

            GotoXY(startX, startY + bgLineCount);

            int currentVisualWidth = 0;
            int k = 0;

            // 배경 반복 채우기
            while (currentVisualWidth < maxAllowedWidth)
            {
                if (k >= bgLine.length()) k = 0;

                unsigned char c = bgLine[k];
                int charByteLen = 0;

                // [배경] 점자/패턴은 1칸 차지
                int charVisualLen = 1;

                if (c < 0x80) { charByteLen = 1; }
                else
                {
                    if ((c & 0xE0) == 0xC0) charByteLen = 2;
                    else if ((c & 0xF0) == 0xE0) charByteLen = 3;
                    else if ((c & 0xF8) == 0xF0) charByteLen = 4;
                    else charByteLen = 1;
                }

                if (currentVisualWidth + charVisualLen > maxAllowedWidth) break;

                for (int byteIdx = 0; byteIdx < charByteLen; ++byteIdx)
                {
                    if (k + byteIdx < bgLine.length()) cout << bgLine[k + byteIdx];
                }

                k += charByteLen;
                currentVisualWidth += charVisualLen;
            }
            bgLineCount++;
        }
        bgFile.close();
    }

    // ---------------------------------------------------------
    // 2단계: 보스 몬스터 덮어쓰기 (중앙 정렬 + 투명 배경)
    // ---------------------------------------------------------
    ifstream bossFile(fileName);
    if (!bossFile.is_open())
    {
        SetConsoleOutputCP(oldCp);
        return;
    }

    vector<string> bossLines;
    string tempLine;
    int maxBossWidth = 0;

    // 파일 읽기 및 최대 너비 계산
    while (getline(bossFile, tempLine))
    {
        // [추가] 오른쪽 공백 제거 (우측에 불필요한 공백이 있으면 중앙 정렬이 틀어짐)
        while (!tempLine.empty() && tempLine.back() == ' ')
        {
            tempLine.pop_back();
        }

        bossLines.push_back(tempLine);
        int len = GetVisualLength(tempLine); // 이제 여기서 1칸 기준으로 정확히 계산됨
        if (len > maxBossWidth) maxBossWidth = len;
    }
    bossFile.close();

    // 중앙 정렬 계산
    int totalAreaWidth = (MAIN_BOX_W + MONSTER_BOX_W) - 2;
    int paddingLeft = (totalAreaWidth - maxBossWidth) / 2;
    if (paddingLeft < 0) paddingLeft = 0;

    // 보스 출력
    for (int i = 0; i < bossLines.size(); i++)
    {
        if (i >= maxHeight) break;

        string& line = bossLines[i];
        int currentY = startY + i;

        // 시작 위치로 이동
        GotoXY(startX + paddingLeft, currentY);

        int k = 0;
        while (k < line.length())
        {
            unsigned char c = line[k];
            int charLen = 0;

            if (c < 0x80) charLen = 1;
            else
            {
                if ((c & 0xE0) == 0xC0) charLen = 2;
                else if ((c & 0xF0) == 0xE0) charLen = 3;
                else if ((c & 0xF8) == 0xF0) charLen = 4;
                else charLen = 1;
            }

            // 투명 처리 (공백이면 건너뜀)
            bool isSpace = (charLen == 1 && c == ' ');

            if (isSpace)
            {
                int currentX = GetCurrentCursorX();
                // [수정] 여기서도 1칸만 이동해야 함
                GotoXY(currentX + 1, currentY);
            }
            else
            {
                for (int byteIdx = 0; byteIdx < charLen; ++byteIdx)
                {
                    if (k + byteIdx < line.length()) cout << line[k + byteIdx];
                }
            }
            k += charLen;
        }
        Sleep(20);
    }

    SetConsoleOutputCP(oldCp);
}

// [5] 메뉴 그리기 - 기본 / 전투 / 상점
void UIManager::RenderVillageMenu()
{
    std::vector<std::string> menus = {
        "1. 상 태 확 인",
        "2. 인 벤 토 리",
        "3. 상 점 이 용",
        "4. 던 전 입 장"
    };

    RenderMainPanel(" VILLAGE ", menus);
}
void UIManager::RenderBattleMode()
{
    std::vector<std::string> battleMsg = {
        " ",
        "      [ ! ]      ",
        " ",
        "    전투중에는   ",
        "    메뉴 기능을  ",
        "   사용 불가합니다 ",
        " ",
        "   승리하여 강의실로 ",
        "    돌아가세요!    "
    };

    RenderMainPanel(" BATTLE!! ", battleMsg);
}
void UIManager::RenderShopMenu()
{
    std::vector<std::string> shopMenu = {
        "1. 물품 목록 (구매)",
        "2. 아이템 판매",
        "3. 나가기"
    };

    RenderMainPanel(" GENERAL STORE ", shopMenu);
}
