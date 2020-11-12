#include <iostream>
#include "Console.hpp"

int main()
{
	Console::Init("Example Title", false, true);
	try {
		Console::Message(LightGreen, "[GOOD] ", White, "Everything is good, if ", true, " then run you're in danger. Chance of survivability is ", 90, "%.");
		Console::MessageStatus("User defined variable is unaccessible", Warning);
		Console::MessageStatus("Read access violation", Error);
		throw "Thrown error oh no. Your program crashed";
	}
	catch (const char* e) {
		Console::MessageStatus(e, Error);
	}
	system("pause");
	Console::Detach();
}