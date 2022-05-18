#pragma once
static class EquationClass
{
public:
	static bool Enabled;

	// Equation Char Array
	static char Equation[124];
	static int EquationArrayIndexPointer; // Equation Array Index Pointer

	static bool AddToCharArray(char Character);
};

static class AutoSelectClass
{
public:
	static bool Enabled;

	// Auto Select Char Array
	static char AutoSelectArray[124];
	static int AutoSelectArrayIndexPointer; // Auto Select Array Index Pointer

	static bool AddToCharArray(char Character);
};