#pragma once
#include <functional>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

#include "../DynamicArray/DynamicArray.h"
#include "../ImprovedDynamicMenu/DynamicMenu.h"

class Option
{
private:
public:
	enum OptionType
	{
		EmptyType = 0,
		IntegerType = 1,
		BooleanType = 2,
	};

	// Static Members
	static DynamicArray<Option*> OptionsArray;
	static std::wstring OptionFileName;

	static void WriteOptions();

	static bool ParseOptions();

	static Option *FindOption(std::wstring OptionName);

	static std::wstring trim(const std::wstring& str, const std::wstring& whitespace = L" \t");
	static std::wstring reduce(const std::wstring& str, const std::wstring& fill = L" ", const std::wstring& whitespace = L" \t");

	static bool stob(std::wstring, bool throw_on_error = true);

	// Relative Members

	std::wstring OptionName;
	int *IntVariable;
	bool *BoolVariable;
	OptionType Type;

	Option() { Type = EmptyType; }

	Option(std::wstring optionName, int *DefaultValue)
	{
		if (optionName == L"")
		{
			throw std::invalid_argument("option needs a name");
			return;
		}

		for (Option* op : OptionsArray)
		{
			if (op->OptionName == optionName)
			{
				throw std::invalid_argument("option with the same name already exists");
				return;
			}
		}

		OptionName = reduce(optionName);
		IntVariable = DefaultValue;
		Type = IntegerType;

		OptionsArray.Append(this);
	}

	Option(std::wstring optionName, bool *DefaultValue)
	{
		if (optionName == L"")
		{
			throw std::invalid_argument("option needs a name");
			return;
		}

		for (Option* op : OptionsArray)
		{
			if (op->OptionName == optionName)
			{
				throw std::invalid_argument("option with the same name already exists");
				return;
			}
		}

		OptionName = reduce(optionName);
		BoolVariable = DefaultValue;
		Type = BooleanType;

		OptionsArray.Append(this);
	}

	MenuEntry ReturnMenuEntry();

	MenuEntry ReturnMenuEntry(std::wstring EntryName);
};
