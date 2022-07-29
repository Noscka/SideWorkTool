#include "GlobalFunction.h"

COORD GlobalFunction::GetConsoleCursorPosition(HANDLE hConsoleOutput)
{
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsoleOutput, &cbsi))
	{
		return cbsi.dwCursorPosition;
	}
	else
	{
		// The function failed. Call GetLastError() for details.
		return { 0, 0 };
	}
}

void GlobalFunction::clear_screen(char fill)
{
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}

void GlobalFunction::clearRanged(int from, int to)
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD tl = { 0, (SHORT)(from) };
	GetConsoleScreenBufferInfo(ConsoleHandle, &csbi);
	DWORD written, cells = csbi.dwSize.X * ((to-from)+1);
	FillConsoleOutputCharacter(ConsoleHandle, ' ', cells, tl, &written);
	FillConsoleOutputAttribute(ConsoleHandle, csbi.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(ConsoleHandle, tl);
}

bool GlobalFunction::isNumber(const std::string& str)
{
	for (char const& c : str)
	{
		if (std::isdigit(c) == 0) return false;
	}
	return true;
}

wchar_t* GlobalFunction::GetUnicodeCharacter(LPARAM lParam, KBDLLHOOKSTRUCT kbdStruct)
{
	// KeyBoardState BYTE array
	BYTE KeyboardState[256] = {};

	// UnicodeCharacter output from ToUnicodeEx
	wchar_t UnicodeCharacter[3] = {};

	// Get keystate from Shift and alt when getting keyboardstate
	GetKeyState(VK_SHIFT);
	GetKeyState(VK_MENU);
	GetKeyboardState(KeyboardState);

	// Get the key hit while taking into account the modifiers (shift+5 -> %)
	ToUnicodeEx((UINT)kbdStruct.vkCode,
				(UINT)kbdStruct.scanCode,
				KeyboardState,
				UnicodeCharacter,
				sizeof(UnicodeCharacter) / sizeof(*UnicodeCharacter) - 1,
				(UINT)kbdStruct.flags,
				GetKeyboardLayout(0));

	return UnicodeCharacter;
}

std::wstring GlobalFunction::to_wstring(const std::string& str)
{
	if (str.empty()) return std::wstring();
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

std::string GlobalFunction::to_string(const std::wstring& wstr)
{
	if (wstr.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}

void GlobalFunction::ShowCaret(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}