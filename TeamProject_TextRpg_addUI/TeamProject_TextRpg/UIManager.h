#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <windows.h>
#include <fstream>
#include <conio.h> // _getch()
class Character;
class Monster;

struct Color
{
    int r, g, b;
};

class UIManager
{
public:
    UIManager();
    ~UIManager();

    // UI초기화
    void Init();

    // 1. 시작 메뉴 (타이틀 화면)
    void InitSystem();      // [1] 창 크기, 폰트 설정 (프로그램 켜자마자 1번만 실행)
    void RenderGameUI();    // [2] 게임용 박스들 그리기 (게임 시작하면 실행)
    void RenderTitleScreen(); // [3] 타이틀 화면
    void RenderGradientArt(std::string fileName, Color startColor, Color endColor); // [4] 그래디언트 컬러 타이틀

    // [유틸] UI 안 망가지게 문자열 입력받는 함수
    std::string InputString(std::string prompt, int customY = -1, int customX = -1);

    // 2. 캐릭터 생성 화면 (이름 입력 안내)
    void RenderCharacterCreate();

    // 3. 메인 화면 (마을/전투 공용)
    void RenderMainPanel(std::string title, const std::vector<std::string>& menus);

    // 4. 메뉴 화면
    void RenderVillageMenu();    // 마을 메뉴
    void RenderBattleMode();     // 전투 중 잠금 화면
    void RenderShopMenu();       // 상점 메인 메뉴

    // =============================================================

    // 스텟 & 로그 렌더링
    void RenderStats(Character* player);
    void RenderMonsterStats(Monster* monster);
    void RenderLogs();

    // [핵심] 텍스트 파일 아스키 아트 로더 (중앙 박스용)
    void RenderMonsterArt(std::string fileName);
    void RenderHiddenBossArt(std::string fileName);

private:
    void GotoXY(int x, int y);
    void DrawBox(int x, int y, int h, int w, std::string title);

    // 레이아웃 상수 (16:9 와이드 비율 / 가로 2배 법칙 적용)
    // ---------------------------------------------------------
    const int SCREEN_WIDTH = 172;
    const int SCREEN_HEIGHT = 62;

    // 1. 메인 박스 (좌측)
    const int MAIN_BOX_X = 0;
    const int MAIN_BOX_Y = 1;
    const int MAIN_BOX_W = 60;
    const int MAIN_BOX_H = 30;

    // 2-1. 몬스터/그림 박스 (중앙)
    const int MONSTER_BOX_X = 60;
    const int MONSTER_BOX_Y = 1;
    const int MONSTER_BOX_W = 60; // 가로를 넓게 잡음 
    const int MONSTER_BOX_H = 30;

    // 2-2. 몬스터 스탯 박스 (좌상단)
    const int M_STAT_BOX_X = 120;
    const int M_STAT_BOX_Y = 1; // 플레이어 박스 위 시작
    const int M_STAT_BOX_W = 50;
    const int M_STAT_BOX_H = 9; // 나머지 높이 채움

    // 3. 스텟 박스 (우측)
    const int STAT_BOX_X = 120;
    const int STAT_BOX_Y = 11;
    const int STAT_BOX_W = 50;
    const int STAT_BOX_H = 20;

    // 4. 로그 박스 (하단)
    const int LOG_BOX_X = 0;
    const int LOG_BOX_Y = 31;
    const int LOG_BOX_W = 170;
    const int LOG_BOX_H = 30;
};