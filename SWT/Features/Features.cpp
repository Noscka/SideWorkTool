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

/// <summary>
/// Check if String is just numbers
/// </summary>
/// <param name="str">String to Check</param>
/// <returns>True if only numbers, False if not just numbers</returns>
bool GlobalFunctions::isNumber(const std::string& str)
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
#pragma endregion

#pragma region Equation Region
bool EquationClass::Enabled = false;
char* EquationClass::InputStorageArray = new char[InputStorageArraySize]();
int EquationClass::InputStorageArrayIndexPointer = 0;
int EquationClass::InputStorageArraySize = 128;
int EquationClass::ArrayStep = 20;
bool EquationClass::AddToDynamicCharArray(char CharaterToAdd)
{
	try
	{
		if (InputStorageArrayIndexPointer >= InputStorageArraySize) // if Current Index pointer is more then the array size (trying to add to OutOfRange space)
		{
			char* TempArray = new char[InputStorageArraySize](); // Create new array which will store the original values

			for (int i = 0; i < InputStorageArraySize; i++) // assign/copy all values from CharArray to Temp
			{
				TempArray[i] = InputStorageArray[i];
			}

			InputStorageArraySize += ArrayStep; // expand the Array size
			InputStorageArray = new char[InputStorageArraySize](); // over ride CharArray with new, bigger, array

			/*
			ArraySize-2 calculates TempArray size
			Copy all values from Temp array to "old" expanded array
			*/
			for (int i = 0; i < InputStorageArraySize - ArrayStep; i++)
			{
				InputStorageArray[i] = TempArray[i];
			}

			delete[] TempArray;
		}

		InputStorageArray[InputStorageArrayIndexPointer] = CharaterToAdd;
		InputStorageArrayIndexPointer++;
	}
	catch (...)
	{
		return false;
	}
	return true;
}
void EquationClass::RemovePreviousCharacter()
{
	// Coord for backspace cursor position editing
	COORD NewCoord;

	if (EquationClass::InputStorageArrayIndexPointer > 0)
	{
		NewCoord = { (SHORT)(GlobalFunctions::GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).X - 1), GlobalFunctions::GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).Y }; // create new coord with x-1 and same y
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NewCoord); // use new coord
		printf(" "); // delete character
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NewCoord); // go back 1 space
		EquationClass::InputStorageArrayIndexPointer--;
	}

	EquationClass::InputStorageArray[EquationClass::InputStorageArrayIndexPointer] = NULL;
}
void EquationClass::FinishFeature(KBDLLHOOKSTRUCT kbdStruct)
{
	EquationClass::Enabled = false; // "disable" hook

	GlobalFunctions::clear_screen();

	double EquationDoubleOutput = te_interp(EquationClass::InputStorageArray, 0); // intepret and solve the equation

	//std::cout << EquationClass::InputStorageArray << " = " << EquationDoubleOutput << "\n"; // display full equation with answer

	// convert InputStorageArray Answer to string with removing trailing 0s
	std::string EquationOutput = std::to_string(EquationDoubleOutput);
	EquationOutput.erase(EquationOutput.find_last_not_of('0') + 1, std::string::npos);
	EquationOutput.erase(EquationOutput.find_last_not_of('.') + 1, std::string::npos);

	{
		std::string temp = "Calculated " + std::string(EquationClass::InputStorageArray) + " = " + EquationOutput + '\n';

		DynamicArray<char> tempArray = DynamicArray<char>();
		tempArray.ArrayAppend((char*)temp.c_str(), temp.length(), false);

		LoggingClass::LoggingDynamicArray.Append(tempArray);
	} // putting temp in lower scope so it gets cleared

	// clear InputStorageArray array and zero Array Index Pointer
	EquationClass::InputStorageArray = new char[EquationClass::InputStorageArraySize]();
	EquationClass::InputStorageArrayIndexPointer = 0;

	// for loop for each character in equation answer and simulate keyboard event
	for (char ch : EquationOutput)
	{
		keybd_event(VkKeyScanExA(ch, GetKeyboardLayout(0)), (UINT)kbdStruct.scanCode, 0, 0);
		keybd_event(VkKeyScanExA(ch, GetKeyboardLayout(0)), (UINT)kbdStruct.scanCode, KEYEVENTF_KEYUP, 0);
	}

	printf("====Logs====\n");
	for (DynamicArray<char> ChAr : LoggingClass::LoggingDynamicArray)
	{
		printf(ChAr.GetArray());
	}
}
#pragma endregion

#pragma region Auto Select Region
bool AutoSelectClass::Enabled = false;
char *AutoSelectClass::InputStorageArray = new char[InputStorageArraySize]();
int AutoSelectClass::InputStorageArrayIndexPointer = 0;
int AutoSelectClass::InputStorageArraySize = 128;
int AutoSelectClass::ArrayStep = 20;
bool AutoSelectClass::AddToDynamicCharArray(char CharaterToAdd)
{
	try
	{
		if (InputStorageArrayIndexPointer >= InputStorageArraySize) // if Current Index pointer is more then the array size (trying to add to OutOfRange space)
		{
			char* TempArray = new char[InputStorageArraySize](); // Create new array which will store the original values

			for (int i = 0; i < InputStorageArraySize; i++) // assign/copy all values from CharArray to Temp
			{
				TempArray[i] = InputStorageArray[i];
			}

			InputStorageArraySize += ArrayStep; // expand the Array size
			InputStorageArray = new char[InputStorageArraySize](); // over ride CharArray with new, bigger, array

			/*
			ArraySize-2 calculates TempArray size
			Copy all values from Temp array to "old" expanded array
			*/
			for (int i = 0; i < InputStorageArraySize - ArrayStep; i++)
			{
				InputStorageArray[i] = TempArray[i];
			}

			delete[] TempArray;
		}

		InputStorageArray[InputStorageArrayIndexPointer] = CharaterToAdd;
		InputStorageArrayIndexPointer++;
	}
	catch (...)
	{
		return false;
	}
	return true;
}
void AutoSelectClass::RemovePreviousCharacter()
{
	// Coord for backspace cursor position editing
	COORD NewCoord;

	if (AutoSelectClass::InputStorageArrayIndexPointer > 0)
	{
		NewCoord = { (SHORT)(GlobalFunctions::GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).X - 1), GlobalFunctions::GetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE)).Y }; // create new coord with x-1 and same y
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NewCoord); // use new coord
		printf(" "); // delete character
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), NewCoord); // go back 1 space
		AutoSelectClass::InputStorageArrayIndexPointer--;
	}
	AutoSelectClass::InputStorageArray[AutoSelectClass::InputStorageArrayIndexPointer] = NULL;
}
void AutoSelectClass::FinishFeature(KBDLLHOOKSTRUCT kbdStruct)
{
	GlobalFunctions::clear_screen();

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

		//keybd_event(VK_SHIFT, (UINT)kbdStruct.scanCode, KEYEVENTF_KEYUP, 0);/
	}
	else
	{
		printf("Input cannot be empty\n");
	}

	AutoSelectClass::Enabled = false;
	
	{
		std::string temp = "Moved " + std::to_string(DirectionCount) + " Spaces Right" + '\n';

		DynamicArray<char> tempArray = DynamicArray<char>();
		tempArray.ArrayAppend((char*)temp.c_str(), temp.length(), false);

		LoggingClass::LoggingDynamicArray.Append(tempArray);
	} // putting temp in lower scope so it gets cleared

	printf("====Logs====\n");
	for (DynamicArray<char> ChAr : LoggingClass::LoggingDynamicArray)
	{
		printf(ChAr.GetArray());
	}
}
#pragma endregion

#pragma region Logging Region
DynamicArray<DynamicArray<char>> LoggingClass::LoggingDynamicArray = DynamicArray<DynamicArray<char>>(2, 4);
#pragma endregion