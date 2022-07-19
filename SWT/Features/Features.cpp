#include "Features.h"

#pragma region GlobalFunctions
COORD GlobalFunctions::GetConsoleCursorPosition(HANDLE hConsoleOutput)
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

void GlobalFunctions::clear_screen(char fill)
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

bool GlobalFunctions::isNumber(const std::string& str)
{
	for (char const& c : str)
	{
		if (std::isdigit(c) == 0) return false;
	}
	return true;
}

wchar_t* GlobalFunctions::GetUnicodeCharacter(LPARAM lParam, KBDLLHOOKSTRUCT kbdStruct)
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

std::wstring GlobalFunctions::to_wstring(const std::string& str)
{
	if (str.empty()) return std::wstring();
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
	return wstrTo;
}

std::string GlobalFunctions::to_string(const std::wstring& wstr)
{
	if (wstr.empty()) return std::string();
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo(size_needed, 0);
	WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}
#pragma endregion

#pragma region Settings Region
DynamicMenu SettingsClass::SettingsMenu = DynamicMenu(L"Settings", false, false, false);

bool SettingsClass::ShowCaret = true;

void QuitAndSave()
{
	SettingsClass::SettingsMenu.ContinueMenu = false;
	Option::WriteOptions();
}

void SettingsClass::initialize()
{
	// Create Option Objects
	Option* ShowCaretOption = new Option(L"Show Caret", &ShowCaret);

	// Parse Option
	Option::ParseOptions();

	// Add to menu
	for (Option* op : Option::OptionsArray)
		SettingsMenu.AddMenuEntry(op->ReturnMenuEntry());

	SettingsMenu.AddMenuEntry(MenuEntry(L"Quit", QuitAndSave));

	Option::WriteOptions();
}
#pragma endregion

#pragma region Equation Region
bool EquationClass::Enabled = false;

DynamicArray<wchar_t> EquationClass::InputStorageArray = DynamicArray<wchar_t>(40, 40);

void EquationClass::RemovePreviousCharacter()
{
	// Coord for backspace cursor position editing
	COORD NewCoord;

	if (EquationClass::InputStorageArray.ArrayIndexPointer > 0)
	{
		NewCoord = { (SHORT)(GlobalFunctions::GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).X - 1), GlobalFunctions::GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).Y }; // create new coord with x-1 and same y
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NewCoord); // use new coord
		wprintf(L" "); // delete character
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NewCoord); // go back 1 space
		EquationClass::InputStorageArray.ArrayIndexPointer--;
	}

	EquationClass::InputStorageArray[EquationClass::InputStorageArray.ArrayIndexPointer] = NULL;
}
void EquationClass::FinishFeature(KBDLLHOOKSTRUCT kbdStruct)
{
	EquationClass::Enabled = false; // "disable" hook

	GlobalFunctions::clear_screen();

	double EquationDoubleOutput = te_interp(GlobalFunctions::to_string(EquationClass::InputStorageArray.Array).c_str(), 0); // intepret and solve the equation

	//std::cout << EquationClass::InputStorageArray << " = " << EquationDoubleOutput << "\n"; // display full equation with answer

	// convert InputStorageArray Answer to string with removing trailing 0s

	std::wstring EquationOutput = std::to_wstring(EquationDoubleOutput);
	EquationOutput.erase(EquationOutput.find_last_not_of('0') + 1, std::string::npos);
	EquationOutput.erase(EquationOutput.find_last_not_of('.') + 1, std::string::npos);

	{
		std::wstring temp = L"Calculated " + std::wstring(EquationClass::InputStorageArray.Array) + L" = " + EquationOutput + L'\n';
		LoggingClass::WriteLog((wchar_t*)temp.c_str(), temp.length());
	} // putting temp in lower scope so it gets cleared

	// clear InputStorageArray array and zero Array Index Pointer
	EquationClass::InputStorageArray.Clear();

	// for loop for each character in equation answer and simulate keyboard event
	for (char ch : EquationOutput)
	{
		keybd_event(VkKeyScanExA(ch, GetKeyboardLayout(0)), (UINT)kbdStruct.scanCode, 0, 0);
		keybd_event(VkKeyScanExA(ch, GetKeyboardLayout(0)), (UINT)kbdStruct.scanCode, KEYEVENTF_KEYUP, 0);
	}

	wprintf(L"====Logs====\n");
	for (DynamicArray<wchar_t> ChAr : LoggingClass::LoggingDynamicArray)
	{
		wprintf(ChAr.GetArray());
	}
}
#pragma endregion

#pragma region Auto Select Region
bool AutoSelectClass::Enabled = false;
DynamicArray<wchar_t> AutoSelectClass::InputStorageArray = DynamicArray<wchar_t>(20, 10);

void AutoSelectClass::RemovePreviousCharacter()
{
	// Coord for backspace cursor position editing
	COORD NewCoord;

	if (AutoSelectClass::InputStorageArray.ArrayIndexPointer > 0)
	{
		NewCoord = { (SHORT)(GlobalFunctions::GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).X - 1), GlobalFunctions::GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).Y }; // create new coord with x-1 and same y
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NewCoord); // use new coord
		wprintf(L" "); // delete character
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NewCoord); // go back 1 space
		AutoSelectClass::InputStorageArray.ArrayIndexPointer--;
	}
	AutoSelectClass::InputStorageArray[AutoSelectClass::InputStorageArray.ArrayIndexPointer] = NULL;
}

void AutoSelectClass::FinishFeature(KBDLLHOOKSTRUCT kbdStruct)
{
	GlobalFunctions::clear_screen();

	int DirectionCount = 0;
	std::wstring StrInput = AutoSelectClass::InputStorageArray.GetArray();

	if (!StrInput.empty())
	{
		DirectionCount = std::stoi(StrInput);
		// clear Auto Select array and zero Array Index Pointer
		AutoSelectClass::InputStorageArray.Clear();

		//keybd_event(VK_SHIFT, (UINT)kbdStruct.scanCode, 0, 0);

		for (int i = 1; i <= DirectionCount; i++)
		{
			keybd_event(VK_RIGHT, (UINT)kbdStruct.scanCode, 0, 0);
			keybd_event(VK_RIGHT, (UINT)kbdStruct.scanCode, KEYEVENTF_KEYUP, 0);
		}

		//keybd_event(VK_SHIFT, (UINT)kbdStruct.scanCode, KEYEVENTF_KEYUP, 0);/
	}
	else
	{
		wprintf(L"Input cannot be empty\n");
	}

	AutoSelectClass::Enabled = false;
	
	{
		std::wstring temp = L"Moved " + std::to_wstring(DirectionCount) + L" Spaces Right" + L'\n';

		LoggingClass::WriteLog((wchar_t*)temp.c_str(), temp.length());
	} // putting temp in lower scope so it gets cleared

	wprintf(L"====Logs====\n");
	for (DynamicArray<wchar_t> ChAr : LoggingClass::LoggingDynamicArray)
	{
		wprintf(ChAr.GetArray());
	}

}
#pragma endregion

#pragma region Logging Region
DynamicArray<DynamicArray<wchar_t>> LoggingClass::LoggingDynamicArray = DynamicArray<DynamicArray<wchar_t>>(2, 4);

void LoggingClass::WriteLog(wchar_t* LogTest, int LogLength)
{
	DynamicArray<wchar_t> tempArray = DynamicArray<wchar_t>();
	tempArray.ArrayAppend(LogTest, LogLength, false);
	LoggingDynamicArray.Append(tempArray);
}
#pragma endregion
