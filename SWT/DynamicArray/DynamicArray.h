#pragma once
#include <iostream>

template<class ArrayDataType>
class DynamicArray
{
private:
	int ArraySize;			// Array starting size and the size after it is resized
	ArrayDataType* Array;	// Pointer to Array
	int ArrayIndexPointer;	// keeps track amount of objects in array
	int ArrayStepSize;		// how much the array will get increased by when it reaches the limit

	typedef ArrayDataType* iterator;
	typedef const ArrayDataType* const_iterator;
public:
	/// <summary>
	/// Constructor to set all the variables
	/// </summary>
	DynamicArray();																// Constructor

	/// <summary>
	/// Constructor with starting size and step size params for custom objects
	/// </summary>
	/// <param name="StartSize"> - Starting size of the array</param>
	/// <param name="StepSize"> - how much the array will increase each time it reaches the limit</param>
	DynamicArray(int StartSize, int StepSize);									// Constructor with starting size and step size params

	/// <summary>
	/// Appends another array to the DynamicArray
	/// </summary>
	/// <param name="ArrayToAdd"> - the array to append</param>
	/// <param name="size"> - size of the array</param>
	/// <param name="includeEscape">(default = false) -  !TEXT DATA TYPES ONLY! if escape characters should be appended as well</param>
	void ArrayAppend(ArrayDataType ArrayToAdd[], int size, bool includeEscape = false);	// Adds an array to the Dynamic Array

	/// <summary>
	/// Append single Object
	/// </summary>
	/// <param name="ObjectToAdd"> - Object to add</param>
	void Append(ArrayDataType ObjectToAdd);												// Adds a Object to the Array

	/// <summary>
	/// Replaces a a chosen positin with the chosen Object
	/// </summary>
	/// <param name="ReplaceObject"> - Object to place in the position</param>
	/// <param name="position"> - position to put the Object in</param>
	void Replace(ArrayDataType ReplaceObject, int position);							// Replaces a Object in the Array

	/// <summary>
	/// Remove and move all Object infront, back 1 spot
	/// </summary>
	/// <param name="position"> - Position to remove</param>
	void Remove(int position);															// Removes Object and moves everything infront of it back

	// Get private variables
	ArrayDataType* GetArray();
	int GetArraySize();
	int GetArrayIndexPointer();
	int GetArrayStepSize();

#pragma region For Loop Functions
	// For loop range-based function
	iterator begin() { return &Array[0]; }
	const_iterator begin() const { return &Array[0]; }
	iterator end() { return &Array[ArrayIndexPointer]; }
	const_iterator end() const { return &Array[ArrayIndexPointer]; }
#pragma endregion

#pragma region Operators
	friend std::ostream& operator<<(std::ostream& os, const DynamicArray& Array)
	{
		if (std::is_same<ArrayDataType, std::string>::value || std::is_same<ArrayDataType, char>::value) // if type is text type, output as text
		{
			os << Array.Array;
		}
		else  // if type is any other "list" the array with comman
		{
			for (int i = 0; i < Array.ArrayIndexPointer; i++)
			{
				os << Array.Array[i];

				if (!(i == Array.ArrayIndexPointer - 1))
				{
					os << ", ";
				}
			}
		}
		return os;
	}

	/// <summary>
	/// [] operator which acts the same as the Array [] operator
	/// </summary>
	/// <param name="position"> - position of the value wanted</param>
	/// <returns>value in the position</returns>
	ArrayDataType& operator[](int position)
	{
		return Array[position];
	}
#pragma endregion
};

#include "DynamicArray.cpp"