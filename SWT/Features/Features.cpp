#include "Features.h"

#pragma region Settings Region
DynamicMenu SettingsClass::SettingsMenu = DynamicMenu(L"Settings", false, false, true);

bool SettingsClass::ShowCaret = true;

void SettingsClass::initialize(LoadingScreen* Object)
{
	// Create Option Objects
	Option* ShowCaretOption = new Option(L"Show Caret", &ShowCaret);

	// Parse Option
	Option::ParseOptions(Object);

	// Add to menu
	for (Option* op : Option::OptionsArray)
		SettingsMenu.AddMenuEntry(op->ReturnMenuEntry());

	// Add custom Quit option
	SettingsMenu.AddMenuEntry(MenuEntry(L"Quit And Save", QuitAndSave));

	Option::WriteOptions();

	ApplyChanges();
}

void SettingsClass::QuitAndSave()
{
	SettingsClass::SettingsMenu.ContinueMenu = false;
	Option::WriteOptions();

	ApplyChanges();
}

void SettingsClass::ApplyChanges()
{
	GlobalFunction::ShowCaret(ShowCaret);
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
		NewCoord = { (SHORT)(GlobalFunction::GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).X - 1), GlobalFunction::GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).Y }; // create new coord with x-1 and same y
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

	GlobalFunction::clear_screen();

	double EquationDoubleOutput = te_interp(GlobalFunction::to_string(EquationClass::InputStorageArray.Array).c_str(), 0); // intepret and solve the equation

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
		NewCoord = { (SHORT)(GlobalFunction::GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).X - 1), GlobalFunction::GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).Y }; // create new coord with x-1 and same y
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NewCoord); // use new coord
		wprintf(L" "); // delete character
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NewCoord); // go back 1 space
		AutoSelectClass::InputStorageArray.ArrayIndexPointer--;
	}
	AutoSelectClass::InputStorageArray[AutoSelectClass::InputStorageArray.ArrayIndexPointer] = NULL;
}

void AutoSelectClass::FinishFeature(KBDLLHOOKSTRUCT kbdStruct)
{
	GlobalFunction::clear_screen();

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
