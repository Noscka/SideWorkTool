#pragma once
static class EquationClass
{
public:
	static bool Enabled;

	// InputStorageArray Char Array
	static char InputStorageArray[124];
	static int InputStorageArrayIndexPointer; // InputStorageArray Array Index Pointer

	static bool AddToCharArray(char Character);
};

static class AutoSelectClass
{
public:
	static bool Enabled;

	// Auto Select Char Array
	static char InputStorageArray[124];
	static int InputStorageArrayIndexPointer; // Auto Select Array Index Pointer

	static bool AddToCharArray(char Character);
};