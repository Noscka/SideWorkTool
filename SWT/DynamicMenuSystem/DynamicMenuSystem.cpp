#include "DynamicMenuSystem.h"
#include "AsciiTextGenerator.h"
#include <cstdarg>
#include <conio.h>
#include <future>

void clear_screen_DynamicMenuSystem(char fill = ' ')
{
	COORD tl = {0,0};
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
}

// Define Variables to not throw "unresolved External Symbol"
#pragma region Variables
CONSOLE_SCREEN_BUFFER_INFO DynamicMenuSystem::csbi;
int DynamicMenuSystem::columns, DynamicMenuSystem::rows;
std::list<MenuEntry> DynamicMenuSystem::MenuEntryList;
bool DynamicMenuSystem::SetUpEntries, DynamicMenuSystem::ContinueMenu = true;
#pragma endregion

inline void DynamicMenuSystem::QuitMenu() {}

void DynamicMenuSystem::CreateMenu(std::string Title, bool AddExitEntry)
{
	DynamicMenuSystem::ContinueMenu = true; // incase menu was quit before

	if(AddExitEntry)
	{
		DynamicMenuSystem::MenuEntryList.push_back(MenuEntry("Quit Menu", QuitMenu));
	}

	int c, ex, counter = 0, CurrentIndex = 0;

	// only run is entries were added
	if(SetUpEntries)
	{
		while(ContinueMenu)
		{
			std::string OutputString; // string for full "display" as it is the most perfomace efficent method

			OutputString = AsciiTextGenerator::AsciiWrite(Title); // add title with "ascii generator"

			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
			columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
			rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

			// for loop using counter to get the index so to add the >< to the selected option
			counter = 0;
			for(MenuEntry Entry : DynamicMenuSystem::MenuEntryList)
			{
				// Append to string as to make it be 1 print operation, makes it way quicker
				if(counter == CurrentIndex)
				{
					OutputString += std::string((columns / 2) - (1 + Entry.Name.length()) / 2, ' ') + ">" + Entry.Name + "<\n";
				}
				else
				{
					OutputString += std::string((columns / 2) - Entry.Name.length() / 2, ' ') + Entry.Name + "\n";
				}
				counter++;
			}

			printf(OutputString.c_str());

			// get key input for arrow and enter inputs
			c = _getch();

			if(c == ENTER)
			{
				// if enter, get the function of the selected entry and run it
				std::list<MenuEntry>::iterator iterator = DynamicMenuSystem::MenuEntryList.begin();
				std::advance(iterator, CurrentIndex);

				//Functions::ClearScreen();
				((MenuEntry)*iterator).Function();

			}
			else if(!(c && c != 224))
			{
				// if not enter, do second getch as arrows input 2 characters to show they are arrows
				switch(ex = _getch())
				{
				case ARROW_UP:
					if(CurrentIndex > 0) // Decrement only if smaller then List size
					{
						CurrentIndex--; // Decrement the Indenetation
					}
					break;

				case ARROW_DOWN:
					if(CurrentIndex < DynamicMenuSystem::MenuEntryList.size() - 1) // Increment only if larger the 0
					{
						CurrentIndex++; // Increment the Indenetation
					}
					break;
				}
			}

			clear_screen_DynamicMenuSystem();
		}
	}
	else
	{
		throw std::invalid_argument("No Entries Added");
	}
}


void DynamicMenuSystem::AddMenuEntries(int size, MenuEntry ...)
{
	SetUpEntries = true; // allow for "CreateMenu" to run

	va_list ArgList; // valist for "infite" inputs
	va_start(ArgList, size);

	for(int i = 0; i < size; i++)
	{
		MenuEntryList.push_back(va_arg(ArgList, MenuEntry));
	}

	va_end(ArgList);
}
