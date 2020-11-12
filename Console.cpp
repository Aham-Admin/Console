#include "Console.hpp"
#pragma warning( disable : 4996 ) // freopen is depricated in c++ 20.

std::ofstream Console::internal::logger;

void Console::Init(const char* ConTitle, bool logToFile, bool detailed)
{
	internal::shouldLog = logToFile;
	internal::detailedLog = detailed;

	if (GetConsoleWindow() == NULL)
	{
		if (!AllocConsole())
		{
			MessageBox(NULL, ((std::string)ConTitle + " failed to Allocate Console").c_str(), NULL, MB_ICONEXCLAMATION);
			return;
		}
		if (freopen("CONOUT$", "w", stdout) == NULL) {
			MessageBox(NULL, ((std::string)ConTitle + " failed to load: stdout").c_str(), NULL, MB_ICONEXCLAMATION);
			return;
		}
		if (freopen("CONOUT$", "w", stderr)) {
			MessageBox(NULL, ((std::string)ConTitle + " failed to load: stderr").c_str(), NULL, MB_ICONEXCLAMATION);
			return;
		}
		if (freopen("CONIN$", "r", stdin)) {
			MessageBox(NULL, ((std::string)ConTitle + " failed to load: stdin").c_str(), NULL, MB_ICONEXCLAMATION);
			return;
		}
	}
	SetConsoleTitle(ConTitle);
	if (internal::shouldLog) {
		bool exists = true;
		std::ifstream file(__DATE__);
		int idx = 1;
		do
		{
			std::ifstream file((std::string)__DATE__ + " " + std::to_string(idx) + ".txt");
			if (!file.good())
				exists = false;
			else
				idx++;
		} while (exists);

		internal::logger.open(((std::string)__DATE__ + " " + std::to_string(idx) + ".txt").c_str());
		internal::logger << __TIMESTAMP__ << std::endl;
	}
}

void Console::Detach()
{
	if (internal::logger.is_open())
	{
		internal::logger.close();
	}
	FreeConsole();
}

bool Console::MessageStatus(const char* msg, ConStatus state)
{
	ConColor clr = White;
	switch (state) {
	case Ok:
		clr = White;
		break;
	case Good:
		clr = LightGreen;
		break;
	case Warning:
		clr = Yellow;
		break;
	case Error:
		clr = Red;
		break;
	default:
		clr = White;
		break;
	}
	if (internal::detailedLog) {
		std::time_t now = std::time(0);
		std::tm* now_tm = std::gmtime(&now);
		char buf[42];
		std::strftime(buf, 42, "%Y-%m-%d %H:%M:%S ", now_tm);
		return Message(buf, "[", clr, internal::ConStatusArray[state], White, "] ", msg);
	}
	return Message("[", clr, internal::ConStatusArray[state], White, "] ", msg);
}
