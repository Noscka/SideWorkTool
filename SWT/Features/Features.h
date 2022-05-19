#pragma once
#include <string>

static class EquationClass
{
public:
	static bool Enabled;

	static char* InputStorageArray; // Equation Char Array
	static int InputStorageArraySize; // InputStorageArray Array Size
	static int InputStorageArrayIndexPointer; // InputStorageArray Array Index Pointer
	static int ArrayStep; // how much the array will get increased by when it reaches the limit

	static bool AddToDynamicCharArray(char Character);
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
};

static class LoggingClass
{
public:
	static char** LoggingArray; // Logging Array Char Array
	static int LoggingArraySize; // InputStorageArray Array Size
	static int LoggingArrayIndexPointer; // Auto Select Array Index Pointer
	static int ArrayStep; // how much the array will get increased by when it reaches the limit

	static bool LogEvent(char Character[]);
};