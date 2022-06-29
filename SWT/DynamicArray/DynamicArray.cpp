#pragma region Constructors
template<class ArrayDataType>
DynamicArray<ArrayDataType>::DynamicArray()
{
    // Default values, can be changed
    ArraySize = 10;
    ArrayStepSize = 5;

    // ! DO NOT CHANGE !
    ArrayIndexPointer = 0;
    Array = new ArrayDataType[ArraySize]();
}

template<class ArrayDataType>
DynamicArray<ArrayDataType>::DynamicArray(int StartSize, int StepSize)
{
    ArraySize = StartSize;
    ArrayStepSize = StepSize;

    // ! DO NOT CHANGE !
    ArrayIndexPointer = 0;
    Array = new ArrayDataType[ArraySize]();
}
#pragma endregion

#pragma region Array Modification
template<class ArrayDataType>
void DynamicArray<ArrayDataType>::ArrayAppend(ArrayDataType ArrayToAdd[], int size, bool includeEscape)
{
    if (std::is_same<ArrayDataType, std::string>::value || std::is_same<ArrayDataType, char>::value) // For Text types only
    {
        for (int i = 0; i < size; ++i) // for loop to get and append all character
        {
            if (includeEscape) // if IncludeEscape is true, append all character
            {
                Append(ArrayToAdd[i]); // Append character to array
            }
            else if (!(ArrayToAdd[i] == 0)) // if IncludeEscape is false, include all chars that aren't null
            {
                Append(ArrayToAdd[i]); // Append character to array
            }
        }
    }
    else
    {
        for (int i = 0; i < size; ++i) // for loop to get and append all Array Objects
        {
            Append(ArrayToAdd[i]);
        }
    }
}

template<class ArrayDataType>
void DynamicArray<ArrayDataType>::Append(ArrayDataType ObjectToAdd)
{
    if (ArrayIndexPointer >= ArraySize) // if Current Index pointer is more then the array size (trying to add to OutOfRange space)
    {
        ArrayDataType* TempArray = new ArrayDataType[ArraySize](); // Create new array which will store the original values

        for (int i = 0; i < ArraySize; i++) // assign/copy all values from Array to Temp
        {
            TempArray[i] = Array[i];
        }

        ArraySize += ArrayStepSize; // expand the Array size
        Array = new ArrayDataType[ArraySize](); // over ride Array with new, bigger, array

        /*
        ArraySize-ArrayStepSize calculates TempArray size
        Copy all values from Temp array to "old" expanded array
        */
        for (int i = 0; i < ArraySize - ArrayStepSize; i++)
        {
            Array[i] = TempArray[i];

        }

        delete[] TempArray;
    }

    Array[ArrayIndexPointer] = ObjectToAdd;
    ArrayIndexPointer++;
}

template<class ArrayDataType>
void DynamicArray<ArrayDataType>::Replace(ArrayDataType ReplaceObject, int position)
{
    if (position >= (ArrayIndexPointer-1) || position < 0)// check if the position to remove is in array range
    {
        throw std::out_of_range("position was out of range of the array");
        return;
    }

    Array[position] = ReplaceObject;
}

template<class ArrayDataType>
void DynamicArray<ArrayDataType>::Remove(int position)
{
    if (position >= (ArrayIndexPointer - 1) || position < 0)// check if the position to remove is in array range
    {
        throw std::out_of_range("position was out of range of the array");
        return;
    }

    for (int i = position; i < (ArrayIndexPointer-1); i++) // moving all back
    {
        Array[i] = Array[i + 1];
    }
    Array[ArrayIndexPointer-1] = NULL; // make last character blank
    ArrayIndexPointer--;
}
#pragma endregion

#pragma region Variables
template<class ArrayDataType>
ArrayDataType* DynamicArray<ArrayDataType>::GetArray()
{
    return Array;
}

template<class ArrayDataType>
int DynamicArray<ArrayDataType>::GetArraySize()
{
    return ArraySize;
}

template<class ArrayDataType>
int DynamicArray<ArrayDataType>::GetArrayIndexPointer()
{
    return ArrayIndexPointer;
}

template<class ArrayDataType>
int DynamicArray<ArrayDataType>::GetArrayStepSize()
{
    return ArrayStepSize;
}
#pragma endregion
