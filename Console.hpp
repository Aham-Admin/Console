#pragma once

#if _WIN32_WINNT < 0x0500
#undef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <wtypes.h>
#include <time.h>
#include <ctime>

enum ConColor
{
	Black = 0,
	DarkBlue,
	Green,
	Turqoise,
	DarkRed,
	DarkPurple,
	DarkYellow,
	Gray,
	DarkGray,
	Blue,
	LightGreen,
	LightBlue,
	Red,
	Purple,
	Yellow,
	White
};
enum ConStatus
{
	Ok,
	Good,
	Warning,
	Error
};

namespace Console {
	static bool enabled = true;
	namespace internal {
		static bool shouldLog = false;
		static bool detailedLog = false;
		static const char* ConStatusArray[] = { "OK", "GOOD", "WARNING", "ERROR" };
		extern std::ofstream logger;
	}
	void Init(const char* ConTitle, bool logToFile = false, bool detailed = false);
	void Detach();

	inline bool Message()
	{
		std::cout << std::endl;
		if (internal::logger.is_open())
		{
			internal::logger << std::endl;
		}
		return true;
	}
	template<typename T, typename ...Types>
	bool Message(T msg, Types ...var)
	{
		if (enabled) {

			if (std::is_same<T, ConColor>::value) {
				HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hCon, static_cast<ConColor>((int)msg));
			}
			else {
				if (std::is_same<T, bool>::value) {
					if ((bool)msg == true)
						std::cout << "true";
					else
						std::cout << "false";
				}
				else
					std::cout << msg;
				if (internal::logger.is_open())
				{
					internal::logger << msg;
				}
			}
			Message(var...);
			return true;
		}
		return false;
	}

	bool MessageStatus(const char* msg, ConStatus state = Ok);
}