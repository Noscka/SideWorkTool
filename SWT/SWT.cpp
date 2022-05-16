#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>
#include <WinUser.h>
#include <string>

#include "./TinyExpr/tinyexpr.h"
#include <thread>

// If Program is enabled
bool Enabled = false;

// Equation Char Array
char Equation[124] = {};
int EquationArrayIndexPointer = 0; // Equation Array Index Pointer

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

bool AddToEquation(char Character)
{
	try
	{
		Equation[EquationArrayIndexPointer] = Character;
		EquationArrayIndexPointer++;
	}
	catch (...)
	{
		return false;
	}
	return true;
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
#pragma endregion

LRESULT CALLBACK HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	if(Enabled)
	{
		if(nCode >= 0)
		{
			switch(wParam)
			{
			// if keydown hook event (allows for holding and "spamming" key)
			case WM_KEYDOWN:
				// lParam is the pointer to the struct containing the data needed, so cast and assign it to kdbStruct.
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
				ToUnicodeEx((UINT)kbdStruct.vkCode, (UINT)kbdStruct.scanCode, KeyboardState, UnicodeCharacter, sizeof(UnicodeCharacter) / sizeof(*UnicodeCharacter) - 1, (UINT)kbdStruct.flags, GetKeyboardLayout(0));

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
					AddToEquation(UnicodeCharacter[0]);
					return -1;

				case 8: // {BACKSPACE}
					if(EquationArrayIndexPointer > 0)
					{
						NewCoord = {(SHORT)(GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).X - 1), GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).Y}; // create new coord with x-1 and same y
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NewCoord); // use new coord
						printf(" "); // delete character
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NewCoord); // go back 1 space
						EquationArrayIndexPointer--;
					}

					Equation[EquationArrayIndexPointer] = NULL;
					return -1;

				case 47: // /
					printf("/");
					AddToEquation(UnicodeCharacter[0]);
					return -1;

				case 43: // +
					printf("+");
					AddToEquation(UnicodeCharacter[0]);
					return -1;

				case 45: // -
					printf("-");
					AddToEquation(UnicodeCharacter[0]);
					return -1;

				case 42: // *
					printf("*");
					AddToEquation(UnicodeCharacter[0]);
					return -1;

				case 46: // .
					printf(".");
					AddToEquation(UnicodeCharacter[0]);
					return -1;

				case 13: // {ENTER}
				case 61: // =
					Enabled = false; // "disable" hook

					clear_screen();

					double EquationDoubleOutput = te_interp(Equation, 0); // intepret and solve the equation

					std::cout << Equation << " = " << EquationDoubleOutput << "\n"; // display full equation with answer

					// clear Equation array and zero Array Index Pointer
					std::fill(std::begin(Equation), std::end(Equation), 0);
					EquationArrayIndexPointer = 0;

					// convert Equation Answer to string with removing trailing 0s
					std::string EquationOutput = std::to_string(EquationDoubleOutput);
					EquationOutput.erase(EquationOutput.find_last_not_of('0') + 1, std::string::npos);
					EquationOutput.erase(EquationOutput.find_last_not_of('.') + 1, std::string::npos);

					// for loop for each character in equation answer and simulate keyboard event
					for(char ch : EquationOutput)
					{
						keybd_event(VkKeyScanExA(ch, GetKeyboardLayout(0)), (UINT)kbdStruct.scanCode, 0, 0);
						keybd_event(VkKeyScanExA(ch, GetKeyboardLayout(0)), (UINT)kbdStruct.scanCode, KEYEVENTF_KEYUP,0);
					}

					return -1;
				}
			}
		}
	}

	// call the next hook in the hook chain. This is nessecary or your hook chain will break and the hook stops
	return CallNextHookEx(_hook, nCode, wParam, lParam);
}

void AutoSelect()
{
	std::string StrInput;
	int input;

	while (true)
	{
		printf("Input amount to go right by: ");
		std::getline(std::cin, StrInput);

		if (!StrInput.empty())
		{
			if (isNumber(StrInput)) // check if input string is just numbers
			{
				input = std::stoi(StrInput);
				if (input < 0)
				{
					printf("Input has to be a positive number");
				}
				else
				{
					break;
				}
			}
			else
			{
				printf("Input has to be a interger\n");
			}
		}
		else
		{
			printf("Input cannot be empty\n");
		}
	}
	
	for (int i = 0; i <= input; i++)
	{
		keybd_event(VK_RIGHT, (UINT)kbdStruct.scanCode, 0, 0);
		keybd_event(VK_RIGHT, (UINT)kbdStruct.scanCode, KEYEVENTF_KEYUP, 0);
	}
}

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

int main()
{
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
				Enabled = !Enabled;

				if (Enabled)
				{
					printf("Enabled\n");
				}
				else
				{
					printf("Disabled\n");
				}
				break;

			case AutoSelectHK:
				AutoSelect();
				break;
			}
		}
	}

	return 0;
}
