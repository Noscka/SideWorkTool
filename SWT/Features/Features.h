#pragma once
#include <string>
#include <Windows.h>
#include <iostream>
#include <codecvt>
#include <locale>

#include "../TinyExpr/tinyexpr.h"
#include "../DynamicArray/DynamicArray.h"
#include "../ImprovedDynamicMenu/DynamicMenu.h"
#include "../Options/Options.h"
#include "../LoadingScreen/LoadingScreen.h"

static class GlobalFunctions
{
public:
	static COORD GetConsoleCursorPosition(HANDLE hConsoleOutput);
	static void clear_screen(char fill = ' ');

	/// <summary>
	/// Check if String is just numbers
	/// </summary>
	/// <param name="str">String to Check</param>
	/// <returns>True if only numbers, False if not just numbers</returns>
	static bool isNumber(const std::string& str);

	/// <summary>
	/// Get data from lParam to determine which key was pressed
	/// </summary>
	/// <param name="lParam">lParam from hook</param>
	/// <returns>wchar_t array</returns>
	static wchar_t* GetUnicodeCharacter(LPARAM lParam, KBDLLHOOKSTRUCT kbdStruct);

	static std::wstring to_wstring(const std::string& str);
	static std::string to_string(const std::wstring& wstr);

	static void ShowCaret(bool showFlag);
};

static class SettingsClass
{
public:
	static DynamicMenu SettingsMenu;

	static bool ShowCaret;

	static void initialize(LoadingScreen* Object);

	static void QuitAndSave();
	static void ApplyChanges();
};

static class EquationClass
{
public:
	static bool Enabled;

	static DynamicArray<wchar_t> InputStorageArray; // Dynamic Array for function

	static void RemovePreviousCharacter();
	static void FinishFeature(KBDLLHOOKSTRUCT kbdStruct);
};

static class AutoSelectClass
{
public:
	static bool Enabled;

	static DynamicArray<wchar_t> InputStorageArray; // Dynamic Array for function

	static void RemovePreviousCharacter();
	static void FinishFeature(KBDLLHOOKSTRUCT kbdStruct);
};

static class LoggingClass
{
private:
public:
	static DynamicArray<DynamicArray<wchar_t>> LoggingDynamicArray;
	static void WriteLog(wchar_t* LogTest, int LogLength);
};