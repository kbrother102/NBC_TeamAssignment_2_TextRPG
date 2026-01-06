#pragma once
#include <string>

// 1. 로그 타입 정의 (내부 Enum)
enum LogType
{
	INFO,
	COMBAT,
	COMBAT_PLAYER,
	COMBAT_ENEMY,
	WARNING,
	TALK,
	EVENT,
	REWARD,
	UI
};

class LogDefines
{
public:
	// 2. 설정값 구조체 (내부 Struct)
	struct Config
	{
		std::string prefix; // 말머리
		int delay;          // 대기 시간(ms)
	};

	// 3. 설정 반환 함수 (정적 함수)
	// 타입을 넣으면 {말머리, 시간}을 뱉어냅니다.
	static Config GetConfig(LogType type)
	{
		switch (type)
		{
		case INFO:
			return
			{
				"[정보] ", 100
			};

		case COMBAT:
			return
			{
				"[전투] ", 200 
			};

		case COMBAT_PLAYER:
			return 
			{
				"[타격] ", 200 
			};

		case COMBAT_ENEMY:
			return 
			{
				"[피격] ", 200 
			};

		case WARNING:
			return
			{
				"[오류] ", 500 
			};

		case TALK:
			return 
			{
				"[대사] ", 1500 
			};

		case EVENT:
			return
			{
				"[성장] ", 1000 
			};

		case REWARD:
			return 
			{
				"[보상] ", 1000 
			};

		case UI:
			return
			{
				""		, 0 
			};

		default:
			return
			{
				""		, 100
			};
		}
	}
};