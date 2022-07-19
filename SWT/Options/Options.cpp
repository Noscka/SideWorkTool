#include "Options.h"


DynamicArray<Option*> Option::OptionsArray = DynamicArray<Option*>();
std::wstring Option::OptionFileName = L"options.txt";

void Option::WriteOptions()
{
	std::wstring outputText;

	for (Option* option : Option::OptionsArray)
	{
        switch (option->Type)
        {
        case IntegerType:
            outputText += (*option).OptionName + std::wstring(4, L' ') + std::to_wstring(*(option->IntVariable)) + L",\n";
            break;
        case BooleanType:
            outputText += (*option).OptionName + std::wstring(4, L' ') + (*(option->BoolVariable) ? L"true" : L"false") + L",\n";
            break;
        }
	}
    
	std::wofstream file;
	file.open(OptionFileName);
	file << (outputText).c_str();
}

bool Option::ParseOptions()
{
	std::wifstream Read;
	Read.open(OptionFileName);

    if (Read.fail())
        return false;

	std::wstring FileContents;
	Read.seekg(0, std::ios::end);
	FileContents.reserve(Read.tellg());
	Read.seekg(0, std::ios::beg);

	FileContents.assign((std::istreambuf_iterator<wchar_t>(Read)),
						std::istreambuf_iterator<wchar_t>());
	Read.close();


    std::wstring temp = L"";
    FileContents.erase(std::remove(FileContents.begin(), FileContents.end(), '\n'), FileContents.end());

    for (wchar_t FCch : FileContents)
    {
        if (FCch == L',')
        {
            std::wstring temp2 = L"";
            bool HasContent = false;
            DynamicArray<std::wstring> StringArray = DynamicArray<std::wstring>(2, 4);
            int i = 0;
            for (wchar_t ch : temp)
            {
                i++;
                temp2 += ch;

                if (ch != ' ')
                    HasContent = true;

                if (ch == ' ' || i >= temp.length())
                {
                    if (HasContent)
                        StringArray.Append(temp2);

                    HasContent = false;
                    temp2 = L"";
                }
            }

            std::wstring Value = StringArray[StringArray.ArrayIndexPointer - 1];
            std::wstring Name = L"";

            for (int i = 0; i <= StringArray.ArrayIndexPointer - 2; i++)
            {
                Name += StringArray[i];
            }

            for (Option* op : Option::OptionsArray)
            {
                if (reduce(op->OptionName) == reduce(Name))
                {
                    switch (op->Type)
                    {
                    case IntegerType:
                        try
                        {
                            *(op->IntVariable) = std::stoi(Value);
                        }
                        catch (std::out_of_range ex)
                        {
                            if (Value[0] == '-')
                                *(op->IntVariable) = INT_MIN;
                            else
                                *(op->IntVariable) = INT_MAX;
                        }
                        break;
                    case BooleanType:
                        *(op->BoolVariable) = stob(Value);
                        break;
                    }
                    break;
                }
            }

            temp = L"";
        }
        else
        {
            temp += FCch;
        }
    }

    return true;
}

Option *Option::FindOption(std::wstring OptionName)
{
    for (Option* op : Option::OptionsArray)
    {
        if (op->OptionName == OptionName)
        {
            return op;
        }
    }
}

std::wstring Option::trim(const std::wstring& str,
                        const std::wstring& whitespace)
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::wstring::npos)
        return L""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

std::wstring Option::reduce(const std::wstring& str,
                    const std::wstring& fill,
                    const std::wstring& whitespace)
{
    // trim first
    auto result = trim(str, whitespace);

    // replace sub ranges
    auto beginSpace = result.find_first_of(whitespace);
    while (beginSpace != std::string::npos)
    {
        const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
        const auto range = endSpace - beginSpace;

        result.replace(beginSpace, range, fill);

        const auto newStart = beginSpace + fill.length();
        beginSpace = result.find_first_of(whitespace, newStart);
    }

    return result;
}

bool Option::stob(std::wstring s, bool throw_on_error)
{
    auto result = false;    // failure to assert is false

    std::wistringstream is(s);
    // first try simple integer conversion
    is >> result;

    if (is.fail())
    {
        // simple integer failed; try boolean
        is.clear();
        is >> std::boolalpha >> result;
    }

    if (is.fail() && throw_on_error)
    {
        throw std::invalid_argument(GlobalFunctions::to_string(s.append(L"Unable to convert to bool")));
    }

    return result;
}

MenuEntry Option::ReturnMenuEntry()
{
	return ReturnMenuEntry(OptionName);
}

MenuEntry Option::ReturnMenuEntry(std::wstring EntryName)
{
    switch (Type)
    {
    case EmptyType:
        break;
    case IntegerType:
        return MenuEntry(EntryName, IntVariable);
        break;
    case BooleanType:
        return MenuEntry(EntryName, BoolVariable);
        break;
    }
}