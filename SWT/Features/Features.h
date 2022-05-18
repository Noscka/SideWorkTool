#pragma once
static class EquationClass
{
public:
	static bool Enabled;

	// InputStorageArray Char Array
	static char* InputStorageArray;
	static int InputStorageArraySize; // InputStorageArray Array Size
	static int InputStorageArrayIndexPointer; // InputStorageArray Array Index Pointer

	static bool AddToDynamicCharArray(char Character);
};

static class AutoSelectClass
{
public:
	static bool Enabled;

	// Auto Select Char Array
	static char* InputStorageArray;
	static int InputStorageArraySize; // InputStorageArray Array Size
	static int InputStorageArrayIndexPointer; // Auto Select Array Index Pointer

	static bool AddToDynamicCharArray(char Character);
};