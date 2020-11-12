# Console
A simple c++ console helper library for Windows.

## Example

```cpp
	Console::Init("Aham's Console Library", false, true);
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
```
## Example Output


[GOOD] Everything is good, if true then run you're in danger. Chance of survivability is 90%.

2020-11-12 16:58:27 [WARNING] User defined variable is unaccessible

2020-11-12 16:58:27 [ERROR] Read access violation

2020-11-12 16:58:27 [ERROR] Thrown error oh no. Your program crashed

Press any key to continue . . .
