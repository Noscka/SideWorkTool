#pragma once
#include <string>
#include <Windows.h>
#include <iostream>
#include <codecvt>
#include <locale>

#include "../GlobalFunction/GlobalFunction.h"
#include "../TinyExpr/tinyexpr.h"
#include "../DynamicArray/DynamicArray.h"
#include "../ImprovedDynamicMenu/DynamicMenu.h"
#include "../Options/Options.h"
#include "../LoadingScreen/LoadingScreen.h"


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