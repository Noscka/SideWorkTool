#include "Features.h"

bool EquationClass::Enabled = false;
char EquationClass::InputStorageArray[124] = {};
int EquationClass::InputStorageArrayIndexPointer = 0;
bool EquationClass::AddToCharArray(char Character)
{
	try
	{
		InputStorageArray[InputStorageArrayIndexPointer] = Character;
		InputStorageArrayIndexPointer++;
	}
	catch (...)
	{
		return false;
	}
	return true;
}


bool AutoSelectClass::Enabled = false;
char AutoSelectClass::InputStorageArray[124] = {};
int AutoSelectClass::InputStorageArrayIndexPointer = 0;
bool AutoSelectClass::AddToCharArray(char Character)
{
	try
	{
		InputStorageArray[InputStorageArrayIndexPointer] = Character;
		InputStorageArrayIndexPointer++;
	}
	catch (...)
	{
		return false;
	}
	return true;
}