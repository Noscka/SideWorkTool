#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <WinUser.h>
#include <string>
#include <future>
#include <thread>
#include <conio.h>

#include "./TinyExpr/tinyexpr.h"
#include "./Features/Features.h"

// Hook Variable
HHOOK _hook;

// This struct contains the data received by the hook callback. As you see in the callback function
// it contains the thing you will need: vkCode = virtual key code.
KBDLLHOOKSTRUCT kbdStruct;

#pragma region GlobalFunctions
COORD GetConsoleCursorPosition(HANDLE hConsoleOutput)
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

void clear_screen(char fill = ' ')
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

/// <summary>
/// Check if String is just numbers
/// </summary>
/// <param name="str">String to Check</param>
/// <returns>True if only numbers, False if not just numbers</returns>
bool isNumber(const std::string& str)
{
	for (char const& c : str)
	{
		if (std::isdigit(c) == 0) return false;
	}
	return true;
}

/// <summary>
/// Get data from lParam to determine which key was pressed
/// </summary>
/// <param name="lParam">lParam from hook</param>
/// <returns>wchar_t array</returns>
wchar_t* GetUnicodeCharacter(LPARAM lParam)
{
	kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);

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
				KeyboardState, UnicodeCharacter, 
				sizeof(UnicodeCharacter) / sizeof(*UnicodeCharacter) - 1, 
				(UINT)kbdStruct.flags, 
				GetKeyboardLayout(0));

	return UnicodeCharacter;
}
#pragma endregion

LRESULT CALLBACK HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
	{
		return CallNextHookEx(_hook, nCode, wParam, lParam);
	}

	if(EquationClass::Enabled)
	{
		switch(wParam)
		{
		// if keydown hook event (allows for holding and "spamming" key)
		case WM_KEYDOWN:
			//// Pointer to UnicodeCharacter Array
			wchar_t UnicodeCharacter[3] = {};
			*UnicodeCharacter = *GetUnicodeCharacter(lParam);

			// Coord for backspace cursor position editing
			COORD NewCoord;

			switch(UnicodeCharacter[0])
			{
			case 48: // 0
			case 49: // 1
			case 50: // 2
			case 51: // 3
			case 52: // 4
			case 53: // 5
			case 54: // 6
			case 55: // 7
			case 56: // 8
			case 57: // 9
				std::wcout << UnicodeCharacter;
				EquationClass::AddToDynamicCharArray(UnicodeCharacter[0]);
				return -1;

			case 8: // {BACKSPACE}
				if(EquationClass::InputStorageArrayIndexPointer > 0)
				{
					NewCoord = {(SHORT)(GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).X - 1), GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).Y}; // create new coord with x-1 and same y
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NewCoord); // use new coord
					printf(" "); // delete character
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NewCoord); // go back 1 space
					EquationClass::InputStorageArrayIndexPointer--;
				}

				EquationClass::InputStorageArray[EquationClass::InputStorageArrayIndexPointer] = NULL;
				return -1;

			case 47: // /
				printf("/");
				EquationClass::AddToDynamicCharArray(UnicodeCharacter[0]);
				return -1;

			case 43: // +
				printf("+");
				EquationClass::AddToDynamicCharArray(UnicodeCharacter[0]);
				return -1;

			case 45: // -
				printf("-");
				EquationClass::AddToDynamicCharArray(UnicodeCharacter[0]);
				return -1;

			case 42: // *
				printf("*");
				EquationClass::AddToDynamicCharArray(UnicodeCharacter[0]);
				return -1;

			case 46: // .
				printf(".");
				EquationClass::AddToDynamicCharArray(UnicodeCharacter[0]);
				return -1;

			case 13: // {ENTER}
			case 61: // =
				EquationClass::Enabled = false; // "disable" hook

				clear_screen();

				double EquationDoubleOutput = te_interp(EquationClass::InputStorageArray, 0); // intepret and solve the equation

				//std::cout << EquationClass::InputStorageArray << " = " << EquationDoubleOutput << "\n"; // display full equation with answer

				// convert InputStorageArray Answer to string with removing trailing 0s
				std::string EquationOutput = std::to_string(EquationDoubleOutput);
				EquationOutput.erase(EquationOutput.find_last_not_of('0') + 1, std::string::npos);
				EquationOutput.erase(EquationOutput.find_last_not_of('.') + 1, std::string::npos);

				std::string temp = "Calculated " + std::string(EquationClass::InputStorageArray) + " = " + EquationOutput + '\n';
				LoggingClass::LogEvent((char*)temp.c_str());

				// clear InputStorageArray array and zero Array Index Pointer
				EquationClass::InputStorageArray = new char[EquationClass::InputStorageArraySize]();
				EquationClass::InputStorageArrayIndexPointer = 0;

				// for loop for each character in equation answer and simulate keyboard event
				for(char ch : EquationOutput)
				{
					keybd_event(VkKeyScanExA(ch, GetKeyboardLayout(0)), (UINT)kbdStruct.scanCode, 0, 0);
					keybd_event(VkKeyScanExA(ch, GetKeyboardLayout(0)), (UINT)kbdStruct.scanCode, KEYEVENTF_KEYUP,0);
				}

				printf("====Logs====\n");
					   for (int i = 0; i < LoggingClass::LoggingArrayIndexPointer; i++)
					   {
						   printf(LoggingClass::LoggingArray[i]);
					   }
				return -1;
			}
		}
	}
	else if (AutoSelectClass::Enabled)
	{
		switch (wParam)
		{
		// if keydown hook event (allows for holding and "spamming" key)
		case WM_KEYDOWN:
			// Pointer to UnicodeCharacter Array
			wchar_t UnicodeCharacter[3] = {};
			*UnicodeCharacter = *GetUnicodeCharacter(lParam);

			// Coord for backspace cursor position editing
			COORD NewCoord;

			switch (UnicodeCharacter[0])
			{
			case 48: // 0
			case 49: // 1
			case 50: // 2
			case 51: // 3
			case 52: // 4
			case 53: // 5
			case 54: // 6
			case 55: // 7
			case 56: // 8
			case 57: // 9
				std::wcout << UnicodeCharacter;
				AutoSelectClass::AddToDynamicCharArray(UnicodeCharacter[0]);
				return -1;

			case 8: // {BACKSPACE}
				if (AutoSelectClass::InputStorageArrayIndexPointer > 0)
				{
					NewCoord = { (SHORT)(GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).X - 1), GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).Y }; // create new coord with x-1 and same y
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NewCoord); // use new coord
					printf(" "); // delete character
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NewCoord); // go back 1 space
					AutoSelectClass::InputStorageArrayIndexPointer--;
				}
				AutoSelectClass::InputStorageArray[AutoSelectClass::InputStorageArrayIndexPointer] = NULL;
				return -1;

			case 13: // {ENTER}
				clear_screen();

				int DirectionCount = 0;
				std::string StrInput = AutoSelectClass::InputStorageArray;

				if (!StrInput.empty())
				{
					DirectionCount = std::stoi(StrInput);
					// clear Auto Select array and zero Array Index Pointer
					AutoSelectClass::InputStorageArray = new char[AutoSelectClass::InputStorageArraySize]();
					AutoSelectClass::InputStorageArrayIndexPointer = 0;

					//keybd_event(VK_SHIFT, (UINT)kbdStruct.scanCode, 0, 0);

					for (int i = 1; i <= DirectionCount; i++)
					{
						keybd_event(VK_RIGHT, (UINT)kbdStruct.scanCode, 0, 0);
						keybd_event(VK_RIGHT, (UINT)kbdStruct.scanCode, KEYEVENTF_KEYUP, 0);
					}

					//keybd_event(VK_SHIFT, (UINT)kbdStruct.scanCode, KEYEVENTF_KEYUP, 0);

					//std::cout << "Moved " << DirectionCount << " Spaces Right" << std::endl;
				}
				else
				{
					printf("Input cannot be empty\n");
				}

				AutoSelectClass::Enabled = false;

				std::string temp = "Moved " + std::to_string(DirectionCount) + " Spaces Right" + '\n';
				LoggingClass::LogEvent((char*)temp.c_str());

				printf("====Logs====\n");
				for (int i = 0; i < LoggingClass::LoggingArrayIndexPointer; i++)
				{
					printf(LoggingClass::LoggingArray[i]);
				}
				return -1;
			}

			break;
		}
	}

	// call the next hook in the hook chain. This is nessecary or your hook chain will break and the hook stops
	return CallNextHookEx(_hook, nCode, wParam, lParam);
}

#pragma region HookRelatedFunctions
void SetHook()
{
	// Set the hook and set it to use the callback function above
	// WH_KEYBOARD_LL means it will set a low level keyboard hook. More information about it at MSDN.
	// The last 2 parameters are NULL, 0 because the callback function is in the same thread and window as the
	// function that sets and releases the hook. If you create a hack you will not need the callback function 
	// in another place then your own code file anyway. Read more about it at MSDN.
	if (!(_hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0)))
	{
		printf("Failed to install hook!");
	}
}

void ReleaseHook()
{
	UnhookWindowsHookEx(_hook);
}
#pragma endregion

int main()
{
#pragma region ProgramAlreadyrunningcheck
	CreateMutexA(0, FALSE, "Local\\$myprogram$"); // try to create a named mutex
	if (GetLastError() == ERROR_ALREADY_EXISTS) // Quit if mutex already exists (program already running)
	{
		printf("Program is already running\n");
		printf("Press any key to exit");
		_getch();
		return -1;
	}
#pragma endregion


	// Set the hook
	SetHook();

	enum
	{
		EquationEnableHK = 1, // Ctrl+Shift+alt+k - Enable Input
		AutoSelectHK = 2 // Ctrl+Shift+alt+L - Run Auto Select Function
	};
	RegisterHotKey(0, EquationEnableHK, MOD_SHIFT | MOD_CONTROL | MOD_ALT, 'K'); // register 1 key as hotkey
	RegisterHotKey(0, AutoSelectHK, MOD_SHIFT | MOD_CONTROL | MOD_ALT, 'L'); // register 2 key as hotkey
	MSG msg;
	while(GetMessage(&msg, 0, 0, 0))
	{
		PeekMessage(&msg, 0, 0, 0, 0x0001);
		switch(msg.message)
		{
		case WM_HOTKEY:
			switch (msg.wParam)
			{
			case EquationEnableHK:
				EquationClass::Enabled = !EquationClass::Enabled;

				if (EquationClass::Enabled)
				{
					printf("Enabled Equation Mode\n");
				}
				else
				{
					printf("Stopped Equation Mode\n");
				}
				break;

			case AutoSelectHK:
				printf("Input amount to go right by: ");
				AutoSelectClass::Enabled = true;
				break;
			}
		}
	}

	return 0;
}
