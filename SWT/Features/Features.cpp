#include "Features.h"
#include <iostream>

bool EquationClass::Enabled = false;
char* EquationClass::InputStorageArray = new char[InputStorageArraySize]();
int EquationClass::InputStorageArrayIndexPointer = 0;
int EquationClass::InputStorageArraySize = 128;
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

			InputStorageArraySize += 20; // expand the Array size
			InputStorageArray = new char[InputStorageArraySize](); // over ride CharArray with new, bigger, array

			/*
			ArraySize-2 calculates TempArray size
			Copy all values from Temp array to "old" expanded array
			*/
			for (int i = 0; i < InputStorageArraySize - 20; i++)
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

bool AutoSelectClass::Enabled = false;
char *AutoSelectClass::InputStorageArray = new char[InputStorageArraySize]();
int AutoSelectClass::InputStorageArrayIndexPointer = 0;
int AutoSelectClass::InputStorageArraySize = 128;
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

			InputStorageArraySize += 20; // expand the Array size
			InputStorageArray = new char[InputStorageArraySize](); // over ride CharArray with new, bigger, array

			/*
			ArraySize-2 calculates TempArray size
			Copy all values from Temp array to "old" expanded array
			*/
			for (int i = 0; i < InputStorageArraySize - 20; i++)
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