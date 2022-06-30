#pragma once
#include <string>
#include <Windows.h>
#include "../TinyExpr/tinyexpr.h"
#include "../DynamicArray/DynamicArray.h"
#include <iostream>


static class GlobalFunctions
{
public:
	static COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);
	static void clear_screen(char fill = ' ');
	static bool isNumber(const std::string& str);
	static wchar_t* GetUnicodeCharacter(LPARAM lParam, KBDLLHOOKSTRUCT kbdStruct);
};

static class EquationClass
{
public:
	static bool Enabled;

	static char* InputStorageArray; // Equation Char Array
	static int InputStorageArraySize; // InputStorageArray Array Size
	static int InputStorageArrayIndexPointer; // InputStorageArray Array Index Pointer
	static int ArrayStep; // how much the array will get increased by when it reaches the limit

	static bool AddToDynamicCharArray(char Character);
	static void RemovePreviousCharacter();
	static void FinishFeature(KBDLLHOOKSTRUCT kbdStruct);
};

static class AutoSelectClass
{
public:
	static bool Enabled;

	static char* InputStorageArray; // Auto Select Char Array
	static int InputStorageArraySize; // InputStorageArray Array Size
	static int InputStorageArrayIndexPointer; // Auto Select Array Index Pointer
	static int ArrayStep; // how much the array will get increased by when it reaches the limit

	static bool AddToDynamicCharArray(char Character);
	static void RemovePreviousCharacter();
	static void FinishFeature(KBDLLHOOKSTRUCT kbdStruct);
};

static class LoggingClass
{
public:
	static DynamicArray<DynamicArray<char>> LoggingDynamicArray;
};