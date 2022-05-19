#include "Features.h"
#include <iostream>

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
#pragma endregion

#pragma region Logging Region
char** LoggingClass::LoggingArray = new char*[LoggingArraySize];
int LoggingClass::LoggingArrayIndexPointer = 0;
int LoggingClass::LoggingArraySize = 8;
int LoggingClass::ArrayStep = 10;
bool LoggingClass::LogEvent(char* StringToAdd)
{
	try
	{
		if (LoggingArrayIndexPointer >= LoggingArraySize)
		{
			char** TwoDimensionalTemp = new char* [LoggingArraySize](); // create temp pointer array of pointer arrays

			for (int i = 0; i < LoggingArraySize; i++) // copy data
			{
				TwoDimensionalTemp[i] = LoggingArray[i];
			}

			LoggingArraySize += ArrayStep;
			LoggingArray = new char* [LoggingArraySize](); // increase array

			for (int i = 0; i < LoggingArraySize - ArrayStep; i++) // copy data back
			{
				LoggingArray[i] = TwoDimensionalTemp[i];
			}

			delete[] TwoDimensionalTemp; //delete array of temp
		}

		LoggingArray[LoggingArrayIndexPointer] = StringToAdd;
		LoggingArrayIndexPointer++;
	}
	catch (...)
	{
		return false;
	}
	return true;
}
#pragma endregion