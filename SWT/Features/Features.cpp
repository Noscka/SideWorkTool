#include "Features.h"

bool EquationClass::Enabled = false;
char EquationClass::Equation[124] = {};
int EquationClass::EquationArrayIndexPointer = 0;
bool EquationClass::AddToCharArray(char Character)
{
	try
	{
		Equation[EquationArrayIndexPointer] = Character;
		EquationArrayIndexPointer++;
	}
	catch (...)
	{
		return false;
	}
	return true;
}


bool AutoSelectClass::Enabled = false;
char AutoSelectClass::AutoSelectArray[124] = {};
int AutoSelectClass::AutoSelectArrayIndexPointer = 0;
bool AutoSelectClass::AddToCharArray(char Character)
{
	try
	{
		AutoSelectArray[AutoSelectArrayIndexPointer] = Character;
		AutoSelectArrayIndexPointer++;
	}
	catch (...)
	{
		return false;
	}
	return true;
}